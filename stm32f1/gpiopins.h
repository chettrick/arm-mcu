/* Abstract bitwise GPIO services */

// $Id$

// Copyright (C)2013, Philip Munts, President, Munts AM Corp.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// * Neither the name of Munts AM Corp. nor the names of its contributors may
//   be used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

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
#define GPIOPIN0IN	(*((unsigned long int *) 0x42210100))
#define GPIOPIN0OUT	(*((unsigned long int *) 0x42210180))

// PA1 is GPIOPIN1
#define GPIOPIN1	1
#define GPIOPIN1IN	(*((unsigned long int *) 0x42210104))
#define GPIOPIN1OUT	(*((unsigned long int *) 0x42210184))

// PA2 is GPIOPIN2
#define GPIOPIN2	2
#define GPIOPIN2IN	(*((unsigned long int *) 0x42210108))
#define GPIOPIN2OUT	(*((unsigned long int *) 0x42210188))

// PA3 is GPIOPIN3
#define GPIOPIN3	3
#define GPIOPIN3IN	(*((unsigned long int *) 0x4221010C))
#define GPIOPIN3OUT	(*((unsigned long int *) 0x4221018C))

// PA4 is GPIOPIN4
#define GPIOPIN4	4
#define GPIOPIN4IN	(*((unsigned long int *) 0x42210110))
#define GPIOPIN4OUT	(*((unsigned long int *) 0x42210190))

// PA5 is GPIOPIN5
#define GPIOPIN5	5
#define GPIOPIN5IN	(*((unsigned long int *) 0x42210114))
#define GPIOPIN5OUT	(*((unsigned long int *) 0x42210194))

// PA6 is GPIOPIN6
#define GPIOPIN6	6
#define GPIOPIN6IN	(*((unsigned long int *) 0x42210118))
#define GPIOPIN6OUT	(*((unsigned long int *) 0x42210198))

// PA7 is GPIOPIN7
#define GPIOPIN7	7
#define GPIOPIN7IN	(*((unsigned long int *) 0x4221011C))
#define GPIOPIN7OUT	(*((unsigned long int *) 0x4221019C))

// PA8 is GPIOPIN8
#define GPIOPIN8	8
#define GPIOPIN8IN	(*((unsigned long int *) 0x42210120))
#define GPIOPIN8OUT	(*((unsigned long int *) 0x422101A0))

// PA9 is GPIOPIN9
#define GPIOPIN9	9
#define GPIOPIN9IN	(*((unsigned long int *) 0x42210124))
#define GPIOPIN9OUT	(*((unsigned long int *) 0x422101A4))

// PA10 is GPIOPIN10
#define GPIOPIN10	10
#define GPIOPIN10IN	(*((unsigned long int *) 0x42210128))
#define GPIOPIN10OUT	(*((unsigned long int *) 0x422101A8))

// PA11 is GPIOPIN11
#define GPIOPIN11	11
#define GPIOPIN11IN	(*((unsigned long int *) 0x4221012C))
#define GPIOPIN11OUT	(*((unsigned long int *) 0x422101AC))

// PA12 is GPIOPIN12
#define GPIOPIN12	12
#define GPIOPIN12IN	(*((unsigned long int *) 0x42210130))
#define GPIOPIN12OUT	(*((unsigned long int *) 0x422101B0))

// PA13 is GPIOPIN13
#define GPIOPIN13	13
#define GPIOPIN13IN	(*((unsigned long int *) 0x42210134))
#define GPIOPIN13OUT	(*((unsigned long int *) 0x422101B4))

// PA14 is GPIOPIN14
#define GPIOPIN14	14
#define GPIOPIN14IN	(*((unsigned long int *) 0x42210138))
#define GPIOPIN14OUT	(*((unsigned long int *) 0x422101B8))

// PA15 is GPIOPIN15
#define GPIOPIN15	15
#define GPIOPIN15IN	(*((unsigned long int *) 0x4221013C))
#define GPIOPIN15OUT	(*((unsigned long int *) 0x422101BC))

// PB0 is GPIOPIN16
#define GPIOPIN16	16
#define GPIOPIN16IN	(*((unsigned long int *) 0x42218100))
#define GPIOPIN16OUT	(*((unsigned long int *) 0x42218180))

// PB1 is GPIOPIN17
#define GPIOPIN17	17
#define GPIOPIN17IN	(*((unsigned long int *) 0x42218104))
#define GPIOPIN17OUT	(*((unsigned long int *) 0x42218184))

