
/*
 * Copyright (C) 2020 iCub Tech - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
*/


// --------------------------------------------------------------------------------------------------------------------
// - public interface
// --------------------------------------------------------------------------------------------------------------------

#include "embot_hw_bsp.h"


// --------------------------------------------------------------------------------------------------------------------
// - external dependencies
// --------------------------------------------------------------------------------------------------------------------

#include <cstring>
#include <vector>
#include <array>

#include "embot_core_binary.h"
#include "embot_core.h"

#if defined(USE_STM32HAL)
    #include "stm32hal.h"
#else
    #warning this implementation is only for stm32hal
#endif


using namespace std;
using namespace embot::core::binary;

// --------------------------------------------------------------------------------------------------------------------
// - Inclusion of the bsp cpp files
// --------------------------------------------------------------------------------------------------------------------

#include "embot_hw_bsp_stm32g4eval_config.h"

#if defined(EMBOT_BSP_IN_A_SINGLE_FILE)
 #include "embot_hw_button_bsp_stm32g4eval.cpp"
 #include "embot_hw_can_bsp_stm32g4eval.cpp"
 #include "embot_hw_flash_bsp_stm32g4eval.cpp"
 #include "embot_hw_gpio_bsp_stm32g4eval.cpp"
 #include "embot_hw_i2c_bsp_stm32g4eval.cpp"
 #include "embot_hw_i2ce_bsp_stm32g4eval.cpp"
 #include "embot_hw_led_bsp_stm32g4eval.cpp"
 #include "embot_hw_specialize_bsp_stm32g4eval.cpp"
 #include "embot_hw_tlv493d_bsp_stm32g4eval.cpp"
 #include "embot_hw_bsp_DRIVER_stm32g4eval.cpp"
#endif // EMBOT_BSP_IN_A_SINGLE_FILE

// - end-of-file (leave a blank line after)----------------------------------------------------------------------------

