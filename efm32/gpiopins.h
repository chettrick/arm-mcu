/* Abstract bitwise GPIO services */

// $Id$

#ifndef _GPIOPINS_H
#define _GPIOPINS_H

#include <_ansi.h>

// These services provide a simple and efficient mechanism for software to
// control individual GPIO pins in an asynchronous fashion, where each GPIO pin
// is independent of any other.  This API is NOT suitable for situations where
// GPIO pins are grouped in buses

// GPIO pins are numbered sequentially from the least significant bit of the
// lowest GPIO port to the highest port and bit.  For example, if an MCU has
// two 8-bit GPIO ports, the GPIO pins would be numbered GPIO0 to GPIO15.

// Each GPIO pin has two macro defined for it: GPIOnIN and GPIOnOUT.  These
// map to Cortex-M3 bitband registers for the particular GPIO pin.  Sadly,
// some Cortex-M3 devices (such as the EFM32 and STM32) do not have a single
// GPIO register that can be both written to and read from, thus preventing
// us from just defining a macro "GPIOn" for each GPIO pin.

_BEGIN_STD_C

typedef enum
{
  GPIOPIN_INPUT,
  GPIOPIN_OUTPUT,
} gpiopin_direction_t;

int gpiopin_configure(unsigned int pin, gpiopin_direction_t direction);

// PA0 is GPIOPIN0
#define GPIOPIN0	0
#define GPIOPIN0IN	(*((unsigned long int *) 0x420C0380))
#define GPIOPIN0OUT	(*((unsigned long int *) 0x420C0180))

// PA1 is GPIOPIN1
#define GPIOPIN1	1
#define GPIOPIN1IN	(*((unsigned long int *) 0x420C0384))
#define GPIOPIN1OUT	(*((unsigned long int *) 0x420C0184))

// PA2 is GPIOPIN2
#define GPIOPIN2	2
#define GPIOPIN2IN	(*((unsigned long int *) 0x420C0388))
#define GPIOPIN2OUT	(*((unsigned long int *) 0x420C0188))

// PA3 is GPIOPIN3
#define GPIOPIN3	3
#define GPIOPIN3IN	(*((unsigned long int *) 0x420C038C))
#define GPIOPIN3OUT	(*((unsigned long int *) 0x420C018C))

// PA4 is GPIOPIN4
#define GPIOPIN4	4
#define GPIOPIN4IN	(*((unsigned long int *) 0x420C0390))
#define GPIOPIN4OUT	(*((unsigned long int *) 0x420C0190))

// PA5 is GPIOPIN5
#define GPIOPIN5	5
#define GPIOPIN5IN	(*((unsigned long int *) 0x420C0394))
#define GPIOPIN5OUT	(*((unsigned long int *) 0x420C0194))

// PA6 is GPIOPIN6
#define GPIOPIN6	6
#define GPIOPIN6IN	(*((unsigned long int *) 0x420C0398))
#define GPIOPIN6OUT	(*((unsigned long int *) 0x420C0198))

// PA7 is GPIOPIN7
#define GPIOPIN7	7
#define GPIOPIN7IN	(*((unsigned long int *) 0x420C039C))
#define GPIOPIN7OUT	(*((unsigned long int *) 0x420C019C))

// PA8 is GPIOPIN8
#define GPIOPIN8	8
#define GPIOPIN8IN	(*((unsigned long int *) 0x420C03A0))
#define GPIOPIN8OUT	(*((unsigned long int *) 0x420C01A0))

// PA9 is GPIOPIN9
#define GPIOPIN9	9
#define GPIOPIN9IN	(*((unsigned long int *) 0x420C03A4))
#define GPIOPIN9OUT	(*((unsigned long int *) 0x420C01A4))

// PA10 is GPIOPIN10
#define GPIOPIN10	10
#define GPIOPIN10IN	(*((unsigned long int *) 0x420C03A8))
#define GPIOPIN10OUT	(*((unsigned long int *) 0x420C01A8))

// PA11 is GPIOPIN11
#define GPIOPIN11	11
#define GPIOPIN11IN	(*((unsigned long int *) 0x420C03AC))
#define GPIOPIN11OUT	(*((unsigned long int *) 0x420C01AC))