// PB2 is GPIOPIN18
#define GPIOPIN18	18
#define GPIOPIN18IN	(*((unsigned long int *) 0x42218108))
#define GPIOPIN18OUT	(*((unsigned long int *) 0x42218188))

// PB3 is GPIOPIN19
#define GPIOPIN19	19
#define GPIOPIN19IN	(*((unsigned long int *) 0x4221810C))
#define GPIOPIN19OUT	(*((unsigned long int *) 0x4221818C))

// PB4 is GPIOPIN20
#define GPIOPIN20	20
#define GPIOPIN20IN	(*((unsigned long int *) 0x42218110))
#define GPIOPIN20OUT	(*((unsigned long int *) 0x42218190))

// PB5 is GPIOPIN21
#define GPIOPIN21	21
#define GPIOPIN21IN	(*((unsigned long int *) 0x42218114))
#define GPIOPIN21OUT	(*((unsigned long int *) 0x42218194))

// PB6 is GPIOPIN22
#define GPIOPIN22	22
#define GPIOPIN22IN	(*((unsigned long int *) 0x42218118))
#define GPIOPIN22OUT	(*((unsigned long int *) 0x42218198))

// PB7 is GPIOPIN23
#define GPIOPIN23	23
#define GPIOPIN23IN	(*((unsigned long int *) 0x4221811C))
#define GPIOPIN23OUT	(*((unsigned long int *) 0x4221819C))

// PB8 is GPIOPIN24
#define GPIOPIN24	24
#define GPIOPIN24IN	(*((unsigned long int *) 0x42218120))
#define GPIOPIN24OUT	(*((unsigned long int *) 0x422181A0))

// PB9 is GPIOPIN25
#define GPIOPIN25	25
#define GPIOPIN25IN	(*((unsigned long int *) 0x42218124))
#define GPIOPIN25OUT	(*((unsigned long int *) 0x422181A4))

// PB10 is GPIOPIN26
#define GPIOPIN26	26
#define GPIOPIN26IN	(*((unsigned long int *) 0x42218128))
#define GPIOPIN26OUT	(*((unsigned long int *) 0x422181A8))

// PB11 is GPIOPIN27
#define GPIOPIN27	27
#define GPIOPIN27IN	(*((unsigned long int *) 0x4221812C))
#define GPIOPIN27OUT	(*((unsigned long int *) 0x422181AC))

// PB12 is GPIOPIN28
#define GPIOPIN28	28
#define GPIOPIN28IN	(*((unsigned long int *) 0x42218130))
#define GPIOPIN28OUT	(*((unsigned long int *) 0x422181B0))

// PB13 is GPIOPIN29
#define GPIOPIN29	29
#define GPIOPIN29IN	(*((unsigned long int *) 0x42218134))
#define GPIOPIN29OUT	(*((unsigned long int *) 0x422181B4))

// PB14 is GPIOPIN30
#define GPIOPIN30	30
#define GPIOPIN30IN	(*((unsigned long int *) 0x42218138))
#define GPIOPIN30OUT	(*((unsigned long int *) 0x422181B8))

// PB15 is GPIOPIN31
#define GPIOPIN31	31
#define GPIOPIN31IN	(*((unsigned long int *) 0x4221813C))
#define GPIOPIN31OUT	(*((unsigned long int *) 0x422181BC))

// PC0 is GPIOPIN32
#define GPIOPIN32	32
#define GPIOPIN32IN	(*((unsigned long int *) 0x42220100))
#define GPIOPIN32OUT	(*((unsigned long int *) 0x42220180))

// PC1 is GPIOPIN33
#define GPIOPIN33	33
#define GPIOPIN33IN	(*((unsigned long int *) 0x42220104))
#define GPIOPIN33OUT	(*((unsigned long int *) 0x42220184))

// PC2 is GPIOPIN34
#define GPIOPIN34	34
#define GPIOPIN34IN	(*((unsigned long int *) 0x42220108))
#define GPIOPIN34OUT	(*((unsigned long int *) 0x42220188))

// PC3 is GPIOPIN35
#define GPIOPIN35	35
#define GPIOPIN35IN	(*((unsigned long int *) 0x4222010C))
#define GPIOPIN35OUT	(*((unsigned long int *) 0x4222018C))

// PC4 is GPIOPIN36
#define GPIOPIN36	36
#define GPIOPIN36IN	(*((unsigned long int *) 0x42220110))
#define GPIOPIN36OUT	(*((unsigned long int *) 0x42220190))

