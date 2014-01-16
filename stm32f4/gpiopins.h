/* Abstract bitwise GPIO services */

// $Id: gpiopins.h 3110 2011-10-06 13:25:49Z svn $

// Copyright (C)2013-2014, Philip Munts, President, Munts AM Corp.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
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

// These services provide a simple and efficient mechanism for software to
// control individual GPIO pins in an asynchronous fashion, where each GPIO pin
// is independent of any other.  This API is NOT suitable for situations where
// GPIO pins are grouped in buses

// GPIO pins are numbered sequentially from the least significant bit of the
// lowest GPIO port to the highest port and bit.  For example, if an MCU has
// two 8-bit GPIO ports, the GPIO pins would be numbered GPIO0 to GPIO15.

// Each GPIO pin has two macro defined for it: GPIOnIN and GPIOnOUT.  These
// map to Cortex-M4 bitband registers for the particular GPIO pin.  Sadly,
// some Cortex-M4 devices (such as the STM32F4) do not have a single
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
#define GPIOPIN0IN	(*((unsigned long int *) 0x42400200))
#define GPIOPIN0OUT	(*((unsigned long int *) 0x42400280))

// PA1 is GPIOPIN1
#define GPIOPIN1	1
#define GPIOPIN1IN	(*((unsigned long int *) 0x42400204))
#define GPIOPIN1OUT	(*((unsigned long int *) 0x42400284))

// PA2 is GPIOPIN2
#define GPIOPIN2	2
#define GPIOPIN2IN	(*((unsigned long int *) 0x42400208))
#define GPIOPIN2OUT	(*((unsigned long int *) 0x42400288))

// PA3 is GPIOPIN3
#define GPIOPIN3	3
#define GPIOPIN3IN	(*((unsigned long int *) 0x4240020C))
#define GPIOPIN3OUT	(*((unsigned long int *) 0x4240028C))

// PA4 is GPIOPIN4
#define GPIOPIN4	4
#define GPIOPIN4IN	(*((unsigned long int *) 0x42400210))
#define GPIOPIN4OUT	(*((unsigned long int *) 0x42400290))

// PA5 is GPIOPIN5
#define GPIOPIN5	5
#define GPIOPIN5IN	(*((unsigned long int *) 0x42400214))
#define GPIOPIN5OUT	(*((unsigned long int *) 0x42400294))

// PA6 is GPIOPIN6
#define GPIOPIN6	6
#define GPIOPIN6IN	(*((unsigned long int *) 0x42400218))
#define GPIOPIN6OUT	(*((unsigned long int *) 0x42400298))

// PA7 is GPIOPIN7
#define GPIOPIN7	7
#define GPIOPIN7IN	(*((unsigned long int *) 0x4240021C))
#define GPIOPIN7OUT	(*((unsigned long int *) 0x4240029C))

// PA8 is GPIOPIN8
#define GPIOPIN8	8
#define GPIOPIN8IN	(*((unsigned long int *) 0x42400220))
#define GPIOPIN8OUT	(*((unsigned long int *) 0x424002A0))

// PA9 is GPIOPIN9
#define GPIOPIN9	9
#define GPIOPIN9IN	(*((unsigned long int *) 0x42400224))
#define GPIOPIN9OUT	(*((unsigned long int *) 0x424002A4))

// PA10 is GPIOPIN10
#define GPIOPIN10	10
#define GPIOPIN10IN	(*((unsigned long int *) 0x42400228))
#define GPIOPIN10OUT	(*((unsigned long int *) 0x424002A8))

// PA11 is GPIOPIN11
#define GPIOPIN11	11
#define GPIOPIN11IN	(*((unsigned long int *) 0x4240022C))
#define GPIOPIN11OUT	(*((unsigned long int *) 0x424002AC))

// PA12 is GPIOPIN12
#define GPIOPIN12	12
#define GPIOPIN12IN	(*((unsigned long int *) 0x42400230))
#define GPIOPIN12OUT	(*((unsigned long int *) 0x424002B0))

// PA13 is GPIOPIN13
#define GPIOPIN13	13
#define GPIOPIN13IN	(*((unsigned long int *) 0x42400234))
#define GPIOPIN13OUT	(*((unsigned long int *) 0x424002B4))

// PA14 is GPIOPIN14
#define GPIOPIN14	14
#define GPIOPIN14IN	(*((unsigned long int *) 0x42400238))
#define GPIOPIN14OUT	(*((unsigned long int *) 0x424002B8))

