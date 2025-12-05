/*
 * Copyright (C) 2025 iCub Tech - Istituto Italiano di Tecnologia
 * Author:  SATHISH KUMAR S
 * email:   sathish.subramani@iit.it
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
// - configuration of peripherals and chips. it is done board by board. it contains a check vs correct STM32HAL_BOARD_*
// --------------------------------------------------------------------------------------------------------------------

#include "embot_hw_bsp_stm32g4eval_config.h"

// --------------------------------------------------------------------------------------------------------------------
// - support maps for the supported drivers
// --------------------------------------------------------------------------------------------------------------------

// - support map: begin of embot::hw::i2c

#include "embot_hw_i2c_bsp.h"

extern "C" {
    void MX_I2C3_Init(void);
}

#if !defined(HAL_I2C_MODULE_ENABLED) || !defined(EMBOT_ENABLE_hw_i2c)

namespace embot { namespace hw { namespace i2c {
    
    constexpr BSP thebsp { };
    void BSP::init(embot::hw::I2C h) const {}    
    const BSP& getBSP() 
    {
        return thebsp;
    }
    
}}}

#else

namespace embot { namespace hw { namespace i2c {
                  
    #if   defined(STM32HAL_BOARD_STM32G4EVAL)
    
    constexpr PROP i2c3p { &hi2c3, embot::hw::i2c::Speed::fast400 };
        
    constexpr BSP thebsp {        
        // maskofsupported   
        mask::pos2mask<uint32_t>(I2C::three),         
        // properties
        {{       
            nullptr, nullptr, &i2c3p
        }}        
    }; 
    void BSP::init(embot::hw::I2C h) const 
    {
        // Assuming I2C3 is the handle used
        if (h == I2C3) 
        {
            MX_I2C3_Init();
        }
    }
    
    #else
        #error embot::hw::i2c::thebsp must be defined    
    #endif
    
    const BSP& getBSP() 
    {
        return thebsp;
    }
              
}}} // namespace embot { namespace hw { namespace i2c {


// irq handlers of i2c

#if defined(STM32HAL_BOARD_STM32G4EVAL)

void I2C3_EV_IRQHandler(void)
{
    HAL_I2C_EV_IRQHandler(&hi2c3);
}

void I2C3_ER_IRQHandler(void)
{
    HAL_I2C_ER_IRQHandler(&hi2c3);
}

void DMA1_Channel1_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_i2c3_rx);
}

void DMA1_Channel2_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_i2c3_tx);
}

#endif // irq handlers

#endif // i2c




// - support map: end of embot::hw::i2c    

// - end-of-file (leave a blank line after)----------------------------------------------------------------------------

