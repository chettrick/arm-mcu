/* Initialize CPU core */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <system_efm32.h>
#include <efm32_cmu.h>

void cpu_init(unsigned long int frequency)
{
  __use_custom_syscalls();

  CHIP_Init();			// Fix chip errata

  SystemInit();

  CMU_OscillatorEnable(cmuOsc_HFXO, true, true);
  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);

  SystemCoreClockUpdate();
}