// PA15 is GPIOPIN15
#define GPIOPIN15	15
#define GPIOPIN15IN	(*((unsigned long int *) 0x4240023C))
#define GPIOPIN15OUT	(*((unsigned long int *) 0x424002BC))

// PB0 is GPIOPIN16
#define GPIOPIN16	16
#define GPIOPIN16IN	(*((unsigned long int *) 0x42408200))
#define GPIOPIN16OUT	(*((unsigned long int *) 0x42408280))

// PB1 is GPIOPIN17
#define GPIOPIN17	17
#define GPIOPIN17IN	(*((unsigned long int *) 0x42408204))
#define GPIOPIN17OUT	(*((unsigned long int *) 0x42408284))

// PB2 is GPIOPIN18
#define GPIOPIN18	18
#define GPIOPIN18IN	(*((unsigned long int *) 0x42408208))
#define GPIOPIN18OUT	(*((unsigned long int *) 0x42408288))

// PB3 is GPIOPIN19
#define GPIOPIN19	19
#define GPIOPIN19IN	(*((unsigned long int *) 0x4240820C))
#define GPIOPIN19OUT	(*((unsigned long int *) 0x4240828C))

// PB4 is GPIOPIN20
#define GPIOPIN20	20
#define GPIOPIN20IN	(*((unsigned long int *) 0x42408210))
#define GPIOPIN20OUT	(*((unsigned long int *) 0x42408290))

// PB5 is GPIOPIN21
#define GPIOPIN21	21
#define GPIOPIN21IN	(*((unsigned long int *) 0x42408214))
#define GPIOPIN21OUT	(*((unsigned long int *) 0x42408294))

// PB6 is GPIOPIN22
#define GPIOPIN22	22
#define GPIOPIN22IN	(*((unsigned long int *) 0x42408218))
#define GPIOPIN22OUT	(*((unsigned long int *) 0x42408298))

// PB7 is GPIOPIN23
#define GPIOPIN23	23
#define GPIOPIN23IN	(*((unsigned long int *) 0x4240821C))
#define GPIOPIN23OUT	(*((unsigned long int *) 0x4240829C))

// PB8 is GPIOPIN24
#define GPIOPIN24	24
#define GPIOPIN24IN	(*((unsigned long int *) 0x42408220))
#define GPIOPIN24OUT	(*((unsigned long int *) 0x424082A0))

// PB9 is GPIOPIN25
#define GPIOPIN25	25
#define GPIOPIN25IN	(*((unsigned long int *) 0x42408224))
#define GPIOPIN25OUT	(*((unsigned long int *) 0x424082A4))

// PB10 is GPIOPIN26
#define GPIOPIN26	26
#define GPIOPIN26IN	(*((unsigned long int *) 0x42408228))
#define GPIOPIN26OUT	(*((unsigned long int *) 0x424082A8))

// PB11 is GPIOPIN27
#define GPIOPIN27	27
#define GPIOPIN27IN	(*((unsigned long int *) 0x4240822C))
#define GPIOPIN27OUT	(*((unsigned long int *) 0x424082AC))

// PB12 is GPIOPIN28
#define GPIOPIN28	28
#define GPIOPIN28IN	(*((unsigned long int *) 0x42408230))
#define GPIOPIN28OUT	(*((unsigned long int *) 0x424082B0))

// PB13 is GPIOPIN29
#define GPIOPIN29	29
#define GPIOPIN29IN	(*((unsigned long int *) 0x42408234))
#define GPIOPIN29OUT	(*((unsigned long int *) 0x424082B4))

// PB14 is GPIOPIN30
#define GPIOPIN30	30
#define GPIOPIN30IN	(*((unsigned long int *) 0x42408238))
#define GPIOPIN30OUT	(*((unsigned long int *) 0x424082B8))

// PB15 is GPIOPIN31
#define GPIOPIN31	31
#define GPIOPIN31IN	(*((unsigned long int *) 0x4240823C))
#define GPIOPIN31OUT	(*((unsigned long int *) 0x424082BC))

// PC0 is GPIOPIN32
#define GPIOPIN32	32
#define GPIOPIN32IN	(*((unsigned long int *) 0x42410200))
#define GPIOPIN32OUT	(*((unsigned long int *) 0x42410280))