// PA12 is GPIOPIN12
#define GPIOPIN12	12
#define GPIOPIN12IN	(*((unsigned long int *) 0x420C03B0))
#define GPIOPIN12OUT	(*((unsigned long int *) 0x420C01B0))

// PA13 is GPIOPIN13
#define GPIOPIN13	13
#define GPIOPIN13IN	(*((unsigned long int *) 0x420C03B4))
#define GPIOPIN13OUT	(*((unsigned long int *) 0x420C01B4))

// PA14 is GPIOPIN14
#define GPIOPIN14	14
#define GPIOPIN14IN	(*((unsigned long int *) 0x420C03B8))
#define GPIOPIN14OUT	(*((unsigned long int *) 0x420C01B8))

// PA15 is GPIOPIN15
#define GPIOPIN15	15
#define GPIOPIN15IN	(*((unsigned long int *) 0x420C03BC))
#define GPIOPIN15OUT	(*((unsigned long int *) 0x420C01BC))

// PB0 is GPIOPIN16
#define GPIOPIN16	16
#define GPIOPIN16IN	(*((unsigned long int *) 0x420C0800))
#define GPIOPIN16OUT	(*((unsigned long int *) 0x420C0600))

// PB1 is GPIOPIN17
#define GPIOPIN17	17
#define GPIOPIN17IN	(*((unsigned long int *) 0x420C0804))
#define GPIOPIN17OUT	(*((unsigned long int *) 0x420C0604))

// PB2 is GPIOPIN18
#define GPIOPIN18	18
#define GPIOPIN18IN	(*((unsigned long int *) 0x420C0808))
#define GPIOPIN18OUT	(*((unsigned long int *) 0x420C0608))

// PB3 is GPIOPIN19
#define GPIOPIN19	19
#define GPIOPIN19IN	(*((unsigned long int *) 0x420C080C))
#define GPIOPIN19OUT	(*((unsigned long int *) 0x420C060C))

// PB4 is GPIOPIN20
#define GPIOPIN20	20
#define GPIOPIN20IN	(*((unsigned long int *) 0x420C0810))
#define GPIOPIN20OUT	(*((unsigned long int *) 0x420C0610))

// PB5 is GPIOPIN21
#define GPIOPIN21	21
#define GPIOPIN21IN	(*((unsigned long int *) 0x420C0814))
#define GPIOPIN21OUT	(*((unsigned long int *) 0x420C0614))

// PB6 is GPIOPIN22
#define GPIOPIN22	22
#define GPIOPIN22IN	(*((unsigned long int *) 0x420C0818))
#define GPIOPIN22OUT	(*((unsigned long int *) 0x420C0618))

// PB7 is GPIOPIN23
#define GPIOPIN23	23
#define GPIOPIN23IN	(*((unsigned long int *) 0x420C081C))
#define GPIOPIN23OUT	(*((unsigned long int *) 0x420C061C))

// PB8 is GPIOPIN24
#define GPIOPIN24	24
#define GPIOPIN24IN	(*((unsigned long int *) 0x420C0820))
#define GPIOPIN24OUT	(*((unsigned long int *) 0x420C0620))

// PB9 is GPIOPIN25
#define GPIOPIN25	25
#define GPIOPIN25IN	(*((unsigned long int *) 0x420C0824))
#define GPIOPIN25OUT	(*((unsigned long int *) 0x420C0624))

// PB10 is GPIOPIN26
#define GPIOPIN26	26
#define GPIOPIN26IN	(*((unsigned long int *) 0x420C0828))
#define GPIOPIN26OUT	(*((unsigned long int *) 0x420C0628))

// PB11 is GPIOPIN27
#define GPIOPIN27	27
#define GPIOPIN27IN	(*((unsigned long int *) 0x420C082C))
#define GPIOPIN27OUT	(*((unsigned long int *) 0x420C062C))

// PB12 is GPIOPIN28
#define GPIOPIN28	28
#define GPIOPIN28IN	(*((unsigned long int *) 0x420C0830))
#define GPIOPIN28OUT	(*((unsigned long int *) 0x420C0630))

