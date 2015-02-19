#include <f3d_uart2.h>
#include <queue.h>
static queue_t rxbuf2;
static queue_t txbuf2;
void f3d_uart3_init(void) {

  // Initialization routines related to UART1
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC,&GPIO_InitStructure);

  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOC,10,GPIO_AF_7);
  GPIO_PinAFConfig(GPIOC,11,GPIO_AF_7);

  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART3 ,&USART_InitStructure);
  USART_Cmd(USART3 , ENABLE);

  // Initialize the rx and tx queues
  init_queue(&rxbuf2);
  init_queue(&txbuf2);
  // Setup the NVIC priority and subpriority
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x08;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x08;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  // Enable the RX interrupt
  USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
}

void USART3_IRQHandler(void) {
  int ch;
  if (USART_GetFlagStatus(USART3, USART_FLAG_RXNE)) {
    ch = USART_ReceiveData(USART3);
    while (!enqueue(&rxbuf2,ch));
  }
  if (USART_GetFlagStatus(USART3,USART_FLAG_TXE)) {
    ch = dequeue(&txbuf2);
    if (ch) {
      USART_SendData(USART3,ch);
    }
    else {
      USART_ITConfig(USART3,USART_IT_TXE,DISABLE);
    }
  }
}



int putchar3(int c) {
  while (!enqueue(&txbuf2,c));
}

/* while (USART_GetFlagStatus(USART3,USART_FLAG_TXE) ==(uint16_t)RESET) */
/* return 0; */
 
/* //if(c == '\n') */
/* USART_ITConfig(USART3,USART_IT_TXE,ENABLE); */
/* USART_SendData(USART3, c); */
/* } */

int getchar3(void) {
  int ch;
  while (!(ch=dequeue(&rxbuf2)));
  return (ch);
}



/* if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == (uint16_t)RESET) */
/* return 0; */
/* else */
/* { */
/* c = USART_ReceiveData(USART3); */
/* return c; */
/* } */
/* } */
/*
*/
/*
int getchar_nb(void)
{
return (dequeue(&rxbuf));
}
*/
void flush3()
{
  USART_ITConfig(USART3,USART_IT_TXE,ENABLE);
}

void putstring3(char *s)
{
  //
  //
  while(*s != 0)
    {
      putchar(*s);
      s++;
    }
}