// PC5 is GPIOPIN37
#define GPIOPIN37	37
#define GPIOPIN37IN	(*((unsigned long int *) 0x42220114))
#define GPIOPIN37OUT	(*((unsigned long int *) 0x42220194))

// PC6 is GPIOPIN38
#define GPIOPIN38	38
#define GPIOPIN38IN	(*((unsigned long int *) 0x42220118))
#define GPIOPIN38OUT	(*((unsigned long int *) 0x42220198))

// PC7 is GPIOPIN39
#define GPIOPIN39	39
#define GPIOPIN39IN	(*((unsigned long int *) 0x4222011C))
#define GPIOPIN39OUT	(*((unsigned long int *) 0x4222019C))

// PC8 is GPIOPIN40
#define GPIOPIN40	40
#define GPIOPIN40IN	(*((unsigned long int *) 0x42220120))
#define GPIOPIN40OUT	(*((unsigned long int *) 0x422201A0))

// PC9 is GPIOPIN41
#define GPIOPIN41	41
#define GPIOPIN41IN	(*((unsigned long int *) 0x42220124))
#define GPIOPIN41OUT	(*((unsigned long int *) 0x422201A4))

// PC10 is GPIOPIN42
#define GPIOPIN42	42
#define GPIOPIN42IN	(*((unsigned long int *) 0x42220128))
#define GPIOPIN42OUT	(*((unsigned long int *) 0x422201A8))

// PC11 is GPIOPIN43
#define GPIOPIN43	43
#define GPIOPIN43IN	(*((unsigned long int *) 0x4222012C))
#define GPIOPIN43OUT	(*((unsigned long int *) 0x422201AC))

// PC12 is GPIOPIN44
#define GPIOPIN44	44
#define GPIOPIN44IN	(*((unsigned long int *) 0x42220130))
#define GPIOPIN44OUT	(*((unsigned long int *) 0x422201B0))

// PC13 is GPIOPIN45
#define GPIOPIN45	45
#define GPIOPIN45IN	(*((unsigned long int *) 0x42220134))
#define GPIOPIN45OUT	(*((unsigned long int *) 0x422201B4))

// PC14 is GPIOPIN46
#define GPIOPIN46	46
#define GPIOPIN46IN	(*((unsigned long int *) 0x42220138))
#define GPIOPIN46OUT	(*((unsigned long int *) 0x422201B8))

// PC15 is GPIOPIN47
#define GPIOPIN47	47
#define GPIOPIN47IN	(*((unsigned long int *) 0x4222013C))
#define GPIOPIN47OUT	(*((unsigned long int *) 0x422201BC))

// PD0 is GPIOPIN48
#define GPIOPIN48	48
#define GPIOPIN48IN	(*((unsigned long int *) 0x42228100))
#define GPIOPIN48OUT	(*((unsigned long int *) 0x42228180))

// PD1 is GPIOPIN49
#define GPIOPIN49	49
#define GPIOPIN49IN	(*((unsigned long int *) 0x42228104))
#define GPIOPIN49OUT	(*((unsigned long int *) 0x42228184))

// PD2 is GPIOPIN50
#define GPIOPIN50	50
#define GPIOPIN50IN	(*((unsigned long int *) 0x42228108))
#define GPIOPIN50OUT	(*((unsigned long int *) 0x42228188))

// PD3 is GPIOPIN51
#define GPIOPIN51	51
#define GPIOPIN51IN	(*((unsigned long int *) 0x4222810C))
#define GPIOPIN51OUT	(*((unsigned long int *) 0x4222818C))

// PD4 is GPIOPIN52
#define GPIOPIN52	52
#define GPIOPIN52IN	(*((unsigned long int *) 0x42228110))
#define GPIOPIN52OUT	(*((unsigned long int *) 0x42228190))

// PD5 is GPIOPIN53
#define GPIOPIN53	53
#define GPIOPIN53IN	(*((unsigned long int *) 0x42228114))
#define GPIOPIN53OUT	(*((unsigned long int *) 0x42228194))

// PD6 is GPIOPIN54
#define GPIOPIN54	54
#define GPIOPIN54IN	(*((unsigned long int *) 0x42228118))
#define GPIOPIN54OUT	(*((unsigned long int *) 0x42228198))

// PD7 is GPIOPIN55
#define GPIOPIN55	55
#define GPIOPIN55IN	(*((unsigned long int *) 0x4222811C))
#define GPIOPIN55OUT	(*((unsigned long int *) 0x4222819C))