// PB13 is GPIOPIN29
#define GPIOPIN29	29
#define GPIOPIN29IN	(*((unsigned long int *) 0x420C0834))
#define GPIOPIN29OUT	(*((unsigned long int *) 0x420C0634))

// PB14 is GPIOPIN30
#define GPIOPIN30	30
#define GPIOPIN30IN	(*((unsigned long int *) 0x420C0838))
#define GPIOPIN30OUT	(*((unsigned long int *) 0x420C0638))

// PB15 is GPIOPIN31
#define GPIOPIN31	31
#define GPIOPIN31IN	(*((unsigned long int *) 0x420C083C))
#define GPIOPIN31OUT	(*((unsigned long int *) 0x420C063C))

// PC0 is GPIOPIN32
#define GPIOPIN32	32
#define GPIOPIN32IN	(*((unsigned long int *) 0x420C0C80))
#define GPIOPIN32OUT	(*((unsigned long int *) 0x420C0A80))

// PC1 is GPIOPIN33
#define GPIOPIN33	33
#define GPIOPIN33IN	(*((unsigned long int *) 0x420C0C84))
#define GPIOPIN33OUT	(*((unsigned long int *) 0x420C0A84))

// PC2 is GPIOPIN34
#define GPIOPIN34	34
#define GPIOPIN34IN	(*((unsigned long int *) 0x420C0C88))
#define GPIOPIN34OUT	(*((unsigned long int *) 0x420C0A88))

// PC3 is GPIOPIN35
#define GPIOPIN35	35
#define GPIOPIN35IN	(*((unsigned long int *) 0x420C0C8C))
#define GPIOPIN35OUT	(*((unsigned long int *) 0x420C0A8C))

// PC4 is GPIOPIN36
#define GPIOPIN36	36
#define GPIOPIN36IN	(*((unsigned long int *) 0x420C0C90))
#define GPIOPIN36OUT	(*((unsigned long int *) 0x420C0A90))

// PC5 is GPIOPIN37
#define GPIOPIN37	37
#define GPIOPIN37IN	(*((unsigned long int *) 0x420C0C94))
#define GPIOPIN37OUT	(*((unsigned long int *) 0x420C0A94))

// PC6 is GPIOPIN38
#define GPIOPIN38	38
#define GPIOPIN38IN	(*((unsigned long int *) 0x420C0C98))
#define GPIOPIN38OUT	(*((unsigned long int *) 0x420C0A98))

// PC7 is GPIOPIN39
#define GPIOPIN39	39
#define GPIOPIN39IN	(*((unsigned long int *) 0x420C0C9C))
#define GPIOPIN39OUT	(*((unsigned long int *) 0x420C0A9C))

// PC8 is GPIOPIN40
#define GPIOPIN40	40
#define GPIOPIN40IN	(*((unsigned long int *) 0x420C0CA0))
#define GPIOPIN40OUT	(*((unsigned long int *) 0x420C0AA0))

// PC9 is GPIOPIN41
#define GPIOPIN41	41
#define GPIOPIN41IN	(*((unsigned long int *) 0x420C0CA4))
#define GPIOPIN41OUT	(*((unsigned long int *) 0x420C0AA4))

// PC10 is GPIOPIN42
#define GPIOPIN42	42
#define GPIOPIN42IN	(*((unsigned long int *) 0x420C0CA8))
#define GPIOPIN42OUT	(*((unsigned long int *) 0x420C0AA8))

// PC11 is GPIOPIN43
#define GPIOPIN43	43
#define GPIOPIN43IN	(*((unsigned long int *) 0x420C0CAC))
#define GPIOPIN43OUT	(*((unsigned long int *) 0x420C0AAC))

// PC12 is GPIOPIN44
#define GPIOPIN44	44
#define GPIOPIN44IN	(*((unsigned long int *) 0x420C0CB0))
#define GPIOPIN44OUT	(*((unsigned long int *) 0x420C0AB0))

