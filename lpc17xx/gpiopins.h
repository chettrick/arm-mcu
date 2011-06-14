/* Abstract bitwise GPIO services */

// $Id$

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

typedef enum
{
  GPIOPIN_INPUT,
  GPIOPIN_OUTPUT,
} gpiopin_direction_t;

int gpiopin_configure(unsigned int pin, gpiopin_direction_t direction);

#define GPIOPIN0	0
#define GPIOPIN0IN	(*((unsigned long int *) 0x23380280))
#define GPIOPIN0OUT	(*((unsigned long int *) 0x23380280))
#define GPIOPIN1	1
#define GPIOPIN1IN	(*((unsigned long int *) 0x23380284))
#define GPIOPIN1OUT	(*((unsigned long int *) 0x23380284))
#define GPIOPIN2	2
#define GPIOPIN2IN	(*((unsigned long int *) 0x23380288))
#define GPIOPIN2OUT	(*((unsigned long int *) 0x23380288))
#define GPIOPIN3	3
#define GPIOPIN3IN	(*((unsigned long int *) 0x2338028C))
#define GPIOPIN3OUT	(*((unsigned long int *) 0x2338028C))
#define GPIOPIN4	4
#define GPIOPIN4IN	(*((unsigned long int *) 0x23380290))
#define GPIOPIN4OUT	(*((unsigned long int *) 0x23380290))
#define GPIOPIN5	5
#define GPIOPIN5IN	(*((unsigned long int *) 0x23380294))
#define GPIOPIN5OUT	(*((unsigned long int *) 0x23380294))
#define GPIOPIN6	6
#define GPIOPIN6IN	(*((unsigned long int *) 0x23380298))
#define GPIOPIN6OUT	(*((unsigned long int *) 0x23380298))
#define GPIOPIN7	7
#define GPIOPIN7IN	(*((unsigned long int *) 0x2338029C))
#define GPIOPIN7OUT	(*((unsigned long int *) 0x2338029C))
#define GPIOPIN8	8
#define GPIOPIN8IN	(*((unsigned long int *) 0x233802A0))
#define GPIOPIN8OUT	(*((unsigned long int *) 0x233802A0))
#define GPIOPIN9	9
#define GPIOPIN9IN	(*((unsigned long int *) 0x233802A4))
#define GPIOPIN9OUT	(*((unsigned long int *) 0x233802A4))
#define GPIOPIN10	10
#define GPIOPIN10IN	(*((unsigned long int *) 0x233802A8))
#define GPIOPIN10OUT	(*((unsigned long int *) 0x233802A8))
#define GPIOPIN11	11
#define GPIOPIN11IN	(*((unsigned long int *) 0x233802AC))
#define GPIOPIN11OUT	(*((unsigned long int *) 0x233802AC))
#define GPIOPIN12	12
#define GPIOPIN12IN	(*((unsigned long int *) 0x233802B0))
#define GPIOPIN12OUT	(*((unsigned long int *) 0x233802B0))
#define GPIOPIN13	13
#define GPIOPIN13IN	(*((unsigned long int *) 0x233802B4))
#define GPIOPIN13OUT	(*((unsigned long int *) 0x233802B4))
#define GPIOPIN14	14
#define GPIOPIN14IN	(*((unsigned long int *) 0x233802B8))
#define GPIOPIN14OUT	(*((unsigned long int *) 0x233802B8))
#define GPIOPIN15	15
#define GPIOPIN15IN	(*((unsigned long int *) 0x233802BC))
#define GPIOPIN15OUT	(*((unsigned long int *) 0x233802BC))
#define GPIOPIN16	16
#define GPIOPIN16IN	(*((unsigned long int *) 0x233802C0))
#define GPIOPIN16OUT	(*((unsigned long int *) 0x233802C0))
#define GPIOPIN17	17
#define GPIOPIN17IN	(*((unsigned long int *) 0x233802C4))
#define GPIOPIN17OUT	(*((unsigned long int *) 0x233802C4))
#define GPIOPIN18	18
#define GPIOPIN18IN	(*((unsigned long int *) 0x233802C8))
#define GPIOPIN18OUT	(*((unsigned long int *) 0x233802C8))
#define GPIOPIN19	19
#define GPIOPIN19IN	(*((unsigned long int *) 0x233802CC))
#define GPIOPIN19OUT	(*((unsigned long int *) 0x233802CC))
#define GPIOPIN20	20
#define GPIOPIN20IN	(*((unsigned long int *) 0x233802D0))
#define GPIOPIN20OUT	(*((unsigned long int *) 0x233802D0))
#define GPIOPIN21	21
#define GPIOPIN21IN	(*((unsigned long int *) 0x233802D4))
#define GPIOPIN21OUT	(*((unsigned long int *) 0x233802D4))
#define GPIOPIN22	22
#define GPIOPIN22IN	(*((unsigned long int *) 0x233802D8))
#define GPIOPIN22OUT	(*((unsigned long int *) 0x233802D8))
#define GPIOPIN23	23
#define GPIOPIN23IN	(*((unsigned long int *) 0x233802DC))
#define GPIOPIN23OUT	(*((unsigned long int *) 0x233802DC))
#define GPIOPIN24	24
#define GPIOPIN24IN	(*((unsigned long int *) 0x233802E0))
#define GPIOPIN24OUT	(*((unsigned long int *) 0x233802E0))
#define GPIOPIN25	25
#define GPIOPIN25IN	(*((unsigned long int *) 0x233802E4))
#define GPIOPIN25OUT	(*((unsigned long int *) 0x233802E4))
#define GPIOPIN26	26
#define GPIOPIN26IN	(*((unsigned long int *) 0x233802E8))
#define GPIOPIN26OUT	(*((unsigned long int *) 0x233802E8))
#define GPIOPIN27	27
#define GPIOPIN27IN	(*((unsigned long int *) 0x233802EC))
#define GPIOPIN27OUT	(*((unsigned long int *) 0x233802EC))
#define GPIOPIN28	28
#define GPIOPIN28IN	(*((unsigned long int *) 0x233802F0))
#define GPIOPIN28OUT	(*((unsigned long int *) 0x233802F0))
#define GPIOPIN29	29
#define GPIOPIN29IN	(*((unsigned long int *) 0x233802F4))
#define GPIOPIN29OUT	(*((unsigned long int *) 0x233802F4))
#define GPIOPIN30	30
#define GPIOPIN30IN	(*((unsigned long int *) 0x233802F8))
#define GPIOPIN30OUT	(*((unsigned long int *) 0x233802F8))
#define GPIOPIN31	31
#define GPIOPIN31IN	(*((unsigned long int *) 0x233802FC))
#define GPIOPIN31OUT	(*((unsigned long int *) 0x233802FC))
#define GPIOPIN32	32
#define GPIOPIN32IN	(*((unsigned long int *) 0x23380680))
#define GPIOPIN32OUT	(*((unsigned long int *) 0x23380680))
#define GPIOPIN33	33
#define GPIOPIN33IN	(*((unsigned long int *) 0x23380684))
#define GPIOPIN33OUT	(*((unsigned long int *) 0x23380684))
#define GPIOPIN34	34
#define GPIOPIN34IN	(*((unsigned long int *) 0x23380688))
#define GPIOPIN34OUT	(*((unsigned long int *) 0x23380688))
#define GPIOPIN35	35
#define GPIOPIN35IN	(*((unsigned long int *) 0x2338068C))
#define GPIOPIN35OUT	(*((unsigned long int *) 0x2338068C))
#define GPIOPIN36	36
#define GPIOPIN36IN	(*((unsigned long int *) 0x23380690))
#define GPIOPIN36OUT	(*((unsigned long int *) 0x23380690))
#define GPIOPIN37	37
#define GPIOPIN37IN	(*((unsigned long int *) 0x23380694))
#define GPIOPIN37OUT	(*((unsigned long int *) 0x23380694))
#define GPIOPIN38	38
#define GPIOPIN38IN	(*((unsigned long int *) 0x23380698))
#define GPIOPIN38OUT	(*((unsigned long int *) 0x23380698))
#define GPIOPIN39	39
#define GPIOPIN39IN	(*((unsigned long int *) 0x2338069C))
#define GPIOPIN39OUT	(*((unsigned long int *) 0x2338069C))
#define GPIOPIN40	40
#define GPIOPIN40IN	(*((unsigned long int *) 0x233806A0))
#define GPIOPIN40OUT	(*((unsigned long int *) 0x233806A0))
#define GPIOPIN41	41
#define GPIOPIN41IN	(*((unsigned long int *) 0x233806A4))
#define GPIOPIN41OUT	(*((unsigned long int *) 0x233806A4))
#define GPIOPIN42	42
#define GPIOPIN42IN	(*((unsigned long int *) 0x233806A8))
#define GPIOPIN42OUT	(*((unsigned long int *) 0x233806A8))
#define GPIOPIN43	43
#define GPIOPIN43IN	(*((unsigned long int *) 0x233806AC))
#define GPIOPIN43OUT	(*((unsigned long int *) 0x233806AC))
#define GPIOPIN44	44
#define GPIOPIN44IN	(*((unsigned long int *) 0x233806B0))
#define GPIOPIN44OUT	(*((unsigned long int *) 0x233806B0))
#define GPIOPIN45	45
#define GPIOPIN45IN	(*((unsigned long int *) 0x233806B4))
#define GPIOPIN45OUT	(*((unsigned long int *) 0x233806B4))
#define GPIOPIN46	46
#define GPIOPIN46IN	(*((unsigned long int *) 0x233806B8))
#define GPIOPIN46OUT	(*((unsigned long int *) 0x233806B8))
#define GPIOPIN47	47
#define GPIOPIN47IN	(*((unsigned long int *) 0x233806BC))
#define GPIOPIN47OUT	(*((unsigned long int *) 0x233806BC))
#define GPIOPIN48	48
#define GPIOPIN48IN	(*((unsigned long int *) 0x233806C0))
#define GPIOPIN48OUT	(*((unsigned long int *) 0x233806C0))
#define GPIOPIN49	49
#define GPIOPIN49IN	(*((unsigned long int *) 0x233806C4))
#define GPIOPIN49OUT	(*((unsigned long int *) 0x233806C4))
#define GPIOPIN50	50
#define GPIOPIN50IN	(*((unsigned long int *) 0x233806C8))
#define GPIOPIN50OUT	(*((unsigned long int *) 0x233806C8))
#define GPIOPIN51	51
#define GPIOPIN51IN	(*((unsigned long int *) 0x233806CC))
#define GPIOPIN51OUT	(*((unsigned long int *) 0x233806CC))
#define GPIOPIN52	52
#define GPIOPIN52IN	(*((unsigned long int *) 0x233806D0))
#define GPIOPIN52OUT	(*((unsigned long int *) 0x233806D0))
#define GPIOPIN53	53
#define GPIOPIN53IN	(*((unsigned long int *) 0x233806D4))
#define GPIOPIN53OUT	(*((unsigned long int *) 0x233806D4))
#define GPIOPIN54	54
#define GPIOPIN54IN	(*((unsigned long int *) 0x233806D8))
#define GPIOPIN54OUT	(*((unsigned long int *) 0x233806D8))
#define GPIOPIN55	55
#define GPIOPIN55IN	(*((unsigned long int *) 0x233806DC))
#define GPIOPIN55OUT	(*((unsigned long int *) 0x233806DC))
#define GPIOPIN56	56
#define GPIOPIN56IN	(*((unsigned long int *) 0x233806E0))
#define GPIOPIN56OUT	(*((unsigned long int *) 0x233806E0))
#define GPIOPIN57	57
#define GPIOPIN57IN	(*((unsigned long int *) 0x233806E4))
#define GPIOPIN57OUT	(*((unsigned long int *) 0x233806E4))
#define GPIOPIN58	58
#define GPIOPIN58IN	(*((unsigned long int *) 0x233806E8))
#define GPIOPIN58OUT	(*((unsigned long int *) 0x233806E8))
#define GPIOPIN59	59
#define GPIOPIN59IN	(*((unsigned long int *) 0x233806EC))
#define GPIOPIN59OUT	(*((unsigned long int *) 0x233806EC))
#define GPIOPIN60	60
#define GPIOPIN60IN	(*((unsigned long int *) 0x233806F0))
#define GPIOPIN60OUT	(*((unsigned long int *) 0x233806F0))
#define GPIOPIN61	61
#define GPIOPIN61IN	(*((unsigned long int *) 0x233806F4))
#define GPIOPIN61OUT	(*((unsigned long int *) 0x233806F4))
#define GPIOPIN62	62
#define GPIOPIN62IN	(*((unsigned long int *) 0x233806F8))
#define GPIOPIN62OUT	(*((unsigned long int *) 0x233806F8))
#define GPIOPIN63	63
#define GPIOPIN63IN	(*((unsigned long int *) 0x233806FC))
#define GPIOPIN63OUT	(*((unsigned long int *) 0x233806FC))
#define GPIOPIN64	64
#define GPIOPIN64IN	(*((unsigned long int *) 0x23380A80))
#define GPIOPIN64OUT	(*((unsigned long int *) 0x23380A80))
#define GPIOPIN65	65
#define GPIOPIN65IN	(*((unsigned long int *) 0x23380A84))
#define GPIOPIN65OUT	(*((unsigned long int *) 0x23380A84))
#define GPIOPIN66	66
#define GPIOPIN66IN	(*((unsigned long int *) 0x23380A88))
#define GPIOPIN66OUT	(*((unsigned long int *) 0x23380A88))
#define GPIOPIN67	67
#define GPIOPIN67IN	(*((unsigned long int *) 0x23380A8C))
#define GPIOPIN67OUT	(*((unsigned long int *) 0x23380A8C))
#define GPIOPIN68	68
#define GPIOPIN68IN	(*((unsigned long int *) 0x23380A90))
#define GPIOPIN68OUT	(*((unsigned long int *) 0x23380A90))
#define GPIOPIN69	69
#define GPIOPIN69IN	(*((unsigned long int *) 0x23380A94))
#define GPIOPIN69OUT	(*((unsigned long int *) 0x23380A94))
#define GPIOPIN70	70
#define GPIOPIN70IN	(*((unsigned long int *) 0x23380A98))
#define GPIOPIN70OUT	(*((unsigned long int *) 0x23380A98))
#define GPIOPIN71	71
#define GPIOPIN71IN	(*((unsigned long int *) 0x23380A9C))
#define GPIOPIN71OUT	(*((unsigned long int *) 0x23380A9C))
#define GPIOPIN72	72
#define GPIOPIN72IN	(*((unsigned long int *) 0x23380AA0))
#define GPIOPIN72OUT	(*((unsigned long int *) 0x23380AA0))
#define GPIOPIN73	73
#define GPIOPIN73IN	(*((unsigned long int *) 0x23380AA4))
#define GPIOPIN73OUT	(*((unsigned long int *) 0x23380AA4))
#define GPIOPIN74	74
#define GPIOPIN74IN	(*((unsigned long int *) 0x23380AA8))
#define GPIOPIN74OUT	(*((unsigned long int *) 0x23380AA8))
#define GPIOPIN75	75
#define GPIOPIN75IN	(*((unsigned long int *) 0x23380AAC))
#define GPIOPIN75OUT	(*((unsigned long int *) 0x23380AAC))
#define GPIOPIN76	76
#define GPIOPIN76IN	(*((unsigned long int *) 0x23380AB0))
#define GPIOPIN76OUT	(*((unsigned long int *) 0x23380AB0))
#define GPIOPIN77	77
#define GPIOPIN77IN	(*((unsigned long int *) 0x23380AB4))
#define GPIOPIN77OUT	(*((unsigned long int *) 0x23380AB4))
#define GPIOPIN78	78
#define GPIOPIN78IN	(*((unsigned long int *) 0x23380AB8))
#define GPIOPIN78OUT	(*((unsigned long int *) 0x23380AB8))
#define GPIOPIN79	79
#define GPIOPIN79IN	(*((unsigned long int *) 0x23380ABC))
#define GPIOPIN79OUT	(*((unsigned long int *) 0x23380ABC))
#define GPIOPIN80	80
#define GPIOPIN80IN	(*((unsigned long int *) 0x23380AC0))
#define GPIOPIN80OUT	(*((unsigned long int *) 0x23380AC0))
#define GPIOPIN81	81
#define GPIOPIN81IN	(*((unsigned long int *) 0x23380AC4))
#define GPIOPIN81OUT	(*((unsigned long int *) 0x23380AC4))
#define GPIOPIN82	82
#define GPIOPIN82IN	(*((unsigned long int *) 0x23380AC8))
#define GPIOPIN82OUT	(*((unsigned long int *) 0x23380AC8))
#define GPIOPIN83	83
#define GPIOPIN83IN	(*((unsigned long int *) 0x23380ACC))
#define GPIOPIN83OUT	(*((unsigned long int *) 0x23380ACC))
#define GPIOPIN84	84
#define GPIOPIN84IN	(*((unsigned long int *) 0x23380AD0))
#define GPIOPIN84OUT	(*((unsigned long int *) 0x23380AD0))
#define GPIOPIN85	85
#define GPIOPIN85IN	(*((unsigned long int *) 0x23380AD4))
#define GPIOPIN85OUT	(*((unsigned long int *) 0x23380AD4))
#define GPIOPIN86	86
#define GPIOPIN86IN	(*((unsigned long int *) 0x23380AD8))
#define GPIOPIN86OUT	(*((unsigned long int *) 0x23380AD8))
#define GPIOPIN87	87
#define GPIOPIN87IN	(*((unsigned long int *) 0x23380ADC))
#define GPIOPIN87OUT	(*((unsigned long int *) 0x23380ADC))
#define GPIOPIN88	88
#define GPIOPIN88IN	(*((unsigned long int *) 0x23380AE0))
#define GPIOPIN88OUT	(*((unsigned long int *) 0x23380AE0))
#define GPIOPIN89	89
#define GPIOPIN89IN	(*((unsigned long int *) 0x23380AE4))
#define GPIOPIN89OUT	(*((unsigned long int *) 0x23380AE4))
#define GPIOPIN90	90
#define GPIOPIN90IN	(*((unsigned long int *) 0x23380AE8))
#define GPIOPIN90OUT	(*((unsigned long int *) 0x23380AE8))
#define GPIOPIN91	91
#define GPIOPIN91IN	(*((unsigned long int *) 0x23380AEC))
#define GPIOPIN91OUT	(*((unsigned long int *) 0x23380AEC))
#define GPIOPIN92	92
#define GPIOPIN92IN	(*((unsigned long int *) 0x23380AF0))
#define GPIOPIN92OUT	(*((unsigned long int *) 0x23380AF0))
#define GPIOPIN93	93
#define GPIOPIN93IN	(*((unsigned long int *) 0x23380AF4))
#define GPIOPIN93OUT	(*((unsigned long int *) 0x23380AF4))
#define GPIOPIN94	94
#define GPIOPIN94IN	(*((unsigned long int *) 0x23380AF8))
#define GPIOPIN94OUT	(*((unsigned long int *) 0x23380AF8))
#define GPIOPIN95	95
#define GPIOPIN95IN	(*((unsigned long int *) 0x23380AFC))
#define GPIOPIN95OUT	(*((unsigned long int *) 0x23380AFC))
#define GPIOPIN96	96
#define GPIOPIN96IN	(*((unsigned long int *) 0x23380E80))
#define GPIOPIN96OUT	(*((unsigned long int *) 0x23380E80))
#define GPIOPIN97	97
#define GPIOPIN97IN	(*((unsigned long int *) 0x23380E84))
#define GPIOPIN97OUT	(*((unsigned long int *) 0x23380E84))
#define GPIOPIN98	98
#define GPIOPIN98IN	(*((unsigned long int *) 0x23380E88))
#define GPIOPIN98OUT	(*((unsigned long int *) 0x23380E88))
#define GPIOPIN99	99
#define GPIOPIN99IN	(*((unsigned long int *) 0x23380E8C))
#define GPIOPIN99OUT	(*((unsigned long int *) 0x23380E8C))
#define GPIOPIN100	100
#define GPIOPIN100IN	(*((unsigned long int *) 0x23380E90))
#define GPIOPIN100OUT	(*((unsigned long int *) 0x23380E90))
#define GPIOPIN101	101
#define GPIOPIN101IN	(*((unsigned long int *) 0x23380E94))
#define GPIOPIN101OUT	(*((unsigned long int *) 0x23380E94))
#define GPIOPIN102	102
#define GPIOPIN102IN	(*((unsigned long int *) 0x23380E98))
#define GPIOPIN102OUT	(*((unsigned long int *) 0x23380E98))
#define GPIOPIN103	103
#define GPIOPIN103IN	(*((unsigned long int *) 0x23380E9C))
#define GPIOPIN103OUT	(*((unsigned long int *) 0x23380E9C))
#define GPIOPIN104	104
#define GPIOPIN104IN	(*((unsigned long int *) 0x23380EA0))
#define GPIOPIN104OUT	(*((unsigned long int *) 0x23380EA0))
#define GPIOPIN105	105
#define GPIOPIN105IN	(*((unsigned long int *) 0x23380EA4))
#define GPIOPIN105OUT	(*((unsigned long int *) 0x23380EA4))
#define GPIOPIN106	106
#define GPIOPIN106IN	(*((unsigned long int *) 0x23380EA8))
#define GPIOPIN106OUT	(*((unsigned long int *) 0x23380EA8))
#define GPIOPIN107	107
#define GPIOPIN107IN	(*((unsigned long int *) 0x23380EAC))
#define GPIOPIN107OUT	(*((unsigned long int *) 0x23380EAC))
#define GPIOPIN108	108
#define GPIOPIN108IN	(*((unsigned long int *) 0x23380EB0))
#define GPIOPIN108OUT	(*((unsigned long int *) 0x23380EB0))
#define GPIOPIN109	109
#define GPIOPIN109IN	(*((unsigned long int *) 0x23380EB4))
#define GPIOPIN109OUT	(*((unsigned long int *) 0x23380EB4))
#define GPIOPIN110	110
#define GPIOPIN110IN	(*((unsigned long int *) 0x23380EB8))
#define GPIOPIN110OUT	(*((unsigned long int *) 0x23380EB8))
#define GPIOPIN111	111
#define GPIOPIN111IN	(*((unsigned long int *) 0x23380EBC))
#define GPIOPIN111OUT	(*((unsigned long int *) 0x23380EBC))
#define GPIOPIN112	112
#define GPIOPIN112IN	(*((unsigned long int *) 0x23380EC0))
#define GPIOPIN112OUT	(*((unsigned long int *) 0x23380EC0))
#define GPIOPIN113	113
#define GPIOPIN113IN	(*((unsigned long int *) 0x23380EC4))
#define GPIOPIN113OUT	(*((unsigned long int *) 0x23380EC4))
#define GPIOPIN114	114
#define GPIOPIN114IN	(*((unsigned long int *) 0x23380EC8))
#define GPIOPIN114OUT	(*((unsigned long int *) 0x23380EC8))
#define GPIOPIN115	115
#define GPIOPIN115IN	(*((unsigned long int *) 0x23380ECC))
#define GPIOPIN115OUT	(*((unsigned long int *) 0x23380ECC))
#define GPIOPIN116	116
#define GPIOPIN116IN	(*((unsigned long int *) 0x23380ED0))
#define GPIOPIN116OUT	(*((unsigned long int *) 0x23380ED0))
#define GPIOPIN117	117
#define GPIOPIN117IN	(*((unsigned long int *) 0x23380ED4))
#define GPIOPIN117OUT	(*((unsigned long int *) 0x23380ED4))
#define GPIOPIN118	118
#define GPIOPIN118IN	(*((unsigned long int *) 0x23380ED8))
#define GPIOPIN118OUT	(*((unsigned long int *) 0x23380ED8))
#define GPIOPIN119	119
#define GPIOPIN119IN	(*((unsigned long int *) 0x23380EDC))
#define GPIOPIN119OUT	(*((unsigned long int *) 0x23380EDC))
#define GPIOPIN120	120
#define GPIOPIN120IN	(*((unsigned long int *) 0x23380EE0))
#define GPIOPIN120OUT	(*((unsigned long int *) 0x23380EE0))
#define GPIOPIN121	121
#define GPIOPIN121IN	(*((unsigned long int *) 0x23380EE4))
#define GPIOPIN121OUT	(*((unsigned long int *) 0x23380EE4))
#define GPIOPIN122	122
#define GPIOPIN122IN	(*((unsigned long int *) 0x23380EE8))
#define GPIOPIN122OUT	(*((unsigned long int *) 0x23380EE8))
#define GPIOPIN123	123
#define GPIOPIN123IN	(*((unsigned long int *) 0x23380EEC))
#define GPIOPIN123OUT	(*((unsigned long int *) 0x23380EEC))
#define GPIOPIN124	124
#define GPIOPIN124IN	(*((unsigned long int *) 0x23380EF0))
#define GPIOPIN124OUT	(*((unsigned long int *) 0x23380EF0))
#define GPIOPIN125	125
#define GPIOPIN125IN	(*((unsigned long int *) 0x23380EF4))
#define GPIOPIN125OUT	(*((unsigned long int *) 0x23380EF4))
#define GPIOPIN126	126
#define GPIOPIN126IN	(*((unsigned long int *) 0x23380EF8))
#define GPIOPIN126OUT	(*((unsigned long int *) 0x23380EF8))
#define GPIOPIN127	127
#define GPIOPIN127IN	(*((unsigned long int *) 0x23380EFC))
#define GPIOPIN127OUT	(*((unsigned long int *) 0x23380EFC))
#define GPIOPIN128	128
#define GPIOPIN128IN	(*((unsigned long int *) 0x23381280))
#define GPIOPIN128OUT	(*((unsigned long int *) 0x23381280))
#define GPIOPIN129	129
#define GPIOPIN129IN	(*((unsigned long int *) 0x23381284))
#define GPIOPIN129OUT	(*((unsigned long int *) 0x23381284))
#define GPIOPIN130	130
#define GPIOPIN130IN	(*((unsigned long int *) 0x23381288))
#define GPIOPIN130OUT	(*((unsigned long int *) 0x23381288))
#define GPIOPIN131	131
#define GPIOPIN131IN	(*((unsigned long int *) 0x2338128C))
#define GPIOPIN131OUT	(*((unsigned long int *) 0x2338128C))
#define GPIOPIN132	132
#define GPIOPIN132IN	(*((unsigned long int *) 0x23381290))
#define GPIOPIN132OUT	(*((unsigned long int *) 0x23381290))
#define GPIOPIN133	133
#define GPIOPIN133IN	(*((unsigned long int *) 0x23381294))
#define GPIOPIN133OUT	(*((unsigned long int *) 0x23381294))
#define GPIOPIN134	134
#define GPIOPIN134IN	(*((unsigned long int *) 0x23381298))
#define GPIOPIN134OUT	(*((unsigned long int *) 0x23381298))
#define GPIOPIN135	135
#define GPIOPIN135IN	(*((unsigned long int *) 0x2338129C))
#define GPIOPIN135OUT	(*((unsigned long int *) 0x2338129C))
#define GPIOPIN136	136
#define GPIOPIN136IN	(*((unsigned long int *) 0x233812A0))
#define GPIOPIN136OUT	(*((unsigned long int *) 0x233812A0))
#define GPIOPIN137	137
#define GPIOPIN137IN	(*((unsigned long int *) 0x233812A4))
#define GPIOPIN137OUT	(*((unsigned long int *) 0x233812A4))
#define GPIOPIN138	138
#define GPIOPIN138IN	(*((unsigned long int *) 0x233812A8))
#define GPIOPIN138OUT	(*((unsigned long int *) 0x233812A8))
#define GPIOPIN139	139
#define GPIOPIN139IN	(*((unsigned long int *) 0x233812AC))
#define GPIOPIN139OUT	(*((unsigned long int *) 0x233812AC))
#define GPIOPIN140	140
#define GPIOPIN140IN	(*((unsigned long int *) 0x233812B0))
#define GPIOPIN140OUT	(*((unsigned long int *) 0x233812B0))
#define GPIOPIN141	141
#define GPIOPIN141IN	(*((unsigned long int *) 0x233812B4))
#define GPIOPIN141OUT	(*((unsigned long int *) 0x233812B4))
#define GPIOPIN142	142
#define GPIOPIN142IN	(*((unsigned long int *) 0x233812B8))
#define GPIOPIN142OUT	(*((unsigned long int *) 0x233812B8))
#define GPIOPIN143	143
#define GPIOPIN143IN	(*((unsigned long int *) 0x233812BC))
#define GPIOPIN143OUT	(*((unsigned long int *) 0x233812BC))
#define GPIOPIN144	144
#define GPIOPIN144IN	(*((unsigned long int *) 0x233812C0))
#define GPIOPIN144OUT	(*((unsigned long int *) 0x233812C0))
#define GPIOPIN145	145
#define GPIOPIN145IN	(*((unsigned long int *) 0x233812C4))
#define GPIOPIN145OUT	(*((unsigned long int *) 0x233812C4))
#define GPIOPIN146	146
#define GPIOPIN146IN	(*((unsigned long int *) 0x233812C8))
#define GPIOPIN146OUT	(*((unsigned long int *) 0x233812C8))
#define GPIOPIN147	147
#define GPIOPIN147IN	(*((unsigned long int *) 0x233812CC))
#define GPIOPIN147OUT	(*((unsigned long int *) 0x233812CC))
#define GPIOPIN148	148
#define GPIOPIN148IN	(*((unsigned long int *) 0x233812D0))
#define GPIOPIN148OUT	(*((unsigned long int *) 0x233812D0))
#define GPIOPIN149	149
#define GPIOPIN149IN	(*((unsigned long int *) 0x233812D4))
#define GPIOPIN149OUT	(*((unsigned long int *) 0x233812D4))
#define GPIOPIN150	150
#define GPIOPIN150IN	(*((unsigned long int *) 0x233812D8))
#define GPIOPIN150OUT	(*((unsigned long int *) 0x233812D8))
#define GPIOPIN151	151
#define GPIOPIN151IN	(*((unsigned long int *) 0x233812DC))
#define GPIOPIN151OUT	(*((unsigned long int *) 0x233812DC))
#define GPIOPIN152	152
#define GPIOPIN152IN	(*((unsigned long int *) 0x233812E0))
#define GPIOPIN152OUT	(*((unsigned long int *) 0x233812E0))
#define GPIOPIN153	153
#define GPIOPIN153IN	(*((unsigned long int *) 0x233812E4))
#define GPIOPIN153OUT	(*((unsigned long int *) 0x233812E4))
#define GPIOPIN154	154
#define GPIOPIN154IN	(*((unsigned long int *) 0x233812E8))
#define GPIOPIN154OUT	(*((unsigned long int *) 0x233812E8))
#define GPIOPIN155	155
#define GPIOPIN155IN	(*((unsigned long int *) 0x233812EC))
#define GPIOPIN155OUT	(*((unsigned long int *) 0x233812EC))
#define GPIOPIN156	156
#define GPIOPIN156IN	(*((unsigned long int *) 0x233812F0))
#define GPIOPIN156OUT	(*((unsigned long int *) 0x233812F0))
#define GPIOPIN157	157
#define GPIOPIN157IN	(*((unsigned long int *) 0x233812F4))
#define GPIOPIN157OUT	(*((unsigned long int *) 0x233812F4))
#define GPIOPIN158	158
#define GPIOPIN158IN	(*((unsigned long int *) 0x233812F8))
#define GPIOPIN158OUT	(*((unsigned long int *) 0x233812F8))
#define GPIOPIN159	159
#define GPIOPIN159IN	(*((unsigned long int *) 0x233812FC))
#define GPIOPIN159OUT	(*((unsigned long int *) 0x233812FC))
