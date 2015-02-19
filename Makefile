TEMPLATEROOT = ..
# POLLED = 1

# compilation flags for gdb

CFLAGS  = -O1 -g
ASFLAGS = -g 

# object files

OBJS= $(STARTUP) main.o \
                 f3d_led.o \
                 f3d_button.o \
                 f3d_uart.o \
		 f3d_uart2.o \
                 f3d_systick.o \
                 queue.o \
                 f3d_delay.o \
                 f3d_sdcard.o \
                 stm32f30x_spi.o \
                 stm32f30x_rcc.o \
                 stm32f30x_gpio.o \
                 stm32f30x_usart.o \
                 stm32f30x_pwr.o \
                 stm32f30x_rtc.o \
                 stm32f30x_misc.o \
                 stm32f30x_tim.o \
                 ff.o \
                 mmcbb.o \
                 newlib_stubs.o \
		sensor.o \
		f3d_accel.o \
		f3d_i2c.o \
		stm32f30x_i2c.o \
                f3d_mag.o
		 
# include common make file

include $(TEMPLATEROOT)/Makefile.common
