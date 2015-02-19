#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_button.h>
#include <f3d_uart.h>
#include <stdio.h>
#include <queue.h>
#include <f3d_gyro.h>
#include <f3d_systick.h>
#include <sensor.h>
#include <f3d_timer4.h>
#include <f3d_sdcard.h>
#include <stm32f30x_rtc.h>
#include <diskio.h>
#include <math.h>
#include <string.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <math.h>

FATFS Fatfs;	/* File system object */
FIL Fil;	/* File object */
BYTE Buff[128];	/* File read buffer */


void amlog( float xa, float ya, float za,float xm,float ym,float zm)
{	FRESULT rc;	/* Result code */
  DIR dir;	/* Directory object */
  FILINFO fno;	/* File information object */
  UINT bw, br;
  unsigned int retval;
  int n=0;
  int i;
  int flag=0;
  char as[100];
  /* Provide a delay to allow the SDCARD time to go through it's power
     up initialization. */
  for (i=0;i<500;i++) {
    f3d_delay_uS(500);
  }
  f_mount(0, &Fatfs);  	
  while(1)
    {if (flag=0)
	{
	  printf("\nOpen an existing file (Data logger).\n");
	  rc = f_open(&Fil, "Data.TXT", FA_WRITE | FA_CREATE_ALWAYS);
	  if (rc) die(rc);
	  n=f_size(&Fil);
	  f_lseek(&Fil,n);
	  sprintf(as,"%f%s%f%s%f%s%f%s%f%s%f\n",xa,",",ya,",",za,",",xm,",",ym,",",zm);
	
	  printf("\nWrite a text data.\n");
	  rc = f_write(&Fil,as,strlen(as), &bw);
	  if (rc) die(rc);
	  flag=0;

	  printf("\nClose the file.\n");
	  rc = f_close(&Fil);
	  if (rc) die(rc);
	}
      else
	{ printf("\nOpen an existing file (Data.txt).\n");
	  rc = f_open(&Fil, "Data.TXT", FA_WRITE);
	  if (rc) die(rc);
	  n=f_size(&Fil);
	  f_lseek(&Fil,n);
	  sprintf(as,"%f%s%f%s%f%s%f%s%f%s%f\n",xa,",",ya,",",za,",",xm,",",ym,",",zm);

	  printf("\nWrite a text data.\n");
	  rc = f_write(&Fil,as,strlen(as), &bw);
	  if (rc) die(rc);

	  printf("\nClose the file.\n");
	  rc = f_close(&Fil);
	  if (rc) die(rc);
	}
    }
  /*printf("\nType the file content.\n");
    for (;;) {
    rc = f_read(&Fil, Buff, sizeof Buff, &br);	/* Read a chunk of file */
  //if (rc || !br) break;	/* Error or end of file */
  //for (i = 0; i < br; i++)	/* Type the data */
  /*putchar(Buff[i]);
    }
    if (rc) die(rc);
  
    printf("\nClose the file.\n");
    rc = f_close(&Fil);
    if (rc) die(rc);
    }*/
  
  printf("\nOpen root directory.\n");
  rc = f_opendir(&dir, "");
  if (rc) die(rc);
  
  printf("\nDirectory listing...\n");
  for (;;) {
    rc = f_readdir(&dir, &fno);	/* Read a directory item */
    if (rc || !fno.fname[0]) break;	/* Error or end of dir */
    if (fno.fattrib & AM_DIR)
      printf(" <dir> %s\n", fno.fname);
    else
      printf("%8lu %s\n", fno.fsize, fno.fname);
  }
  if (rc) die(rc);
  printf("\nTest completed.\n");

  rc = disk_ioctl(0,GET_SECTOR_COUNT,&retval);
  printf("%d %d\n",rc,retval);
  while (1);
}

/* char gpsparse(char s[200]) */
/* { */
/* int i,k; */
/* char temp[200]; */
/* for(i=0;i<200;i++) */
/* { */
/* if(s[i]=='$GGPA') */
/* {for(k=0;k<200;k++) */
/* {temp[k]=s[i];} */
/* }} */
/* return temp; */
/* } */