// PD8 is GPIOPIN56
#define GPIOPIN56	56
#define GPIOPIN56IN	(*((unsigned long int *) 0x42228120))
#define GPIOPIN56OUT	(*((unsigned long int *) 0x422281A0))

// PD9 is GPIOPIN57
#define GPIOPIN57	57
#define GPIOPIN57IN	(*((unsigned long int *) 0x42228124))
#define GPIOPIN57OUT	(*((unsigned long int *) 0x422281A4))

// PD10 is GPIOPIN58
#define GPIOPIN58	58
#define GPIOPIN58IN	(*((unsigned long int *) 0x42228128))
#define GPIOPIN58OUT	(*((unsigned long int *) 0x422281A8))

// PD11 is GPIOPIN59
#define GPIOPIN59	59
#define GPIOPIN59IN	(*((unsigned long int *) 0x4222812C))
#define GPIOPIN59OUT	(*((unsigned long int *) 0x422281AC))

// PD12 is GPIOPIN60
#define GPIOPIN60	60
#define GPIOPIN60IN	(*((unsigned long int *) 0x42228130))
#define GPIOPIN60OUT	(*((unsigned long int *) 0x422281B0))

// PD13 is GPIOPIN61
#define GPIOPIN61	61
#define GPIOPIN61IN	(*((unsigned long int *) 0x42228134))
#define GPIOPIN61OUT	(*((unsigned long int *) 0x422281B4))

// PD14 is GPIOPIN62
#define GPIOPIN62	62
#define GPIOPIN62IN	(*((unsigned long int *) 0x42228138))
#define GPIOPIN62OUT	(*((unsigned long int *) 0x422281B8))

// PD15 is GPIOPIN63
#define GPIOPIN63	63
#define GPIOPIN63IN	(*((unsigned long int *) 0x4222813C))
#define GPIOPIN63OUT	(*((unsigned long int *) 0x422281BC))

// PE0 is GPIOPIN64
#define GPIOPIN64	64
#define GPIOPIN64IN	(*((unsigned long int *) 0x42230100))
#define GPIOPIN64OUT	(*((unsigned long int *) 0x42230180))

// PE1 is GPIOPIN65
#define GPIOPIN65	65
#define GPIOPIN65IN	(*((unsigned long int *) 0x42230104))
#define GPIOPIN65OUT	(*((unsigned long int *) 0x42230184))

// PE2 is GPIOPIN66
#define GPIOPIN66	66
#define GPIOPIN66IN	(*((unsigned long int *) 0x42230108))
#define GPIOPIN66OUT	(*((unsigned long int *) 0x42230188))

// PE3 is GPIOPIN67
#define GPIOPIN67	67
#define GPIOPIN67IN	(*((unsigned long int *) 0x4223010C))
#define GPIOPIN67OUT	(*((unsigned long int *) 0x4223018C))

// PE4 is GPIOPIN68
#define GPIOPIN68	68
#define GPIOPIN68IN	(*((unsigned long int *) 0x42230110))
#define GPIOPIN68OUT	(*((unsigned long int *) 0x42230190))

// PE5 is GPIOPIN69
#define GPIOPIN69	69
#define GPIOPIN69IN	(*((unsigned long int *) 0x42230114))
#define GPIOPIN69OUT	(*((unsigned long int *) 0x42230194))

// PE6 is GPIOPIN70
#define GPIOPIN70	70
#define GPIOPIN70IN	(*((unsigned long int *) 0x42230118))
#define GPIOPIN70OUT	(*((unsigned long int *) 0x42230198))

// PE7 is GPIOPIN71
#define GPIOPIN71	71
#define GPIOPIN71IN	(*((unsigned long int *) 0x4223011C))
#define GPIOPIN71OUT	(*((unsigned long int *) 0x4223019C))

// PE8 is GPIOPIN72
#define GPIOPIN72	72
#define GPIOPIN72IN	(*((unsigned long int *) 0x42230120))
#define GPIOPIN72OUT	(*((unsigned long int *) 0x422301A0))

// PE9 is GPIOPIN73
#define GPIOPIN73	73
#define GPIOPIN73IN	(*((unsigned long int *) 0x42230124))
#define GPIOPIN73OUT	(*((unsigned long int *) 0x422301A4))

