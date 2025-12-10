#include "app_main.h"

#include "cdc_uart.hpp"
#include "libxr.hpp"
#include "main.h"
#include "stm32_adc.hpp"
#include "stm32_can.hpp"
#include "stm32_canfd.hpp"
#include "stm32_dac.hpp"
#include "stm32_flash.hpp"
#include "stm32_gpio.hpp"
#include "stm32_i2c.hpp"
#include "stm32_power.hpp"
#include "stm32_pwm.hpp"
#include "stm32_spi.hpp"
#include "stm32_timebase.hpp"
#include "stm32_uart.hpp"
#include "stm32_usb_dev.hpp"
#include "stm32_watchdog.hpp"
#include "flash_map.hpp"
#include "app_framework.hpp"
#include "xrobot_main.hpp"

using namespace LibXR;

/* User Code Begin 1 */
/* User Code End 1 */
// NOLINTBEGIN
// clang-format off
/* External HAL Declarations */
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

/* No DMA Resources generated. */

extern "C" void app_main(void) {
  // clang-format on
  // NOLINTEND
  /* User Code Begin 2 */
  
  /* User Code End 2 */
  // clang-format off
  // NOLINTBEGIN
  STM32TimerTimebase timebase(&htim2);
  PlatformInit();
  STM32PowerManager power_manager;

  /* GPIO Configuration */
  STM32GPIO Echo(Echo_GPIO_Port, Echo_Pin);
  STM32GPIO Trig(Trig_GPIO_Port, Trig_Pin);
  STM32GPIO ENCA(ENCA_GPIO_Port, ENCA_Pin);
  STM32GPIO ENCB(ENCB_GPIO_Port, ENCB_Pin);
  STM32GPIO AIN1(AIN1_GPIO_Port, AIN1_Pin);
  STM32GPIO AIN2(AIN2_GPIO_Port, AIN2_Pin);


  STM32PWM pwm_tim1_ch1(&htim1, TIM_CHANNEL_1, false);


  /* Terminal Configuration */


  LibXR::HardwareContainer peripherals{
    LibXR::Entry<LibXR::PowerManager>({power_manager, {"power_manager"}}),
    LibXR::Entry<LibXR::GPIO>({Echo, {"Echo"}}),
    LibXR::Entry<LibXR::GPIO>({Trig, {"Trig"}}),
    LibXR::Entry<LibXR::GPIO>({AIN1, {"AIN1"}}),
    LibXR::Entry<LibXR::GPIO>({AIN2, {"AIN2"}}),
    LibXR::Entry<LibXR::PWM>({pwm_tim1_ch1, {"pwm_tim1_ch1"}}),
    LibXR::Entry<LibXR::GPIO>({ENCA, {"ENCA"}}),
    LibXR::Entry<LibXR::GPIO>({ENCB, {"ENCB"}})
  };

  // clang-format on
  // NOLINTEND
  /* User Code Begin 3 */
  STM32Flash flash(FLASH_SECTORS, FLASH_SECTOR_NUMBER);
  LibXR::DatabaseRaw<4> database(flash);

  peripherals.Register(LibXR::Entry<LibXR::Database>{database, {"database"}});
  XRobotMain(peripherals);
  /* User Code End 3 */
}