// PC1 is GPIOPIN33
#define GPIOPIN33	33
#define GPIOPIN33IN	(*((unsigned long int *) 0x42410204))
#define GPIOPIN33OUT	(*((unsigned long int *) 0x42410284))

// PC2 is GPIOPIN34
#define GPIOPIN34	34
#define GPIOPIN34IN	(*((unsigned long int *) 0x42410208))
#define GPIOPIN34OUT	(*((unsigned long int *) 0x42410288))

// PC3 is GPIOPIN35
#define GPIOPIN35	35
#define GPIOPIN35IN	(*((unsigned long int *) 0x4241020C))
#define GPIOPIN35OUT	(*((unsigned long int *) 0x4241028C))

// PC4 is GPIOPIN36
#define GPIOPIN36	36
#define GPIOPIN36IN	(*((unsigned long int *) 0x42410210))
#define GPIOPIN36OUT	(*((unsigned long int *) 0x42410290))

// PC5 is GPIOPIN37
#define GPIOPIN37	37
#define GPIOPIN37IN	(*((unsigned long int *) 0x42410214))
#define GPIOPIN37OUT	(*((unsigned long int *) 0x42410294))

// PC6 is GPIOPIN38
#define GPIOPIN38	38
#define GPIOPIN38IN	(*((unsigned long int *) 0x42410218))
#define GPIOPIN38OUT	(*((unsigned long int *) 0x42410298))

// PC7 is GPIOPIN39
#define GPIOPIN39	39
#define GPIOPIN39IN	(*((unsigned long int *) 0x4241021C))
#define GPIOPIN39OUT	(*((unsigned long int *) 0x4241029C))

// PC8 is GPIOPIN40
#define GPIOPIN40	40
#define GPIOPIN40IN	(*((unsigned long int *) 0x42410220))
#define GPIOPIN40OUT	(*((unsigned long int *) 0x424102A0))

// PC9 is GPIOPIN41
#define GPIOPIN41	41
#define GPIOPIN41IN	(*((unsigned long int *) 0x42410224))
#define GPIOPIN41OUT	(*((unsigned long int *) 0x424102A4))

// PC10 is GPIOPIN42
#define GPIOPIN42	42
#define GPIOPIN42IN	(*((unsigned long int *) 0x42410228))
#define GPIOPIN42OUT	(*((unsigned long int *) 0x424102A8))

// PC11 is GPIOPIN43
#define GPIOPIN43	43
#define GPIOPIN43IN	(*((unsigned long int *) 0x4241022C))
#define GPIOPIN43OUT	(*((unsigned long int *) 0x424102AC))

// PC12 is GPIOPIN44
#define GPIOPIN44	44
#define GPIOPIN44IN	(*((unsigned long int *) 0x42410230))
#define GPIOPIN44OUT	(*((unsigned long int *) 0x424102B0))

// PC13 is GPIOPIN45
#define GPIOPIN45	45
#define GPIOPIN45IN	(*((unsigned long int *) 0x42410234))
#define GPIOPIN45OUT	(*((unsigned long int *) 0x424102B4))

// PC14 is GPIOPIN46
#define GPIOPIN46	46
#define GPIOPIN46IN	(*((unsigned long int *) 0x42410238))
#define GPIOPIN46OUT	(*((unsigned long int *) 0x424102B8))

// PC15 is GPIOPIN47
#define GPIOPIN47	47
#define GPIOPIN47IN	(*((unsigned long int *) 0x4241023C))
#define GPIOPIN47OUT	(*((unsigned long int *) 0x424102BC))

// PD0 is GPIOPIN48
#define GPIOPIN48	48
#define GPIOPIN48IN	(*((unsigned long int *) 0x42418200))
#define GPIOPIN48OUT	(*((unsigned long int *) 0x42418280))

// PD1 is GPIOPIN49
#define GPIOPIN49	49
#define GPIOPIN49IN	(*((unsigned long int *) 0x42418204))
#define GPIOPIN49OUT	(*((unsigned long int *) 0x42418284))

// PD2 is GPIOPIN50
#define GPIOPIN50	50
#define GPIOPIN50IN	(*((unsigned long int *) 0x42418208))
#define GPIOPIN50OUT	(*((unsigned long int *) 0x42418288))

// PD3 is GPIOPIN51
#define GPIOPIN51	51
#define GPIOPIN51IN	(*((unsigned long int *) 0x4241820C))
#define GPIOPIN51OUT	(*((unsigned long int *) 0x4241828C))

