MEMORY
{
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
  rom (rx) : ORIGIN = 0x00000000, LENGTH = 128K
}

SECTIONS
{
  . = 0x0;		/* From 0x00000000 */
  .text : {
  *(vectors)		/* Vector table */
  *(.text)		/* Program code */
  *(.rodata)		/* Read only data */
  } >rom
  . = 0x20000000;	/* From 0x20000000 */      
  .data : {
  *(.data)		/* Data memory */
  } >ram AT > rom 
  .bss : {
  *(.bss)		/* Zero-filled run time allocate data memory */
  } >ram AT > rom
}  

/*  Libraries to link against. */

INPUT( -lstm32f103 )

/*  Provide a default vector for any unhandled interrupts. */

PROVIDE(NMIException = _default_handler);
PROVIDE(HardFaultException = _default_handler);
PROVIDE(MemManageException = _default_handler);
PROVIDE(BusFaultException = _default_handler);
PROVIDE(UsageFaultException = _default_handler);
PROVIDE(SVCHandler = _default_handler);
PROVIDE(DebugMonitor = _default_handler);
PROVIDE(PendSVC = _default_handler);
PROVIDE(SysTickHandler = _default_handler);
PROVIDE(WWDG_IRQHandler = _default_handler);
PROVIDE(PVD_IRQHandler = _default_handler);
PROVIDE(TAMPER_IRQHandler = _default_handler);
PROVIDE(RTC_IRQHandler = _default_handler);
PROVIDE(FLASH_IRQHandler = _default_handler);
PROVIDE(RCC_IRQHandler = _default_handler);
PROVIDE(EXTI0_IRQHandler = _default_handler);
PROVIDE(EXTI1_IRQHandler = _default_handler);
PROVIDE(EXTI2_IRQHandler = _default_handler);
PROVIDE(EXTI3_IRQHandler = _default_handler);
PROVIDE(EXTI4_IRQHandler = _default_handler);
PROVIDE(DMAChannel1_IRQHandler = _default_handler);
PROVIDE(DMAChannel2_IRQHandler = _default_handler);
PROVIDE(DMAChannel3_IRQHandler = _default_handler);
PROVIDE(DMAChannel4_IRQHandler = _default_handler);
PROVIDE(DMAChannel5_IRQHandler = _default_handler);
PROVIDE(DMAChannel6_IRQHandler = _default_handler);
PROVIDE(DMAChannel7_IRQHandler = _default_handler);
PROVIDE(ADC_IRQHandler = _default_handler);
PROVIDE(USB_HP_CAN_TX_IRQHandler = _default_handler);
PROVIDE(USB_LP_CAN_RX0_IRQHandler = _default_handler);
PROVIDE(CAN_RX1_IRQHandler = _default_handler);
PROVIDE(CAN_SCE_IRQHandler = _default_handler);
PROVIDE(EXTI9_5_IRQHandler = _default_handler);
PROVIDE(TIM1_BRK_IRQHandler = _default_handler);
PROVIDE(TIM1_UP_IRQHandler = _default_handler);
PROVIDE(TIM1_TRG_COM_IRQHandler = _default_handler);
PROVIDE(TIM1_CC_IRQHandler = _default_handler);
PROVIDE(TIM2_IRQHandler = _default_handler);
PROVIDE(TIM3_IRQHandler = _default_handler);
PROVIDE(TIM4_IRQHandler = _default_handler);
PROVIDE(I2C1_EV_IRQHandler = _default_handler);
PROVIDE(I2C1_ER_IRQHandler = _default_handler);
PROVIDE(I2C2_EV_IRQHandler = _default_handler);
PROVIDE(I2C2_ER_IRQHandler = _default_handler);
PROVIDE(SPI1_IRQHandler = _default_handler);
PROVIDE(SPI2_IRQHandler = _default_handler);
PROVIDE(USART1_IRQHandler = _default_handler);
PROVIDE(USART2_IRQHandler = _default_handler);
PROVIDE(USART3_IRQHandler = _default_handler);
PROVIDE(EXTI15_10_IRQHandler = _default_handler);
PROVIDE(RTCAlarm_IRQHandler = _default_handler);
PROVIDE(USBWakeUp_IRQHandler = _default_handler);