// PE10 is GPIOPIN74
#define GPIOPIN74	74
#define GPIOPIN74IN	(*((unsigned long int *) 0x42230128))
#define GPIOPIN74OUT	(*((unsigned long int *) 0x422301A8))

// PE11 is GPIOPIN75
#define GPIOPIN75	75
#define GPIOPIN75IN	(*((unsigned long int *) 0x4223012C))
#define GPIOPIN75OUT	(*((unsigned long int *) 0x422301AC))

// PE12 is GPIOPIN76
#define GPIOPIN76	76
#define GPIOPIN76IN	(*((unsigned long int *) 0x42230130))
#define GPIOPIN76OUT	(*((unsigned long int *) 0x422301B0))

// PE13 is GPIOPIN77
#define GPIOPIN77	77
#define GPIOPIN77IN	(*((unsigned long int *) 0x42230134))
#define GPIOPIN77OUT	(*((unsigned long int *) 0x422301B4))

// PE14 is GPIOPIN78
#define GPIOPIN78	78
#define GPIOPIN78IN	(*((unsigned long int *) 0x42230138))
#define GPIOPIN78OUT	(*((unsigned long int *) 0x422301B8))

// PE15 is GPIOPIN79
#define GPIOPIN79	79
#define GPIOPIN79IN	(*((unsigned long int *) 0x4223013C))
#define GPIOPIN79OUT	(*((unsigned long int *) 0x422301BC))

// PF0 is GPIOPIN80
#define GPIOPIN80	80
#define GPIOPIN80IN	(*((unsigned long int *) 0x42238100))
#define GPIOPIN80OUT	(*((unsigned long int *) 0x42238180))

// PF1 is GPIOPIN81
#define GPIOPIN81	81
#define GPIOPIN81IN	(*((unsigned long int *) 0x42238104))
#define GPIOPIN81OUT	(*((unsigned long int *) 0x42238184))

// PF2 is GPIOPIN82
#define GPIOPIN82	82
#define GPIOPIN82IN	(*((unsigned long int *) 0x42238108))
#define GPIOPIN82OUT	(*((unsigned long int *) 0x42238188))

// PF3 is GPIOPIN83
#define GPIOPIN83	83
#define GPIOPIN83IN	(*((unsigned long int *) 0x4223810C))
#define GPIOPIN83OUT	(*((unsigned long int *) 0x4223818C))

// PF4 is GPIOPIN84
#define GPIOPIN84	84
#define GPIOPIN84IN	(*((unsigned long int *) 0x42238110))
#define GPIOPIN84OUT	(*((unsigned long int *) 0x42238190))

// PF5 is GPIOPIN85
#define GPIOPIN85	85
#define GPIOPIN85IN	(*((unsigned long int *) 0x42238114))
#define GPIOPIN85OUT	(*((unsigned long int *) 0x42238194))

// PF6 is GPIOPIN86
#define GPIOPIN86	86
#define GPIOPIN86IN	(*((unsigned long int *) 0x42238118))
#define GPIOPIN86OUT	(*((unsigned long int *) 0x42238198))

// PF7 is GPIOPIN87
#define GPIOPIN87	87
#define GPIOPIN87IN	(*((unsigned long int *) 0x4223811C))
#define GPIOPIN87OUT	(*((unsigned long int *) 0x4223819C))

// PF8 is GPIOPIN88
#define GPIOPIN88	88
#define GPIOPIN88IN	(*((unsigned long int *) 0x42238120))
#define GPIOPIN88OUT	(*((unsigned long int *) 0x422381A0))

// PF9 is GPIOPIN89
#define GPIOPIN89	89
#define GPIOPIN89IN	(*((unsigned long int *) 0x42238124))
#define GPIOPIN89OUT	(*((unsigned long int *) 0x422381A4))

// PF10 is GPIOPIN90
#define GPIOPIN90	90
#define GPIOPIN90IN	(*((unsigned long int *) 0x42238128))
#define GPIOPIN90OUT	(*((unsigned long int *) 0x422381A8))

// PF11 is GPIOPIN91
#define GPIOPIN91	91
#define GPIOPIN91IN	(*((unsigned long int *) 0x4223812C))
#define GPIOPIN91OUT	(*((unsigned long int *) 0x422381AC))

// PF12 is GPIOPIN92
#define GPIOPIN92	92
#define GPIOPIN92IN	(*((unsigned long int *) 0x42238130))
#define GPIOPIN92OUT	(*((unsigned long int *) 0x422381B0))