// PD4 is GPIOPIN52
#define GPIOPIN52	52
#define GPIOPIN52IN	(*((unsigned long int *) 0x42418210))
#define GPIOPIN52OUT	(*((unsigned long int *) 0x42418290))

// PD5 is GPIOPIN53
#define GPIOPIN53	53
#define GPIOPIN53IN	(*((unsigned long int *) 0x42418214))
#define GPIOPIN53OUT	(*((unsigned long int *) 0x42418294))

// PD6 is GPIOPIN54
#define GPIOPIN54	54
#define GPIOPIN54IN	(*((unsigned long int *) 0x42418218))
#define GPIOPIN54OUT	(*((unsigned long int *) 0x42418298))

// PD7 is GPIOPIN55
#define GPIOPIN55	55
#define GPIOPIN55IN	(*((unsigned long int *) 0x4241821C))
#define GPIOPIN55OUT	(*((unsigned long int *) 0x4241829C))

// PD8 is GPIOPIN56
#define GPIOPIN56	56
#define GPIOPIN56IN	(*((unsigned long int *) 0x42418220))
#define GPIOPIN56OUT	(*((unsigned long int *) 0x424182A0))

// PD9 is GPIOPIN57
#define GPIOPIN57	57
#define GPIOPIN57IN	(*((unsigned long int *) 0x42418224))
#define GPIOPIN57OUT	(*((unsigned long int *) 0x424182A4))

// PD10 is GPIOPIN58
#define GPIOPIN58	58
#define GPIOPIN58IN	(*((unsigned long int *) 0x42418228))
#define GPIOPIN58OUT	(*((unsigned long int *) 0x424182A8))

// PD11 is GPIOPIN59
#define GPIOPIN59	59
#define GPIOPIN59IN	(*((unsigned long int *) 0x4241822C))
#define GPIOPIN59OUT	(*((unsigned long int *) 0x424182AC))

// PD12 is GPIOPIN60
#define GPIOPIN60	60
#define GPIOPIN60IN	(*((unsigned long int *) 0x42418230))
#define GPIOPIN60OUT	(*((unsigned long int *) 0x424182B0))

// PD13 is GPIOPIN61
#define GPIOPIN61	61
#define GPIOPIN61IN	(*((unsigned long int *) 0x42418234))
#define GPIOPIN61OUT	(*((unsigned long int *) 0x424182B4))

// PD14 is GPIOPIN62
#define GPIOPIN62	62
#define GPIOPIN62IN	(*((unsigned long int *) 0x42418238))
#define GPIOPIN62OUT	(*((unsigned long int *) 0x424182B8))

// PD15 is GPIOPIN63
#define GPIOPIN63	63
#define GPIOPIN63IN	(*((unsigned long int *) 0x4241823C))
#define GPIOPIN63OUT	(*((unsigned long int *) 0x424182BC))

// PE0 is GPIOPIN64
#define GPIOPIN64	64
#define GPIOPIN64IN	(*((unsigned long int *) 0x42420200))
#define GPIOPIN64OUT	(*((unsigned long int *) 0x42420280))

// PE1 is GPIOPIN65
#define GPIOPIN65	65
#define GPIOPIN65IN	(*((unsigned long int *) 0x42420204))
#define GPIOPIN65OUT	(*((unsigned long int *) 0x42420284))

// PE2 is GPIOPIN66
#define GPIOPIN66	66
#define GPIOPIN66IN	(*((unsigned long int *) 0x42420208))
#define GPIOPIN66OUT	(*((unsigned long int *) 0x42420288))

// PE3 is GPIOPIN67
#define GPIOPIN67	67
#define GPIOPIN67IN	(*((unsigned long int *) 0x4242020C))
#define GPIOPIN67OUT	(*((unsigned long int *) 0x4242028C))

// PE4 is GPIOPIN68
#define GPIOPIN68	68
#define GPIOPIN68IN	(*((unsigned long int *) 0x42420210))
#define GPIOPIN68OUT	(*((unsigned long int *) 0x42420290))

// PE5 is GPIOPIN69
#define GPIOPIN69	69
#define GPIOPIN69IN	(*((unsigned long int *) 0x42420214))
#define GPIOPIN69OUT	(*((unsigned long int *) 0x42420294))

