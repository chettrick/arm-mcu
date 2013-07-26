#!/bin/sh

# Script to validate the ARM Microcontroller Framework

# $Id$

# Transform named parameters to environment variables

for x ; do export ${x%=*}="${x#*=}"; done

# Set some default values

if [ ${#ARMSRC} -eq 0 ]; then
  export ARMSRC=${HOME}/src/ARM
fi

##########################################################################

export MCUFAMILY=at91sam7s
export BOARDNAME=OLIMEX_SAM7_P256
export WITH_CONIO=no
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=at91sam7s
export BOARDNAME=OLIMEX_SAM7_P256
export WITH_CONIO=yes
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_conio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=lpc11xx
export BOARDNAME=PROTOBOARD_LPC1114FN28
export WITH_CONIO=yes
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_adc.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_conio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=lpc11xx
export BOARDNAME=RASPBERRYPI_LPC1114
export WITH_CONIO=yes
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_adc.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_conio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=lpc17xx
export BOARDNAME=MBED_LPC1768
export WITH_CONIO=no
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_freertos.bin clean WITH_FREERTOS=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=lpc17xx
export BOARDNAME=MBED_LPC1768
export WITH_CONIO=no
export WITH_USBSERIAL=yes

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_freertos.bin clean WITH_FREERTOS=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=lpc17xx
export BOARDNAME=MBED_LPC1768
export WITH_CONIO=yes
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_conio.bin
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=lpc17xx
export BOARDNAME=BLUEBOARD_LPC1768_H
export WITH_CONIO=no
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_freertos.bin clean WITH_FREERTOS=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=lpc17xx
export BOARDNAME=BLUEBOARD_LPC1768_H
export WITH_CONIO=no
export WITH_USBSERIAL=yes

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_freertos.bin clean WITH_FREERTOS=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=lpc17xx
export BOARDNAME=BLUEBOARD_LPC1768_H
export WITH_CONIO=yes
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_conio.bin
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=lpc17xx
export BOARDNAME=LPC1768_MINI_DK2
export WITH_CONIO=no
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_freertos.bin clean WITH_FREERTOS=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=lpc17xx
export BOARDNAME=LPC1768_MINI_DK2
export WITH_CONIO=no
export WITH_USBSERIAL=yes

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_freertos.bin clean WITH_FREERTOS=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=lpc17xx
export BOARDNAME=LPC1768_MINI_DK2
export WITH_CONIO=yes
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_conio.bin
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=lpc23xx
export BOARDNAME=MBED_LPC2368
export WITH_CONIO=no
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=lpc23xx
export BOARDNAME=MBED_LPC2368
export WITH_CONIO=yes
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_conio.bin
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=lpc23xx
export BOARDNAME=OLIMEX_LPC_P2378
export WITH_CONIO=no
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=lpc23xx
export BOARDNAME=OLIMEX_LPC_P2378
export WITH_CONIO=yes
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_conio.bin
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=stm32f1
export BOARDNAME=OLIMEX_STM32_P103
export WITH_CONIO=no
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_freertos.bin clean WITH_FREERTOS=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=stm32f1
export BOARDNAME=OLIMEX_STM32_P103
export WITH_CONIO=yes
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_conio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=stm32f1
export BOARDNAME=OLIMEX_STM32_P107
export WITH_CONIO=no
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_freertos.bin clean WITH_FREERTOS=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=stm32f1
export BOARDNAME=OLIMEX_STM32_P107
export WITH_CONIO=yes
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_conio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=stm32f1
export BOARDNAME=STM32_VALUE_LINE_DISCOVERY
export WITH_CONIO=no
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=stm32f1
export BOARDNAME=STM32_VALUE_LINE_DISCOVERY
export WITH_CONIO=yes
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_conio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=stm32f1
export BOARDNAME=W5200E01_M3
export WITH_CONIO=no
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_freertos.bin clean WITH_FREERTOS=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_spi.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_wiznet.bin clean WITH_WIZNET=yes WITH_W5200=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=stm32f1
export BOARDNAME=W5200E01_M3
export WITH_CONIO=yes
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_conio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_spi.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=stm32f4
export BOARDNAME=STM32F4_DISCOVERY
export WITH_CONIO=no
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_freertos.bin clean WITH_FREERTOS=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=stm32f4
export BOARDNAME=STM32F4_DISCOVERY
export WITH_CONIO=no
export WITH_USBSERIAL=yes

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_freertos.bin clean WITH_FREERTOS=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=stm32f4
export BOARDNAME=STM32F4_DISCOVERY
export WITH_CONIO=yes
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_conio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=stm32f4
export BOARDNAME=FEZ_CERB40
export WITH_CONIO=no
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_freertos.bin clean WITH_FREERTOS=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=stm32f4
export BOARDNAME=FEZ_CERB40
export WITH_CONIO=no
export WITH_USBSERIAL=yes

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_freertos.bin clean WITH_FREERTOS=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=stm32f4
export BOARDNAME=FEZ_CERB40
export WITH_CONIO=yes
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_conio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=stm32f4
export BOARDNAME=NETDUINO2
export WITH_CONIO=no
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_freertos.bin clean WITH_FREERTOS=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=stm32f4
export BOARDNAME=NETDUINO2
export WITH_CONIO=no
export WITH_USBSERIAL=yes

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_freertos.bin clean WITH_FREERTOS=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=stm32f4
export BOARDNAME=NETDUINO2
export WITH_CONIO=yes
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_conio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=str91x
export BOARDNAME=STMICRO_STR910_EVAL
export WITH_CONIO=no
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_adc.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rtc.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=str91x
export BOARDNAME=STMICRO_STR910_EVAL
export WITH_CONIO=no
export WITH_USBSERIAL=yes

cd ${ARMSRC}/${MCUFAMILY}
make test_adc.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rtc.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_float.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_stdio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi

##########################################################################

export MCUFAMILY=str91x
export BOARDNAME=STMICRO_STR910_EVAL
export WITH_CONIO=yes
export WITH_USBSERIAL=no

cd ${ARMSRC}/${MCUFAMILY}
make test_gpio.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
cd ${ARMSRC}/demos
make test_objects.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_rand.bin clean
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
make test_systick.bin clean WITH_LWIP=yes
if [ $? -ne 0 ]; then echo "BARF" ; exit ; fi
