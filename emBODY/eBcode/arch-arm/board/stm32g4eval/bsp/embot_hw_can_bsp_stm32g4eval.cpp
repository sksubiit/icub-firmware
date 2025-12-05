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

// - support map: begin of embot::hw::can

#include "embot_hw_can_bsp.h"

extern "C" {
    void MX_FDCAN1_Init(void);
    void MX_FDCAN2_Init(void);
}

#if   !defined(EMBOT_ENABLE_hw_can)

namespace embot { namespace hw { namespace can {
    
    constexpr BSP thebsp { };
    void BSP::init(embot::hw::CAN h) const {}    
    const BSP& getBSP() 
    {
        return thebsp;
    }
    
}}}

#else

namespace embot { namespace hw { namespace can {
               
    #if   defined(STM32HAL_BOARD_STM32G4EVAL)
        
    // it has HAL_FDCAN_MODULE_ENABLED
    
    constexpr PROP can1p = { .handle = &hfdcan1 }; 
    constexpr PROP can2p = { .handle = &hfdcan2 };    
        
    constexpr BSP thebsp {        
        // maskofsupported
        mask::pos2mask<uint32_t>(CAN::one) | mask::pos2mask<uint32_t>(CAN::two),        
        // properties
        {{
            &can1p, &can2p           
        }}        
    };
    
    void BSP::init(embot::hw::CAN h) const 
    {
        // Map the abstract handle 'h' to the specific hardware init
        // Assuming CAN::one maps to FDCAN1 and CAN::two to FDCAN2 based on your board config
        switch(h)
        {
            case CAN::one: 
                MX_FDCAN1_Init(); 
                break;
            case CAN::two: 
                MX_FDCAN2_Init(); 
                break;
            default: 
                break;
        }
    }
    
    #else
        #error embot::hw::can::thebsp must be defined    
    #endif
    
    const BSP& getBSP() 
    {
        return thebsp;
    }
              
}}} // namespace embot { namespace hw { namespace can {
    

#if defined(HAL_FDCAN_MODULE_ENABLED)

extern "C"
{    
    void FDCAN1_IT0_IRQHandler(void)
    {
        HAL_FDCAN_IRQHandler(&hfdcan1);
    }  
    
    void FDCAN1_IT1_IRQHandler(void)
    {
        HAL_FDCAN_IRQHandler(&hfdcan1);
    }  
}
        

#endif //

#endif // EMBOT_ENABLE_hw_can


// - support map: end of embot::hw::can


// - end-of-file (leave a blank line after)----------------------------------------------------------------------------