// PE6 is GPIOPIN70
#define GPIOPIN70	70
#define GPIOPIN70IN	(*((unsigned long int *) 0x42420218))
#define GPIOPIN70OUT	(*((unsigned long int *) 0x42420298))

// PE7 is GPIOPIN71
#define GPIOPIN71	71
#define GPIOPIN71IN	(*((unsigned long int *) 0x4242021C))
#define GPIOPIN71OUT	(*((unsigned long int *) 0x4242029C))

// PE8 is GPIOPIN72
#define GPIOPIN72	72
#define GPIOPIN72IN	(*((unsigned long int *) 0x42420220))
#define GPIOPIN72OUT	(*((unsigned long int *) 0x424202A0))

// PE9 is GPIOPIN73
#define GPIOPIN73	73
#define GPIOPIN73IN	(*((unsigned long int *) 0x42420224))
#define GPIOPIN73OUT	(*((unsigned long int *) 0x424202A4))

// PE10 is GPIOPIN74
#define GPIOPIN74	74
#define GPIOPIN74IN	(*((unsigned long int *) 0x42420228))
#define GPIOPIN74OUT	(*((unsigned long int *) 0x424202A8))

// PE11 is GPIOPIN75
#define GPIOPIN75	75
#define GPIOPIN75IN	(*((unsigned long int *) 0x4242022C))
#define GPIOPIN75OUT	(*((unsigned long int *) 0x424202AC))

// PE12 is GPIOPIN76
#define GPIOPIN76	76
#define GPIOPIN76IN	(*((unsigned long int *) 0x42420230))
#define GPIOPIN76OUT	(*((unsigned long int *) 0x424202B0))

// PE13 is GPIOPIN77
#define GPIOPIN77	77
#define GPIOPIN77IN	(*((unsigned long int *) 0x42420234))
#define GPIOPIN77OUT	(*((unsigned long int *) 0x424202B4))

// PE14 is GPIOPIN78
#define GPIOPIN78	78
#define GPIOPIN78IN	(*((unsigned long int *) 0x42420238))
#define GPIOPIN78OUT	(*((unsigned long int *) 0x424202B8))

// PE15 is GPIOPIN79
#define GPIOPIN79	79
#define GPIOPIN79IN	(*((unsigned long int *) 0x4242023C))
#define GPIOPIN79OUT	(*((unsigned long int *) 0x424202BC))

// PF0 is GPIOPIN80
#define GPIOPIN80	80
#define GPIOPIN80IN	(*((unsigned long int *) 0x42428200))
#define GPIOPIN80OUT	(*((unsigned long int *) 0x42428280))

// PF1 is GPIOPIN81
#define GPIOPIN81	81
#define GPIOPIN81IN	(*((unsigned long int *) 0x42428204))
#define GPIOPIN81OUT	(*((unsigned long int *) 0x42428284))

// PF2 is GPIOPIN82
#define GPIOPIN82	82
#define GPIOPIN82IN	(*((unsigned long int *) 0x42428208))
#define GPIOPIN82OUT	(*((unsigned long int *) 0x42428288))

// PF3 is GPIOPIN83
#define GPIOPIN83	83
#define GPIOPIN83IN	(*((unsigned long int *) 0x4242820C))
#define GPIOPIN83OUT	(*((unsigned long int *) 0x4242828C))

// PF4 is GPIOPIN84
#define GPIOPIN84	84
#define GPIOPIN84IN	(*((unsigned long int *) 0x42428210))
#define GPIOPIN84OUT	(*((unsigned long int *) 0x42428290))

// PF5 is GPIOPIN85
#define GPIOPIN85	85
#define GPIOPIN85IN	(*((unsigned long int *) 0x42428214))
#define GPIOPIN85OUT	(*((unsigned long int *) 0x42428294))

// PF6 is GPIOPIN86
#define GPIOPIN86	86
#define GPIOPIN86IN	(*((unsigned long int *) 0x42428218))
#define GPIOPIN86OUT	(*((unsigned long int *) 0x42428298))

// PF7 is GPIOPIN87
#define GPIOPIN87	87
#define GPIOPIN87IN	(*((unsigned long int *) 0x4242821C))
#define GPIOPIN87OUT	(*((unsigned long int *) 0x4242829C))

// PF8 is GPIOPIN88
#define GPIOPIN88	88
#define GPIOPIN88IN	(*((unsigned long int *) 0x42428220))
#define GPIOPIN88OUT	(*((unsigned long int *) 0x424282A0))

