#include <stm32f30x.h>

#define L3G_Sensitivity_250dps   (float) 114.285f
#define L3G_Sensitivity_500dps   (float) 57.1429f
#define L3G_Sensitivity_2000dps   (float) 14.285f

#define SENSOR_CS_LOW()   GPIO_ResetBits(GPIOA, GPIO_Pin_8);
#define SENSOR_CS_HIGH()  GPIO_SetBits(GPIOA, GPIO_Pin_8);

void f3d_sensor_interface_init();
void f3d_sensor_init(void);
void f3d_sensor_read(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead);
void f3d_sensor_write(uint8_t*, uint8_t, uint16_t);
static uint8_t f3d_sensor_sendbyte(uint8_t);
void f3d_sensor_getdata(float *pfData);
