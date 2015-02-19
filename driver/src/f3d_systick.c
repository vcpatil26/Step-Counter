#include<f3d_systick.h>
#include<stdio.h>
#include <f3d_button.h>
#include<math.h>
static int j=0;
static int k=0;
static int m=0;
static int n=0;
static int16_t l[9000]={0};
static uint32_t z[300]={0};
static uint8_t pu8[3] ={0};
float Raw[3]={0};
static int falli=0;
void f3d_systick_init(void)
{
// Setup a systick rate of 100hz.
SysTick_Config(SystemCoreClock/100);
     setvbuf(stdin, NULL, _IONBF, 0);
     setvbuf(stdout, NULL, _IONBF, 0);
     setvbuf(stderr, NULL, _IONBF, 0);
     /* USART_ITConfig(USART1,USART_IT_TXE,ENABLE); */
     /* USART_ITConfig(USART2,USART_IT_TXE,ENABLE); */
}


/*void printy(void)
{
falli=1;
int i;
float pressure;
float Altitude_ft;
float velocity;
int y=0;
for(i=0;i<8999;i=i+3){
Raw[0]=(float)l[i]/L3G_Sensitivity_500dps;
Raw[1]=(float)l[i+1]/L3G_Sensitivity_500dps; USART_ITConfig(USART1,USART_IT_TXE,ENABLE);
Raw[2]=(float)l[i+2]/L3G_Sensitivity_500dps;
//printf("\nX:");
printf("%f",Raw[0]);
printf(",");
printf("%f",Raw[1]);
printf(",");
printf("%f",Raw[2]);
printf(",");
if(i%30==0){
pressure = (float)z[y] / 4096;
Altitude_ft = (1-pow(pressure/1013.25,0.190284))*145366.45;
if(Altitude_ft>=145366.45)
break;
y++;
printf("%f",Altitude_ft);}
//printf("%s","CUrrent count:");
printf("\n");
}
float pressure1 = (float)z[0] / 4096;
float pressure2 = (float)z[y-1] / 4096;
float Altitude_ft1 = (1-pow(pressure1/1013.25,0.190284))*145366.45;
float Altitude_ft2 = (1-pow(pressure2/1013.25,0.190284))*145366.45;
velocity= (Altitude_ft1 - Altitude_ft2)/y;
printf("\n\nvelocity is:%f",velocity);
}*/	


void SysTick_Handler(void)
{
float pressure1;
  k++;
  j++;
  static state = 0;
  int systick_flag;
  USART_ITConfig(USART1,USART_IT_TXE,ENABLE);
  USART_ITConfig(USART2,USART_IT_TXE,ENABLE);
  //USART_ITConfig(USART3,USART_IT_TXE,ENABLE);
    /* if(k%10==0 && k<30000 && falli==0) */
    /* { */
    /* int16_t pfData[3]; */
    /* f3d_gyro_getdata(pfData); */

    /* //printf("\nX :",pfdata[0]); */

    /* int i; */
    /* for(i=0; i<3; i++) { */
    /* //Raw[i]=(float)pfData[i]/L3G_Sensitivity_500dps; */
    /* l[m]= pfData[i]; */
    /* //printf("%u\n",l[m]); */
    /* m++; */
    /* } */


    /* /\*printf("\nX:"); */
    /* printf("%f",Raw[0]); */
    /* printf("\nY :"); */
    /* printf("%f",Raw[1]); */
    /* printf("\nZ :"); */
    /* printf("%f\n",Raw[2]);*\/ */
    /* if(j%100==0) */
    /* { */

    /* state ^= 1; */
    /* if (state==1) */
    /* state=1;//GPIOE->BSRR = GPIO_Pin_9; */
    /* else */
    /* state=2;//GPIOE->BRR = GPIO_Pin_9; */
    /* uint8_t ctrl1 = 0x00; */
    /* ctrl1 = 0x01; */
    /* f3d_sensor_write(&ctrl1, 0x21, 1); */
    /* systick_flag = 1; */
    /* uint8_t pu8[3] ={0}; */
    /* f3d_sensor_read(pu8, 0x28, 3); */
    /* uint32_t pressure = ((uint32_t)pu8[2]<<16)|((uint32_t)pu8[1]<<8)|pu8[0]; */

    /* z[n]=pressure; */
    /* n++; */
    /* //pressure1 = (float)z[n]; */
    /* //printf("%f",pressure1); */
    /* /\*float pressure1 = pressure / 4096; */
    /* printf("Pressure is:%f mb\n",pressure1);*\/ */
    /* //printf("%d",n); */

    /* /\*while(1){ */
    /* int z=0; */
    /* int j=f3d_button_read(); */
    /* if(j==1){ */
    /* while(f3d_button_read()); */
    /* j=0; */
    /* while(j!=1 && z<20) */
    /* { */
    /* z=z+1; */
    /* j=f3d_button_read(); */
    /* //if(j==0){ */
    /* uint8_t ctrl1 = 0x00; */
    /* ctrl1 = 0x01; */
    /* f3d_sensor_write(&ctrl1, 0x21, 1); */
    /* int16_t temperature; */
    /* uint8_t pu8[3] ={0}; */
    /* f3d_sensor_read(pu8, 0x2B, 2);//READING TEMPERATURE */
    /* temperature = ((uint16_t) pu8[1]<<8) | pu8[0]; */
    /* float Temperature_DegC = 42.5 + temperature / (120*4); */
    /* printf("Temperature is:%f\n",Temperature_DegC); */
    /* f3d_sensor_read(pu8, 0x28, 3);//READING PRESSURE */
    /* uint32_t pressure = ((uint32_t)pu8[2]<<16)|((uint32_t)pu8[1]<<8)|pu8[0]; // make a unsigned 32 bit variable */
    /* float pressure1 = pressure / 4096; */
    /* printf("Pressure is:%f mb\n",pressure1); */
    /* float Altitude_ft = (1-pow(pressure1/1013.25,0.190284))*145366.45; */
    /* printf("Altitude is:%f Ft\n",Altitude_ft); }while(f3d_button_read());}*\/ */
    /* } */
}