// PF9 is GPIOPIN89
#define GPIOPIN89	89
#define GPIOPIN89IN	(*((unsigned long int *) 0x42428224))
#define GPIOPIN89OUT	(*((unsigned long int *) 0x424282A4))

// PF10 is GPIOPIN90
#define GPIOPIN90	90
#define GPIOPIN90IN	(*((unsigned long int *) 0x42428228))
#define GPIOPIN90OUT	(*((unsigned long int *) 0x424282A8))

// PF11 is GPIOPIN91
#define GPIOPIN91	91
#define GPIOPIN91IN	(*((unsigned long int *) 0x4242822C))
#define GPIOPIN91OUT	(*((unsigned long int *) 0x424282AC))

// PF12 is GPIOPIN92
#define GPIOPIN92	92
#define GPIOPIN92IN	(*((unsigned long int *) 0x42428230))
#define GPIOPIN92OUT	(*((unsigned long int *) 0x424282B0))

// PF13 is GPIOPIN93
#define GPIOPIN93	93
#define GPIOPIN93IN	(*((unsigned long int *) 0x42428234))
#define GPIOPIN93OUT	(*((unsigned long int *) 0x424282B4))

// PF14 is GPIOPIN94
#define GPIOPIN94	94
#define GPIOPIN94IN	(*((unsigned long int *) 0x42428238))
#define GPIOPIN94OUT	(*((unsigned long int *) 0x424282B8))

// PF15 is GPIOPIN95
#define GPIOPIN95	95
#define GPIOPIN95IN	(*((unsigned long int *) 0x4242823C))
#define GPIOPIN95OUT	(*((unsigned long int *) 0x424282BC))

// PG0 is GPIOPIN96
#define GPIOPIN96	96
#define GPIOPIN96IN	(*((unsigned long int *) 0x42430200))
#define GPIOPIN96OUT	(*((unsigned long int *) 0x42430280))

// PG1 is GPIOPIN97
#define GPIOPIN97	97
#define GPIOPIN97IN	(*((unsigned long int *) 0x42430204))
#define GPIOPIN97OUT	(*((unsigned long int *) 0x42430284))

// PG2 is GPIOPIN98
#define GPIOPIN98	98
#define GPIOPIN98IN	(*((unsigned long int *) 0x42430208))
#define GPIOPIN98OUT	(*((unsigned long int *) 0x42430288))

// PG3 is GPIOPIN99
#define GPIOPIN99	99
#define GPIOPIN99IN	(*((unsigned long int *) 0x4243020C))
#define GPIOPIN99OUT	(*((unsigned long int *) 0x4243028C))

// PG4 is GPIOPIN100
#define GPIOPIN100	100
#define GPIOPIN100IN	(*((unsigned long int *) 0x42430210))
#define GPIOPIN100OUT	(*((unsigned long int *) 0x42430290))

// PG5 is GPIOPIN101
#define GPIOPIN101	101
#define GPIOPIN101IN	(*((unsigned long int *) 0x42430214))
#define GPIOPIN101OUT	(*((unsigned long int *) 0x42430294))

// PG6 is GPIOPIN102
#define GPIOPIN102	102
#define GPIOPIN102IN	(*((unsigned long int *) 0x42430218))
#define GPIOPIN102OUT	(*((unsigned long int *) 0x42430298))

// PG7 is GPIOPIN103
#define GPIOPIN103	103
#define GPIOPIN103IN	(*((unsigned long int *) 0x4243021C))
#define GPIOPIN103OUT	(*((unsigned long int *) 0x4243029C))

// PG8 is GPIOPIN104
#define GPIOPIN104	104
#define GPIOPIN104IN	(*((unsigned long int *) 0x42430220))
#define GPIOPIN104OUT	(*((unsigned long int *) 0x424302A0))

// PG9 is GPIOPIN105
#define GPIOPIN105	105
#define GPIOPIN105IN	(*((unsigned long int *) 0x42430224))
#define GPIOPIN105OUT	(*((unsigned long int *) 0x424302A4))

// PG10 is GPIOPIN106
#define GPIOPIN106	106
#define GPIOPIN106IN	(*((unsigned long int *) 0x42430228))
#define GPIOPIN106OUT	(*((unsigned long int *) 0x424302A8))

