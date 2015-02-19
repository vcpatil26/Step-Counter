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
#include<queue.h>
#include<f3d_gyro.h>
#include<f3d_systick.h>
#include <sensor.h>
#include <f3d_timer4.h>
#include <f3d_sdcard.h>
#include <stm32f30x_rtc.h>
#include <diskio.h>
#include <math.h>
#include<string.h>
FATFS Fatfs;	/* File system object */
FIL Fil;	/* File object */
BYTE Buff[128];	/* File read buffer */


/* int LSE_init (void) { */
/*   RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); */
/*   PWR_BackupAccessCmd(ENABLE); */
/*   RCC_LSEDriveConfig(RCC_LSEDrive_Low); */
/*   RCC_LSEConfig(RCC_LSE_ON); */
/*   while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET); */
/*   PWR_BackupAccessCmd(DISABLE); */
/*   return 0; */
/* } */

/* int RTC_init(void) { */
/*   RTC_TimeTypeDef  RTC_TimeStructure; */
/*   RTC_DateTypeDef  RTC_DateStructure; */
/*   RTC_InitTypeDef  RTC_InitStructure; */

/*   RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); */
/*   PWR_BackupAccessCmd(ENABLE); */
/*   //  printf("%04x\n",(uint32_t)(RTC->ISR)); */

/*   if (RTC_GetFlagStatus(RTC_FLAG_RSF) == SET) { */
/*     printf("Warm Boot\n"); */
/*   } */
/*   else { */
/*     printf("Cold Reset\n"); */
/*     RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); */
/*     PWR_BackupAccessCmd(ENABLE); */
/*     RCC_BackupResetCmd(ENABLE); */
/*     RCC_BackupResetCmd(DISABLE); */
/*     RCC_LSEDriveConfig(RCC_LSEDrive_High); */
/*     RCC_LSEConfig(RCC_LSE_ON); */

/*     printf("before LSE Init\n"); */
/*     while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET); */
/*     printf("After LSE Init\n"); */
    
/*     RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); */
/*     RCC_RTCCLKCmd(ENABLE); */
/*     RTC_WaitForSynchro(); */
    
/*     RTC_StructInit(&RTC_InitStructure); */
/*     RTC_Init(&RTC_InitStructure); */
    
/*     RTC_DateStructInit(&RTC_DateStructure); */
/*     RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure); */
    
/*     RTC_TimeStructInit(&RTC_TimeStructure); */
/*     RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure); */
    
/*     PWR_BackupAccessCmd(DISABLE); */
/*   } */
/* } */


int h=0;
int m1=0;
int m2=0;
int flag3=0;


/*void RTC_init(void) {
  RTC_TimeTypeDef  RTC_TimeStructure;
  RTC_DateTypeDef  RTC_DateStructure;
  RTC_InitTypeDef  RTC_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  PWR_BackupAccessCmd(ENABLE);   // Enable access to write to the RTC Registers
  RCC_BackupResetCmd(ENABLE);
  RCC_BackupResetCmd(DISABLE);

  PWR_BackupAccessCmd(ENABLE);

  /* LSI used as RTC source clock*/
  /*RCC_LSICmd(ENABLE);
  
  /* Wait till LSI is ready */  
  /*while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
  
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
  RCC_RTCCLKCmd(ENABLE);
  RTC_WaitForSynchro(); 
  
  RTC_StructInit(&RTC_InitStructure);   // Set the structure members to their default values
  RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
  RTC_InitStructure.RTC_AsynchPrediv = 88;
  RTC_InitStructure.RTC_SynchPrediv = 470;
  RTC_Init(&RTC_InitStructure); 

  RTC_DateStructure.RTC_Year = 13;
  RTC_DateStructure.RTC_Month = RTC_Month_November;
  RTC_DateStructure.RTC_Date = 7;
  RTC_DateStructure.RTC_WeekDay = RTC_Weekday_Thursday;
  RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);

  RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
  RTC_TimeStructure.RTC_Hours   = 0x09;
  RTC_TimeStructure.RTC_Minutes = 0x05;
  RTC_TimeStructure.RTC_Seconds = 0x00;  
  RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);
}*/


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