void gpslog(char p[200] )
{	
  //flush2();
  FRESULT rc;	/* Result code */
  DIR dir;	/* Directory object */
  FILINFO fno;	/* File information object */
  UINT bw, br;
  printf("Reached here");
  unsigned int retval;
  int n=0;
  int i;
  int flag=0;
  /* Provide a delay to allow the SDCARD time to go through it's power
     up initialization. */
  for (i=0;i<500;i++) {
    f3d_delay_uS(500);
  }
  f_mount(0, &Fatfs);  	
  while(1)
    {if (flag==0)
	{
	  printf("\nOpen an existing file (Gdata).\n");
	  rc = f_open(&Fil, "GPSDATA.TXT", FA_WRITE | FA_CREATE_ALWAYS);
	  if (rc) die(rc);
	  n=f_size(&Fil);
	  f_lseek(&Fil,n);	
	
	  printf("\nWrite a text data.\n");
	  rc = f_write(&Fil,p,strlen(p), &bw);
	  if (rc) die(rc);
	  flag=1;

	  printf("\nClose the file.\n");
	  rc = f_close(&Fil);
	  if (rc) die(rc);
	}
      else
	{ printf("\nOpen an existing file (GData.txt).\n");
	  rc = f_open(&Fil, "GPSDATA.TXT", FA_WRITE);
	  if (rc) die(rc);
 

	  printf("\nWrite a text data.\n");
	  rc = f_write(&Fil,p,strlen(p), &bw);
	  if (rc) die(rc);

	  printf("\nClose the file.\n");
	  rc = f_close(&Fil);
	  if (rc) die(rc);
	}
    }
  /*printf("\nType the file content.\n");
    for (;;) {
    rc = f_read(&Fil, Buff, sizeof Buff, &br);	/* Read a chunk of file */
  //if (rc || !br) break;	/* Error or end of file */
  //for (i = 0; i < br; i++)	/* Type the data */
  /*putchar(Buff[i]);
    }
    if (rc) die(rc);
  
    printf("\nClose the file.\n");
    rc = f_close(&Fil);
    if (rc) die(rc);
    }*/
  
  printf("\nOpen root directory.\n");
  rc = f_opendir(&dir, "");
  if (rc) die(rc);
  
  printf("\nDirectory listing...\n");
  for (;;) {
    rc = f_readdir(&dir, &fno);	/* Read a directory item */
    if (rc || !fno.fname[0]) break;	/* Error or end of dir */
    if (fno.fattrib & AM_DIR)
      printf(" <dir> %s\n", fno.fname);
    else
      printf("%8lu %s\n", fno.fsize, fno.fname);
  }
  if (rc) die(rc);
  printf("\nTest completed.\n");

  rc = disk_ioctl(0,GET_SECTOR_COUNT,&retval);
  printf("%d %d\n",rc,retval);
  while (1);
}


void main(void) {
  int mych;
  f3d_systick_init();
  f3d_uart_init();
  f3d_uart2_init();
  f3d_i2c1_init();
  f3d_accel_init();
  f3d_mag_init();
  f3d_delay_init();
  //f3d_led_init();
  f3d_sensor_interface_init();
  f3d_sensor_init();
  f3d_sdcard_init();
  //f3d_timer4_init();

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  float accel_data[3];
  float mag_data[3];
  int c,i;
  //float tilt,utilt;
  //float pitch,roll;
  //float xh,yh;
  float xm,ym,zm;
  float xa,ya,za,xna,yna;
  // DIR dir;	/* Directory object */
  //FILINFO fno;	/* File information object */
  //UINT bw, br;
  //unsigned int retval;
  //int n=0;
  //int i;
  char as[100];
  char g[500];
  //printf("Hrllo");
  /* Provide a delay to allow the SDCARD time to go through it's power
     up initialization. */
  /*for (i=0;i<500;i++) {
    f3d_delay_uS(500);
    }*/
  printf("\n\rAlive Again\n\r");

  /* while(1) { */
  /*   putchar2('a'); */
  /* } */

  /* while(1) { */
  /*   putchar2(getchar2()); */
  /* } */

  while (1) {
    if (mych=getchar_nb()) {
      putchar2(mych);
    }
    if (mych=getchar2_nb()) {
      putchar(mych);
    }
  }

  while (1) {
    if (mych=getchar2_nb()) {
      putchar(mych);
    }
    if (mych=getchar_nb()) {
      putchar2(mych);
    }
  }
  while(1) {
    //printf("Hello");
    f3d_accel_read(accel_data);		
    xa=accel_data[0];
    ya=accel_data[1];
    za=accel_data[2];
    c=0;

    //xna=(xa/sqrt((xa*xa)+(ya*ya)+(za*za)));
    //pitch=asin(-xna);
    //yna=(ya/sqrt((xa*xa)+(ya*ya)+(za*za)));
    //roll=asin(yna/cos(pitch));
    //printf("%s%f\n","Pitch : ",pitch*57.2957795);
    //printf("%s%f\n","Roll : ",roll*57.2957795);
    f3d_mag_read(mag_data);
    xm=mag_data[0];
    ym=mag_data[1];
    zm=mag_data[2];	


    printf("Magnetometer data: %d,%d,%d\n",xm,ym,zm);
    printf("Accelerometer data: %d,%d,%d\n",xa,ya,za);
    //amlog(xa,ya,za,xm,ym,zm);
    char mychar[20]="new string";
    putchar2(getchar2());
    //gpslog(mychar);
    //gpslog(g);
    /*while(1 && c<=500){
      printf("Code reached here\n");
      g[c] = getchar2();
      /*if(g[c]=='$GPGGA')
      {gpslog(g);}*/
    //gpslog(g);
    //c++;
    //break;}*/

    	
    //i++;
	
	

   
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