// PG11 is GPIOPIN107
#define GPIOPIN107	107
#define GPIOPIN107IN	(*((unsigned long int *) 0x4243022C))
#define GPIOPIN107OUT	(*((unsigned long int *) 0x424302AC))

// PG12 is GPIOPIN108
#define GPIOPIN108	108
#define GPIOPIN108IN	(*((unsigned long int *) 0x42430230))
#define GPIOPIN108OUT	(*((unsigned long int *) 0x424302B0))

// PG13 is GPIOPIN109
#define GPIOPIN109	109
#define GPIOPIN109IN	(*((unsigned long int *) 0x42430234))
#define GPIOPIN109OUT	(*((unsigned long int *) 0x424302B4))

// PG14 is GPIOPIN110
#define GPIOPIN110	110
#define GPIOPIN110IN	(*((unsigned long int *) 0x42430238))
#define GPIOPIN110OUT	(*((unsigned long int *) 0x424302B8))

// PG15 is GPIOPIN111
#define GPIOPIN111	111
#define GPIOPIN111IN	(*((unsigned long int *) 0x4243023C))
#define GPIOPIN111OUT	(*((unsigned long int *) 0x424302BC))

// PH0 is GPIOPIN112
#define GPIOPIN112	112
#define GPIOPIN112IN	(*((unsigned long int *) 0x42438200))
#define GPIOPIN112OUT	(*((unsigned long int *) 0x42438280))

// PH1 is GPIOPIN113
#define GPIOPIN113	113
#define GPIOPIN113IN	(*((unsigned long int *) 0x42438204))
#define GPIOPIN113OUT	(*((unsigned long int *) 0x42438284))

// PH2 is GPIOPIN114
#define GPIOPIN114	114
#define GPIOPIN114IN	(*((unsigned long int *) 0x42438208))
#define GPIOPIN114OUT	(*((unsigned long int *) 0x42438288))

// PH3 is GPIOPIN115
#define GPIOPIN115	115
#define GPIOPIN115IN	(*((unsigned long int *) 0x4243820C))
#define GPIOPIN115OUT	(*((unsigned long int *) 0x4243828C))

// PH4 is GPIOPIN116
#define GPIOPIN116	116
#define GPIOPIN116IN	(*((unsigned long int *) 0x42438210))
#define GPIOPIN116OUT	(*((unsigned long int *) 0x42438290))

// PH5 is GPIOPIN117
#define GPIOPIN117	117
#define GPIOPIN117IN	(*((unsigned long int *) 0x42438214))
#define GPIOPIN117OUT	(*((unsigned long int *) 0x42438294))

// PH6 is GPIOPIN118
#define GPIOPIN118	118
#define GPIOPIN118IN	(*((unsigned long int *) 0x42438218))
#define GPIOPIN118OUT	(*((unsigned long int *) 0x42438298))

// PH7 is GPIOPIN119
#define GPIOPIN119	119
#define GPIOPIN119IN	(*((unsigned long int *) 0x4243821C))
#define GPIOPIN119OUT	(*((unsigned long int *) 0x4243829C))

// PH8 is GPIOPIN120
#define GPIOPIN120	120
#define GPIOPIN120IN	(*((unsigned long int *) 0x42438220))
#define GPIOPIN120OUT	(*((unsigned long int *) 0x424382A0))

// PH9 is GPIOPIN121
#define GPIOPIN121	121
#define GPIOPIN121IN	(*((unsigned long int *) 0x42438224))
#define GPIOPIN121OUT	(*((unsigned long int *) 0x424382A4))

// PH10 is GPIOPIN122
#define GPIOPIN122	122
#define GPIOPIN122IN	(*((unsigned long int *) 0x42438228))
#define GPIOPIN122OUT	(*((unsigned long int *) 0x424382A8))

// PH11 is GPIOPIN123
#define GPIOPIN123	123
#define GPIOPIN123IN	(*((unsigned long int *) 0x4243822C))
#define GPIOPIN123OUT	(*((unsigned long int *) 0x424382AC))

// PH12 is GPIOPIN124
#define GPIOPIN124	124
#define GPIOPIN124IN	(*((unsigned long int *) 0x42438230))
#define GPIOPIN124OUT	(*((unsigned long int *) 0x424382B0))

// PH13 is GPIOPIN125
#define GPIOPIN125	125
#define GPIOPIN125IN	(*((unsigned long int *) 0x42438234))
#define GPIOPIN125OUT	(*((unsigned long int *) 0x424382B4))