int ampm()
{
   int m=0;
	int c=0;
    while(f3d_button_read()==1);
    while(f3d_button_read()!=1 && m<3) {
       int i=0;
       f3d_led_on(m);
       while(i<1000000) {
          if(f3d_button_read()==1)
                return m;   
          i++;
       }
       f3d_led_off(m);
       m++;    
    } 
}


int setalarm()
{    
    int m=0;
	int c=0;
    while(f3d_button_read()==2);
    while(f3d_button_read()!=2) {
       int i=0;
       f3d_led_on(m);
       while(i<1000000) {
          if(f3d_button_read()==1)		
	     if(c==0)
                return m;   
	     else
		return m+8;
          i++;
       }
       //f3d_led_off(m);
       m++;
	if (m>7){
	   f3d_led_all_off();
	   m=m%8;
	   c=c+1;
	}  
	    
    }
}


void bijli(int b, int m,int balli)
{

	
	f3d_led_all_off();
	int h;
	int faa;
	if(b>12)
	f3d_led_on(7);
	else
	f3d_led_off(7);
	if(balli==1) {
	   h=m;
	   f3d_led_off(6);
	   //f3d_led_off(7);
	}
	else {
	   h=b;
	   //f3d_led_on(7);
	   f3d_led_on(6);
	   if(h>12) {
	      //f3d_led_on(6);
	      h=h-12;
	   }
	//else f3d_led_off(6);
	}
	
	faa= h%2;
	h=h/2;
	if(faa==1)
	   //a[3]=1;
	   f3d_led_on(0);
	else 
	   //a[3]=0;
	   f3d_led_off(0);
	faa= h%2;
	h=h/2;
	if(faa==1)
	   //a[3]=1;
	   f3d_led_on(1);
	else 
	   //a[3]=0;
	   f3d_led_off(1);
	faa= h%2;
	h=h/2;
	if(faa==1)
	   //a[2]=1;
	   f3d_led_on(2);
	else 
	   //a[2]=0;
	   f3d_led_off(2);
	faa= h%2;
	h=h/2;
	if(faa==1)
	   //a[1]=1;
	   f3d_led_on(3);
	else 
	   //a[1]=0;
	   f3d_led_off(3);
	faa= h%2;
	h=h/2;
	if(faa==1)
	   //a[0]=1;
	   f3d_led_on(4);
	else 
	   //a[0]=0;
	   f3d_led_off(4);
	faa= h%2;
	h=h/2;
	if(faa==1)
	   //a[0]=1;
	   f3d_led_on(5);
	else 
	   //a[0]=0;
	   f3d_led_off(5);	
}

void log243( int hours, int mins, int sec,int month,int date,int year,int mode)
{	FRESULT rc;	/* Result code */
  DIR dir;	/* Directory object */
  FILINFO fno;	/* File information object */
  UINT bw, br;
  unsigned int retval;
	int n=0;
int i;
  char as[100];
    f_mount(0, &Fatfs);  
if(flag3==0){
  //rc = f_open(&Fil, "HELLO.TXT", FA_WRITE | FA_CREATE_ALWAYS);
  //if (rc) die(rc);
flag3=1;
}
   printf("\nOpen an existing file (message.txt).\n");
   rc = f_open(&Fil, "HELLO.TXT", FA_WRITE);
   if (rc) die(rc);

   n=f_size(&Fil);
   f_lseek(&Fil,n);
   if(mode==1)
   sprintf(as,"%s%d%s%d%s%d%s%d%s%d%s%d\n","Time set:",hours,":",mins,":",sec," ",month,"/",date,"/",year);
   if(mode==2)
   sprintf(as,"%s%d%s%d%s%d%s%d%s%d%s%d\n","Button press:",hours,":",mins,":",sec," ",month,"/",date,"/",year);	
   if(mode==3)
   sprintf(as,"%s%d%s%d%s%d%s%d%s%d%s%d\n","Alaram was set at:",hours,":",mins,":",sec," ",month,"/",date,"/",year);
   if(mode==4)
   sprintf(as,"%s%d%s%d%s%d%s%d%s%d%s%d\n","Alaram went on at:",hours,":",mins,":",sec," ",month,"/",date,"/",year);
   if(mode==5)
   sprintf(as,"%s%d%s%d%s%d%s%d%s%d%s%d\n","Alaram was off at:",hours,":",mins,":",sec," ",month,"/",date,"/",year);
   if(mode==6)
   sprintf(as,"%s%d%s%d%s%d%s%d%s%d%s%d\n","Board moved at:",hours,":",mins,":",sec," ",month,"/",date,"/",year);
   		
	
   printf("\nWrite a text data.\n");
   rc = f_write(&Fil,as,strlen(as), &bw);
   if (rc) die(rc);

   printf("\nClose the file.\n");
   rc = f_close(&Fil);
   if (rc) die(rc);

    printf("\nOpen an existing file (message.txt).\n");
  rc = f_open(&Fil, "HELLO.TXT", FA_READ);
  if (rc) die(rc);
  
  printf("\nType the file content.\n");
  for (;;) {
    rc = f_read(&Fil, Buff, sizeof Buff, &br);	/* Read a chunk of file */
    if (rc || !br) break;	/* Error or end of file */
    for (i = 0; i < br; i++)	/* Type the data */
      putchar(Buff[i]);
  }
  if (rc) die(rc);
  
  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);
}