// PF13 is GPIOPIN93
#define GPIOPIN93	93
#define GPIOPIN93IN	(*((unsigned long int *) 0x42238134))
#define GPIOPIN93OUT	(*((unsigned long int *) 0x422381B4))

// PF14 is GPIOPIN94
#define GPIOPIN94	94
#define GPIOPIN94IN	(*((unsigned long int *) 0x42238138))
#define GPIOPIN94OUT	(*((unsigned long int *) 0x422381B8))

// PF15 is GPIOPIN95
#define GPIOPIN95	95
#define GPIOPIN95IN	(*((unsigned long int *) 0x4223813C))
#define GPIOPIN95OUT	(*((unsigned long int *) 0x422381BC))

// PG0 is GPIOPIN96
#define GPIOPIN96	96
#define GPIOPIN96IN	(*((unsigned long int *) 0x42240100))
#define GPIOPIN96OUT	(*((unsigned long int *) 0x42240180))

// PG1 is GPIOPIN97
#define GPIOPIN97	97
#define GPIOPIN97IN	(*((unsigned long int *) 0x42240104))
#define GPIOPIN97OUT	(*((unsigned long int *) 0x42240184))

// PG2 is GPIOPIN98
#define GPIOPIN98	98
#define GPIOPIN98IN	(*((unsigned long int *) 0x42240108))
#define GPIOPIN98OUT	(*((unsigned long int *) 0x42240188))

// PG3 is GPIOPIN99
#define GPIOPIN99	99
#define GPIOPIN99IN	(*((unsigned long int *) 0x4224010C))
#define GPIOPIN99OUT	(*((unsigned long int *) 0x4224018C))

// PG4 is GPIOPIN100
#define GPIOPIN100	100
#define GPIOPIN100IN	(*((unsigned long int *) 0x42240110))
#define GPIOPIN100OUT	(*((unsigned long int *) 0x42240190))

// PG5 is GPIOPIN101
#define GPIOPIN101	101
#define GPIOPIN101IN	(*((unsigned long int *) 0x42240114))
#define GPIOPIN101OUT	(*((unsigned long int *) 0x42240194))

// PG6 is GPIOPIN102
#define GPIOPIN102	102
#define GPIOPIN102IN	(*((unsigned long int *) 0x42240118))
#define GPIOPIN102OUT	(*((unsigned long int *) 0x42240198))

// PG7 is GPIOPIN103
#define GPIOPIN103	103
#define GPIOPIN103IN	(*((unsigned long int *) 0x4224011C))
#define GPIOPIN103OUT	(*((unsigned long int *) 0x4224019C))

// PG8 is GPIOPIN104
#define GPIOPIN104	104
#define GPIOPIN104IN	(*((unsigned long int *) 0x42240120))
#define GPIOPIN104OUT	(*((unsigned long int *) 0x422401A0))

// PG9 is GPIOPIN105
#define GPIOPIN105	105
#define GPIOPIN105IN	(*((unsigned long int *) 0x42240124))
#define GPIOPIN105OUT	(*((unsigned long int *) 0x422401A4))

// PG10 is GPIOPIN106
#define GPIOPIN106	106
#define GPIOPIN106IN	(*((unsigned long int *) 0x42240128))
#define GPIOPIN106OUT	(*((unsigned long int *) 0x422401A8))

// PG11 is GPIOPIN107
#define GPIOPIN107	107
#define GPIOPIN107IN	(*((unsigned long int *) 0x4224012C))
#define GPIOPIN107OUT	(*((unsigned long int *) 0x422401AC))

// PG12 is GPIOPIN108
#define GPIOPIN108	108
#define GPIOPIN108IN	(*((unsigned long int *) 0x42240130))
#define GPIOPIN108OUT	(*((unsigned long int *) 0x422401B0))

// PG13 is GPIOPIN109
#define GPIOPIN109	109
#define GPIOPIN109IN	(*((unsigned long int *) 0x42240134))
#define GPIOPIN109OUT	(*((unsigned long int *) 0x422401B4))

// PG14 is GPIOPIN110
#define GPIOPIN110	110
#define GPIOPIN110IN	(*((unsigned long int *) 0x42240138))
#define GPIOPIN110OUT	(*((unsigned long int *) 0x422401B8))

// PG15 is GPIOPIN111
#define GPIOPIN111	111
#define GPIOPIN111IN	(*((unsigned long int *) 0x4224013C))
#define GPIOPIN111OUT	(*((unsigned long int *) 0x422401BC))

_END_STD_C
#endif