// PH14 is GPIOPIN126
#define GPIOPIN126	126
#define GPIOPIN126IN	(*((unsigned long int *) 0x42438238))
#define GPIOPIN126OUT	(*((unsigned long int *) 0x424382B8))

// PH15 is GPIOPIN127
#define GPIOPIN127	127
#define GPIOPIN127IN	(*((unsigned long int *) 0x4243823C))
#define GPIOPIN127OUT	(*((unsigned long int *) 0x424382BC))

// PI0 is GPIOPIN128
#define GPIOPIN128	128
#define GPIOPIN128IN	(*((unsigned long int *) 0x42440200))
#define GPIOPIN128OUT	(*((unsigned long int *) 0x42440280))

// PI1 is GPIOPIN129
#define GPIOPIN129	129
#define GPIOPIN129IN	(*((unsigned long int *) 0x42440204))
#define GPIOPIN129OUT	(*((unsigned long int *) 0x42440284))

// PI2 is GPIOPIN130
#define GPIOPIN130	130
#define GPIOPIN130IN	(*((unsigned long int *) 0x42440208))
#define GPIOPIN130OUT	(*((unsigned long int *) 0x42440288))

// PI3 is GPIOPIN131
#define GPIOPIN131	131
#define GPIOPIN131IN	(*((unsigned long int *) 0x4244020C))
#define GPIOPIN131OUT	(*((unsigned long int *) 0x4244028C))

// PI4 is GPIOPIN132
#define GPIOPIN132	132
#define GPIOPIN132IN	(*((unsigned long int *) 0x42440210))
#define GPIOPIN132OUT	(*((unsigned long int *) 0x42440290))

// PI5 is GPIOPIN133
#define GPIOPIN133	133
#define GPIOPIN133IN	(*((unsigned long int *) 0x42440214))
#define GPIOPIN133OUT	(*((unsigned long int *) 0x42440294))

// PI6 is GPIOPIN134
#define GPIOPIN134	134
#define GPIOPIN134IN	(*((unsigned long int *) 0x42440218))
#define GPIOPIN134OUT	(*((unsigned long int *) 0x42440298))

// PI7 is GPIOPIN135
#define GPIOPIN135	135
#define GPIOPIN135IN	(*((unsigned long int *) 0x4244021C))
#define GPIOPIN135OUT	(*((unsigned long int *) 0x4244029C))

// PI8 is GPIOPIN136
#define GPIOPIN136	136
#define GPIOPIN136IN	(*((unsigned long int *) 0x42440220))
#define GPIOPIN136OUT	(*((unsigned long int *) 0x424402A0))

// PI9 is GPIOPIN137
#define GPIOPIN137	137
#define GPIOPIN137IN	(*((unsigned long int *) 0x42440224))
#define GPIOPIN137OUT	(*((unsigned long int *) 0x424402A4))

// PI10 is GPIOPIN138
#define GPIOPIN138	138
#define GPIOPIN138IN	(*((unsigned long int *) 0x42440228))
#define GPIOPIN138OUT	(*((unsigned long int *) 0x424402A8))

// PI11 is GPIOPIN139
#define GPIOPIN139	139
#define GPIOPIN139IN	(*((unsigned long int *) 0x4244022C))
#define GPIOPIN139OUT	(*((unsigned long int *) 0x424402AC))

// PI12 is GPIOPIN140
#define GPIOPIN140	140
#define GPIOPIN140IN	(*((unsigned long int *) 0x42440230))
#define GPIOPIN140OUT	(*((unsigned long int *) 0x424402B0))

// PI13 is GPIOPIN141
#define GPIOPIN141	141
#define GPIOPIN141IN	(*((unsigned long int *) 0x42440234))
#define GPIOPIN141OUT	(*((unsigned long int *) 0x424402B4))

// PI14 is GPIOPIN142
#define GPIOPIN142	142
#define GPIOPIN142IN	(*((unsigned long int *) 0x42440238))
#define GPIOPIN142OUT	(*((unsigned long int *) 0x424402B8))

// PI15 is GPIOPIN143
#define GPIOPIN143	143
#define GPIOPIN143IN	(*((unsigned long int *) 0x4244023C))
#define GPIOPIN143OUT	(*((unsigned long int *) 0x424402BC))

_END_STD_C
#endif
