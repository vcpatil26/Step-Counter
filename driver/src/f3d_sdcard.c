/* f3d_sdcard.c ---
*
* Filename: f3d_sdcard.c
* Description:
* Author: Bryce Himebaugh
* Maintainer:
* Created: Thu Oct 24 05:18:36 2013
* Last-Updated:
* By:
* Update #: 0
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

/* Copyright (c) 2004-2007 The Trustees of Indiana University and
* Indiana University Research and Technology Corporation.
*
* All rights reserved.
*
* Additional copyrights may follow
*/

/* Code: */
#include <f3d_sdcard.h>
#include <f3d_delay.h>
#include <stdio.h>

void f3d_sdcard_init(void) {
  /* Pin Assignments
CS PB8
SCK PB13
MISO PB14
MOSI PB15
*/

  // Setup SPI2 to talk to the SD card
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef SPI_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 , ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  // Initialization for SCK, MISO, MOSI
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_5);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_5);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_5);

  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* SPI configuration -------------------------------------------------------*/
  SPI_I2S_DeInit(SPI2);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  // SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(SPI2, &SPI_InitStructure);

  /* Configure the RX FIFO Threshold */
  SPI_RxFIFOThresholdConfig(SPI2, SPI_RxFIFOThreshold_QF);
  /* Enable SPI1 */
  SPI_Cmd(SPI2, ENABLE);

  /* RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); // Prepare to use DMA to accelerate the transactions */

  /* Configure PB8 for SD Card CS */
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  // Deassert both chip selects
  SD_CS_HIGH();
}

int spiReadWrite(SPI_TypeDef *SPIx,uint8_t *rbuf, const uint8_t *tbuf, int cnt, uint16_t speed) {
  int i;
  int timeout;

  SPIx->CR1 = (SPIx->CR1&~SPI_BaudRatePrescaler_256)|speed;
  for (i = 0; i < cnt; i++){
    if (tbuf) {
      SPI_SendData8(SPIx,*tbuf++);
    }
    else {
      SPI_SendData8(SPIx,0xff);
    }
    timeout = 100;
    while (SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_RXNE) == RESET);
    if (rbuf) {
      *rbuf++ = SPI_ReceiveData8(SPIx);
    }
    else {
      SPI_ReceiveData8(SPIx);
    }
  }
  return i;
}

int spiReadWrite16(SPI_TypeDef *SPIx,uint16_t *rbuf, const uint16_t *tbuf, int cnt, uint16_t speed) {
  int i;
  
  SPIx->CR1 = (SPIx->CR1&~SPI_BaudRatePrescaler_256)|speed;
  SPI_DataSizeConfig(SPIx, SPI_DataSize_16b);
  
  for (i = 0; i < cnt; i++){
    if (tbuf) {
      // printf("data=0x%4x\n\r",*tbuf);
      SPI_I2S_SendData16(SPIx,*tbuf++);
    }
    else {
      SPI_I2S_SendData16(SPIx,0xffff);
    }
    while (SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_RXNE) == RESET);
    if (rbuf) {
      *rbuf++ = SPI_I2S_ReceiveData16(SPIx);
    }
    else {
      SPI_I2S_ReceiveData16(SPIx);
    }
  }
  SPI_DataSizeConfig(SPIx, SPI_DataSize_8b);

  return i;
}


uint32_t get_fattime(void) {
  // Get time and return a packed 32-bit word for FAT File System
  // bit31:25 Year from 1980 (0..127)
  // bit24:21 Month (1..12)
  // bit20:16 Day in month(1..31)
  // bit15:11 Hour (0..23)
  // bit10:5 Minute (0..59)
  // bit4:0 Second / 2 (0..29)
  uint32_t compressed_time = 0;
  uint32_t temp = 0;
  RTC_DateTypeDef RTC_DateStructure;
  RTC_TimeTypeDef RTC_TimeStructure;

  RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
  RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
  
  printf("%d\n",RTC_DateStructure.RTC_Year);
  compressed_time |= (((2000-1980) + RTC_DateStructure.RTC_Year) << 25);
  compressed_time |= (RTC_DateStructure.RTC_Month << 21);
  compressed_time |= (RTC_DateStructure.RTC_Date << 16);
  compressed_time |= (RTC_TimeStructure.RTC_Hours << 11);
  compressed_time |= (RTC_TimeStructure.RTC_Minutes<<5);
  compressed_time |= RTC_TimeStructure.RTC_Seconds/2;
  return (compressed_time);
}

char *error_messages[20] = {"FR_OK: Succeeded\n", \
"FR_DISK_ERR: A hard error occurred in the low level disk I/O layer\n", \
"FR_INT_ERR: Assertion failed", \
"FR_NOT_READY: The physical drive cannot work", \
"FR_NO_FILE: Could not find the file\n", \
"FR_NO_PATH: Could not find the path\n", \
"FR_INVALID_NAME: The path name format is invalid\n", \
"FR_DENIED: Access denied due to prohibited access or directory full\n", \
"FR_EXIST: Access denied due to prohibited access\n", \
"FR_INVALID_OBJECT: The file/directory object is invalid\n", \
"FR_WRITE_PROTECTED: The physical drive is write protected\n", \
"FR_INVALID_DRIVE: The logical drive number is invalid\n", \
"FR_NOT_ENABLED: The volume has no work area\n", \
"FR_NO_FILESYSTEM: There is no valid FAT volume\n", \
"FR_MKFS_ABORTED: The f_mkfs() aborted due to any parameter error\n", \
"FR_TIMEOUT: Could not get a grant to access the volume within defined period\n", \
"FR_LOCKED: The operation is rejected according to the file sharing policy\n", \
"FR_NOT_ENOUGH_CORE: LFN working buffer could not be allocated\n", \
"FR_TOO_MANY_OPEN_FILE: Number of open files > _FS_SHARE\n", \
"FR_INVALID_PARAMETER: Given parameter is invalid\n" };


void die (FRESULT rc) {
  if ((rc>=0)&&(rc<20)) {
    printf("Failed with rc=%u.\n", rc);
    printf("%s\n",error_messages[rc]);
  }
  else {
    printf("Failed with rc=%d.\n", rc);
  }
  while (1);
}