// PC13 is GPIOPIN45
#define GPIOPIN45	45
#define GPIOPIN45IN	(*((unsigned long int *) 0x420C0CB4))
#define GPIOPIN45OUT	(*((unsigned long int *) 0x420C0AB4))

// PC14 is GPIOPIN46
#define GPIOPIN46	46
#define GPIOPIN46IN	(*((unsigned long int *) 0x420C0CB8))
#define GPIOPIN46OUT	(*((unsigned long int *) 0x420C0AB8))

// PC15 is GPIOPIN47
#define GPIOPIN47	47
#define GPIOPIN47IN	(*((unsigned long int *) 0x420C0CBC))
#define GPIOPIN47OUT	(*((unsigned long int *) 0x420C0ABC))

// PD0 is GPIOPIN48
#define GPIOPIN48	48
#define GPIOPIN48IN	(*((unsigned long int *) 0x420C1100))
#define GPIOPIN48OUT	(*((unsigned long int *) 0x420C0F00))

// PD1 is GPIOPIN49
#define GPIOPIN49	49
#define GPIOPIN49IN	(*((unsigned long int *) 0x420C1104))
#define GPIOPIN49OUT	(*((unsigned long int *) 0x420C0F04))

// PD2 is GPIOPIN50
#define GPIOPIN50	50
#define GPIOPIN50IN	(*((unsigned long int *) 0x420C1108))
#define GPIOPIN50OUT	(*((unsigned long int *) 0x420C0F08))

// PD3 is GPIOPIN51
#define GPIOPIN51	51
#define GPIOPIN51IN	(*((unsigned long int *) 0x420C110C))
#define GPIOPIN51OUT	(*((unsigned long int *) 0x420C0F0C))

// PD4 is GPIOPIN52
#define GPIOPIN52	52
#define GPIOPIN52IN	(*((unsigned long int *) 0x420C1110))
#define GPIOPIN52OUT	(*((unsigned long int *) 0x420C0F10))

// PD5 is GPIOPIN53
#define GPIOPIN53	53
#define GPIOPIN53IN	(*((unsigned long int *) 0x420C1114))
#define GPIOPIN53OUT	(*((unsigned long int *) 0x420C0F14))

// PD6 is GPIOPIN54
#define GPIOPIN54	54
#define GPIOPIN54IN	(*((unsigned long int *) 0x420C1118))
#define GPIOPIN54OUT	(*((unsigned long int *) 0x420C0F18))

// PD7 is GPIOPIN55
#define GPIOPIN55	55
#define GPIOPIN55IN	(*((unsigned long int *) 0x420C111C))
#define GPIOPIN55OUT	(*((unsigned long int *) 0x420C0F1C))

// PD8 is GPIOPIN56
#define GPIOPIN56	56
#define GPIOPIN56IN	(*((unsigned long int *) 0x420C1120))
#define GPIOPIN56OUT	(*((unsigned long int *) 0x420C0F20))

// PD9 is GPIOPIN57
#define GPIOPIN57	57
#define GPIOPIN57IN	(*((unsigned long int *) 0x420C1124))
#define GPIOPIN57OUT	(*((unsigned long int *) 0x420C0F24))

// PD10 is GPIOPIN58
#define GPIOPIN58	58
#define GPIOPIN58IN	(*((unsigned long int *) 0x420C1128))
#define GPIOPIN58OUT	(*((unsigned long int *) 0x420C0F28))

// PD11 is GPIOPIN59
#define GPIOPIN59	59
#define GPIOPIN59IN	(*((unsigned long int *) 0x420C112C))
#define GPIOPIN59OUT	(*((unsigned long int *) 0x420C0F2C))

// PD12 is GPIOPIN60
#define GPIOPIN60	60
#define GPIOPIN60IN	(*((unsigned long int *) 0x420C1130))
#define GPIOPIN60OUT	(*((unsigned long int *) 0x420C0F30))

// PD13 is GPIOPIN61
#define GPIOPIN61	61
#define GPIOPIN61IN	(*((unsigned long int *) 0x420C1134))
#define GPIOPIN61OUT	(*((unsigned long int *) 0x420C0F34))