void to_wifly(char as[])
{
  
}

void main(void) {
  RTC_TimeTypeDef RTC_TimeStructure;
  RTC_DateTypeDef RTC_DateStructure;
  int flaayu=1;
  int count=0;
  int seconds;
  char linebuffer[100];
  char field[30];
  char *p = field;
  char delimiter[] = ",";
  int field_num;
  int i,j;
  int c = 3000000;
  int n=0;

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  f3d_systick_init();
  f3d_uart_init();
  f3d_led_init();
  f3d_button_init();
  f3d_gyro_init();
  f3d_sensor_interface_init();
  f3d_sensor_init();
  f3d_timer4_init();
  f3d_sdcard_init();
  
  RTC_init();
  printf("RTC Code Start\n");
  printf("@\n");

  getline(linebuffer);
  printf("\nHere is the line: %s\n",linebuffer);
  printf("#\n");
  int flag =0;
  rtc_settime(linebuffer);
  int o=0;
    RTC_GetTime(RTC_Format_BIN,&RTC_TimeStructure);
    RTC_GetDate(RTC_Format_BIN,&RTC_DateStructure);
    log243(RTC_TimeStructure.RTC_Hours,RTC_TimeStructure.RTC_Minutes,RTC_TimeStructure.RTC_Seconds,RTC_DateStructure.RTC_Month,RTC_DateStructure.RTC_Date,RTC_DateStructure.RTC_Year + 2000,1);
  while (1) {
    RTC_GetTime(RTC_Format_BIN,&RTC_TimeStructure);
    RTC_GetDate(RTC_Format_BIN,&RTC_DateStructure);
    if (seconds!=RTC_TimeStructure.RTC_Seconds) {
      printf("%02d:%02d:%02d ",RTC_TimeStructure.RTC_Hours,RTC_TimeStructure.RTC_Minutes,RTC_TimeStructure.RTC_Seconds);
      seconds=RTC_TimeStructure.RTC_Seconds;
      printf("%d/%d/%d\n",RTC_DateStructure.RTC_Month,RTC_DateStructure.RTC_Date,RTC_DateStructure.RTC_Year + 2000); 
    }  
    while(f3d_button_read()!=2){
	RTC_GetTime(RTC_Format_BIN,&RTC_TimeStructure);
    	 RTC_GetDate(RTC_Format_BIN,&RTC_DateStructure);
	 int16_t pfData[3];
    float raw[3];
    f3d_gyro_getdata(pfData); 
    int i;
   for(i=0; i<3; i++) { 
   raw[i]=(float)pfData[i]/L3G_Sensitivity_500dps;
   if(raw[i]>20){
    flaayu=0;} 
 }
if(flaayu==0)
{
RTC_GetTime(RTC_Format_BIN,&RTC_TimeStructure);
    RTC_GetDate(RTC_Format_BIN,&RTC_DateStructure);
    log243(RTC_TimeStructure.RTC_Hours,RTC_TimeStructure.RTC_Minutes,RTC_TimeStructure.RTC_Seconds,RTC_DateStructure.RTC_Month,RTC_DateStructure.RTC_Date,RTC_DateStructure.RTC_Year + 2000,6);
flaayu=1;
c = 2000000;
	    while(c>0)
	      c--; 
c = 2000000;
}
	  if(RTC_TimeStructure.RTC_Hours == h && RTC_TimeStructure.RTC_Minutes == ((m1*10)+m2) && flag == 0){
          log243(RTC_TimeStructure.RTC_Hours,RTC_TimeStructure.RTC_Minutes,RTC_TimeStructure.RTC_Seconds,RTC_DateStructure.RTC_Month,RTC_DateStructure.RTC_Date,RTC_DateStructure.RTC_Year + 2000,4);	
	  //printf("ALARM TIME\n");
	    flag = 1;
	    for(o=0;o<10;o++) {
	    f3d_frequency(800);
	    while(c>0)
	      c--;
	    f3d_frequency(0);
	    c = 2000000;
	    while(c>0)
	      c--; 
 	    c = 2000000;
	   log243(RTC_TimeStructure.RTC_Hours,RTC_TimeStructure.RTC_Minutes,RTC_TimeStructure.RTC_Seconds,RTC_DateStructure.RTC_Month,RTC_DateStructure.RTC_Date,RTC_DateStructure.RTC_Year + 2000,5);
 	    }
	  }
	  j=f3d_button_read();
	  //printf("J= %d\n",j);
	  if(j==1) {
	  //printf("HOURS DISPLAY\n");
	    while(f3d_button_read()==1);
	    RTC_GetTime(RTC_Format_BIN,&RTC_TimeStructure);
    	    RTC_GetDate(RTC_Format_BIN,&RTC_DateStructure);
            log243(RTC_TimeStructure.RTC_Hours,RTC_TimeStructure.RTC_Minutes,RTC_TimeStructure.RTC_Seconds,RTC_DateStructure.RTC_Month,RTC_DateStructure.RTC_Date,RTC_DateStructure.RTC_Year + 2000,2);
	    bijli(RTC_TimeStructure.RTC_Hours,RTC_TimeStructure.RTC_Minutes,0);
            
	    while(f3d_button_read()==0);
	    while(f3d_button_read()==1);
	    log243(RTC_TimeStructure.RTC_Hours,RTC_TimeStructure.RTC_Minutes,RTC_TimeStructure.RTC_Seconds,RTC_DateStructure.RTC_Month,RTC_DateStructure.RTC_Date,RTC_DateStructure.RTC_Year + 2000,2);
	    //printf("MINUTES DISPLAY\n");
	    RTC_GetTime(RTC_Format_BIN,&RTC_TimeStructure);
    	    RTC_GetDate(RTC_Format_BIN,&RTC_DateStructure);
	    bijli(RTC_TimeStructure.RTC_Hours,RTC_TimeStructure.RTC_Minutes,1);
          }
        }
	printf("ALARM MODE\n");
        f3d_led_all_off();
        h = setalarm();
	h = h+12;
        f3d_led_all_off();
        while(f3d_button_read()==1);
        m1 = setalarm();
        f3d_led_all_off();
        while(f3d_button_read()==1);
        m2 = setalarm();
	f3d_led_all_off();
	while(f3d_button_read()==1);
	if(ampm()==0)
	   h=h-12;

        printf("ALARM SET TO %d:%d%d\n",h,m1,m2);
	RTC_GetTime(RTC_Format_BIN,&RTC_TimeStructure);
    	RTC_GetDate(RTC_Format_BIN,&RTC_DateStructure);
	log243(RTC_TimeStructure.RTC_Hours,RTC_TimeStructure.RTC_Minutes,RTC_TimeStructure.RTC_Seconds,RTC_DateStructure.RTC_Month,RTC_DateStructure.RTC_Date,RTC_DateStructure.RTC_Year + 2000,3);
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
