/* main.c ---
 *
 * Filename: main.c
 * Description:
 * Author:
 * Maintainer:
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated:
 *           By:
 *     Update #: 0
 * Keywords:
 * Compatibility:
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change log:
 *
 *
 */
/* Code: */

#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_button.h>
#include <f3d_uart.h>
#include <stdio.h>

void RTC_init(void) {
  RTC_TimeTypeDef  RTC_TimeStructure;
  RTC_DateTypeDef  RTC_DateStructure;
  RTC_InitTypeDef  RTC_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  PWR_BackupAccessCmd(ENABLE);
  RCC_BackupResetCmd(ENABLE);
  RCC_BackupResetCmd(DISABLE);
  RCC_LSEDriveConfig(RCC_LSEDrive_High);
  RCC_LSEConfig(RCC_LSE_ON);
  printf("Prim: before LSE Init\n");
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
  printf("Prim: after LSE Init\n");
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
  RCC_RTCCLKCmd(ENABLE);

  RTC_WriteProtectionCmd(DISABLE); // Disable the RTC's write protection
  RTC_EnterInitMode();
  RTC_WaitForSynchro(); 

  RTC_StructInit(&RTC_InitStructure);
  RTC_Init(&RTC_InitStructure);
  
  RTC_DateStructInit(&RTC_DateStructure);
  RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);
  
  RTC_TimeStructInit(&RTC_TimeStructure);
  RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);
  
  RTC_ExitInitMode();
  RTC_WriteProtectionCmd(ENABLE);
  PWR_BackupAccessCmd(DISABLE);
}



void getline(char *buf) {
  char c;
  c=getchar();
  while ((c!='\n') && (c!='\r')) {
    *buf++ = c;
    putchar(c);
    c = getchar();
  }
  *buf = 0;
}

int rtc_settime (char *buf) {
  enum {HOUR,MINUTE,SECOND,MONTH,DAY,YEAR};

  RTC_TimeTypeDef t;
  RTC_DateTypeDef d;

  char *tok_start = buf;
  char *tok_end = buf;
  int field = HOUR;

  RTC_TimeStructInit(&t);
  RTC_DateStructInit(&d);

  while (field<=YEAR) {
    while ((*tok_end != ',') && (*tok_end)) {
      tok_end++;
    }
    *tok_end = 0;
    switch (field++) {
    case HOUR:
      t.RTC_Hours=atoi(tok_start);
      printf("hour = %d\n",t.RTC_Hours);
      break;
    case MINUTE:
      t.RTC_Minutes=atoi(tok_start);
      printf("min = %d\n",t.RTC_Minutes);
      break;
    case SECOND:
      t.RTC_Seconds=atoi(tok_start);
      printf("sec = %d\n",t.RTC_Seconds);
      break;
    case MONTH:
      d.RTC_Month=atoi(tok_start);
      printf("month = %d\n",d.RTC_Month);
      break;
    case DAY:
      d.RTC_Date=atoi(tok_start);
      printf("day = %d\n",d.RTC_Date);
      break;
    case YEAR:
      d.RTC_Year=atoi(tok_start) - 2000;
      printf("year = %d\n",d.RTC_Year);
      break;
    }
    tok_end++;
    tok_start=tok_end;
  }

  PWR_BackupAccessCmd(ENABLE);
  RTC_SetTime(RTC_Format_BIN, &t);
  RTC_SetDate(RTC_Format_BIN, &d);
  PWR_BackupAccessCmd(DISABLE);
  return (0);
}

void main(void) {
  RTC_TimeTypeDef RTC_TimeStructure;
  RTC_DateTypeDef RTC_DateStructure;

  int count=0;
  int seconds;
  char linebuffer[100];
  char field[30];
  char *p = field;
  char delimiter[] = ",";
  int field_num;
  int i;

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_uart_init();
  f3d_systick_init();
  f3d_led_init();
  f3d_button_init();
  RTC_init();
  printf("RTC Code Start\n");
  printf("@\n");

  getline(linebuffer);
  printf("\nHere is the line: %s\n",linebuffer);
  printf("#\n");

  rtc_settime(linebuffer);

  f3d_led_on(2);
  while (1) {
    RTC_GetTime(RTC_Format_BIN,&RTC_TimeStructure);
    RTC_GetDate(RTC_Format_BIN,&RTC_DateStructure);

    if (seconds!=RTC_TimeStructure.RTC_Seconds) {
      printf("%02d:%02d:%02d ",RTC_TimeStructure.RTC_Hours,RTC_TimeStructure.RTC_Minutes,RTC_TimeStructure.RTC_Seconds);
      seconds=RTC_TimeStructure.RTC_Seconds;
      printf("%d/%d/%d\n",RTC_DateStructure.RTC_Month,RTC_DateStructure.RTC_Date,RTC_DateStructure.RTC_Year + 2000); 

    }
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  printf("Assertion: %s %d\n",file, line);
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