// PD14 is GPIOPIN62
#define GPIOPIN62	62
#define GPIOPIN62IN	(*((unsigned long int *) 0x420C1138))
#define GPIOPIN62OUT	(*((unsigned long int *) 0x420C0F38))

// PD15 is GPIOPIN63
#define GPIOPIN63	63
#define GPIOPIN63IN	(*((unsigned long int *) 0x420C113C))
#define GPIOPIN63OUT	(*((unsigned long int *) 0x420C0F3C))

// PE0 is GPIOPIN64
#define GPIOPIN64	64
#define GPIOPIN64IN	(*((unsigned long int *) 0x420C1580))
#define GPIOPIN64OUT	(*((unsigned long int *) 0x420C1380))

// PE1 is GPIOPIN65
#define GPIOPIN65	65
#define GPIOPIN65IN	(*((unsigned long int *) 0x420C1584))
#define GPIOPIN65OUT	(*((unsigned long int *) 0x420C1384))

// PE2 is GPIOPIN66
#define GPIOPIN66	66
#define GPIOPIN66IN	(*((unsigned long int *) 0x420C1588))
#define GPIOPIN66OUT	(*((unsigned long int *) 0x420C1388))

// PE3 is GPIOPIN67
#define GPIOPIN67	67
#define GPIOPIN67IN	(*((unsigned long int *) 0x420C158C))
#define GPIOPIN67OUT	(*((unsigned long int *) 0x420C138C))

// PE4 is GPIOPIN68
#define GPIOPIN68	68
#define GPIOPIN68IN	(*((unsigned long int *) 0x420C1590))
#define GPIOPIN68OUT	(*((unsigned long int *) 0x420C1390))

// PE5 is GPIOPIN69
#define GPIOPIN69	69
#define GPIOPIN69IN	(*((unsigned long int *) 0x420C1594))
#define GPIOPIN69OUT	(*((unsigned long int *) 0x420C1394))

// PE6 is GPIOPIN70
#define GPIOPIN70	70
#define GPIOPIN70IN	(*((unsigned long int *) 0x420C1598))
#define GPIOPIN70OUT	(*((unsigned long int *) 0x420C1398))

// PE7 is GPIOPIN71
#define GPIOPIN71	71
#define GPIOPIN71IN	(*((unsigned long int *) 0x420C159C))
#define GPIOPIN71OUT	(*((unsigned long int *) 0x420C139C))

// PE8 is GPIOPIN72
#define GPIOPIN72	72
#define GPIOPIN72IN	(*((unsigned long int *) 0x420C15A0))
#define GPIOPIN72OUT	(*((unsigned long int *) 0x420C13A0))

// PE9 is GPIOPIN73
#define GPIOPIN73	73
#define GPIOPIN73IN	(*((unsigned long int *) 0x420C15A4))
#define GPIOPIN73OUT	(*((unsigned long int *) 0x420C13A4))

// PE10 is GPIOPIN74
#define GPIOPIN74	74
#define GPIOPIN74IN	(*((unsigned long int *) 0x420C15A8))
#define GPIOPIN74OUT	(*((unsigned long int *) 0x420C13A8))

// PE11 is GPIOPIN75
#define GPIOPIN75	75
#define GPIOPIN75IN	(*((unsigned long int *) 0x420C15AC))
#define GPIOPIN75OUT	(*((unsigned long int *) 0x420C13AC))

// PE12 is GPIOPIN76
#define GPIOPIN76	76
#define GPIOPIN76IN	(*((unsigned long int *) 0x420C15B0))
#define GPIOPIN76OUT	(*((unsigned long int *) 0x420C13B0))

// PE13 is GPIOPIN77
#define GPIOPIN77	77
#define GPIOPIN77IN	(*((unsigned long int *) 0x420C15B4))
#define GPIOPIN77OUT	(*((unsigned long int *) 0x420C13B4))

// PE14 is GPIOPIN78
#define GPIOPIN78	78
#define GPIOPIN78IN	(*((unsigned long int *) 0x420C15B8))
#define GPIOPIN78OUT	(*((unsigned long int *) 0x420C13B8))

// PE15 is GPIOPIN79
#define GPIOPIN79	79
#define GPIOPIN79IN	(*((unsigned long int *) 0x420C15BC))
#define GPIOPIN79OUT	(*((unsigned long int *) 0x420C13BC))

// PF0 is GPIOPIN80
#define GPIOPIN80	80
#define GPIOPIN80IN	(*((unsigned long int *) 0x420C1A00))
#define GPIOPIN80OUT	(*((unsigned long int *) 0x420C1800))

// PF1 is GPIOPIN81
#define GPIOPIN81	81
#define GPIOPIN81IN	(*((unsigned long int *) 0x420C1A04))
#define GPIOPIN81OUT	(*((unsigned long int *) 0x420C1804))

// PF2 is GPIOPIN82
#define GPIOPIN82	82
#define GPIOPIN82IN	(*((unsigned long int *) 0x420C1A08))
#define GPIOPIN82OUT	(*((unsigned long int *) 0x420C1808))

// PF3 is GPIOPIN83
#define GPIOPIN83	83
#define GPIOPIN83IN	(*((unsigned long int *) 0x420C1A0C))
#define GPIOPIN83OUT	(*((unsigned long int *) 0x420C180C))

// PF4 is GPIOPIN84
#define GPIOPIN84	84
#define GPIOPIN84IN	(*((unsigned long int *) 0x420C1A10))
#define GPIOPIN84OUT	(*((unsigned long int *) 0x420C1810))

// PF5 is GPIOPIN85
#define GPIOPIN85	85
#define GPIOPIN85IN	(*((unsigned long int *) 0x420C1A14))
#define GPIOPIN85OUT	(*((unsigned long int *) 0x420C1814))

// PF6 is GPIOPIN86
#define GPIOPIN86	86
#define GPIOPIN86IN	(*((unsigned long int *) 0x420C1A18))
#define GPIOPIN86OUT	(*((unsigned long int *) 0x420C1818))

// PF7 is GPIOPIN87
#define GPIOPIN87	87
#define GPIOPIN87IN	(*((unsigned long int *) 0x420C1A1C))
#define GPIOPIN87OUT	(*((unsigned long int *) 0x420C181C))

// PF8 is GPIOPIN88
#define GPIOPIN88	88
#define GPIOPIN88IN	(*((unsigned long int *) 0x420C1A20))
#define GPIOPIN88OUT	(*((unsigned long int *) 0x420C1820))

// PF9 is GPIOPIN89
#define GPIOPIN89	89
#define GPIOPIN89IN	(*((unsigned long int *) 0x420C1A24))
#define GPIOPIN89OUT	(*((unsigned long int *) 0x420C1824))

// PF10 is GPIOPIN90
#define GPIOPIN90	90
#define GPIOPIN90IN	(*((unsigned long int *) 0x420C1A28))
#define GPIOPIN90OUT	(*((unsigned long int *) 0x420C1828))

// PF11 is GPIOPIN91
#define GPIOPIN91	91
#define GPIOPIN91IN	(*((unsigned long int *) 0x420C1A2C))
#define GPIOPIN91OUT	(*((unsigned long int *) 0x420C182C))

// PF12 is GPIOPIN92
#define GPIOPIN92	92
#define GPIOPIN92IN	(*((unsigned long int *) 0x420C1A30))
#define GPIOPIN92OUT	(*((unsigned long int *) 0x420C1830))

// PF13 is GPIOPIN93
#define GPIOPIN93	93
#define GPIOPIN93IN	(*((unsigned long int *) 0x420C1A34))
#define GPIOPIN93OUT	(*((unsigned long int *) 0x420C1834))

// PF14 is GPIOPIN94
#define GPIOPIN94	94
#define GPIOPIN94IN	(*((unsigned long int *) 0x420C1A38))
#define GPIOPIN94OUT	(*((unsigned long int *) 0x420C1838))

// PF15 is GPIOPIN95
#define GPIOPIN95	95
#define GPIOPIN95IN	(*((unsigned long int *) 0x420C1A3C))
#define GPIOPIN95OUT	(*((unsigned long int *) 0x420C183C))

_END_STD_C
#endif
