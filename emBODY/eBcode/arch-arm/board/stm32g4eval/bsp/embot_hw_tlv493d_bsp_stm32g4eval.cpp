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
// - support map: begin of embot::hw::tlv493d

#include "embot_hw_tlv493d_bsp.h"

#if   !defined(HAL_I2C_MODULE_ENABLED) || !defined(EMBOT_ENABLE_hw_tlv493d)

namespace embot { namespace hw { namespace tlv493d {
    
    constexpr BSP thebsp { };
    void BSP::init(embot::hw::TLV493D h) const {}    
    const BSP& getBSP() 
    {
        return thebsp;
    }
    
}}}

#else

namespace embot { namespace hw { namespace tlv493d {
           
    #if defined(STM32HAL_BOARD_STM32G4EVAL)

#if defined(EMBOT_ENABLE_hw_tlv493d_i2ceMODE)
    // we use emulated i2c on bus one
    constexpr PROP prop01 { embot::hw::I2Cdescriptor{embot::hw::ANY::one,   0xBC} };


    constexpr BSP thebsp {     

        // maskofsupported
        mask::pos2mask<uint32_t>(TLV493D::one),        
        // properties
        {{
            &prop01
        }}    
    };
    
#else
    // we use a proper I2C    
    constexpr PROP prop01 { embot::hw::I2Cdescriptor{embot::hw::ANY::three,   0xBC} };
    constexpr PROP prop02fake { embot::hw::I2Cdescriptor{embot::hw::ANY::three,   0x02} };
    constexpr PROP prop03fake { embot::hw::I2Cdescriptor{embot::hw::ANY::three,   0x03} };
    constexpr PROP prop04fake { embot::hw::I2Cdescriptor{embot::hw::ANY::three,   0x04} };
    constexpr PROP prop05fake { embot::hw::I2Cdescriptor{embot::hw::ANY::three,   0x05} };
    constexpr PROP prop06fake { embot::hw::I2Cdescriptor{embot::hw::ANY::three,   0x06} };


    constexpr BSP thebsp {     
#if !defined(EMBOT_ENABLE_hw_tlv493d_emulatedMODE)     
        // maskofsupported
        mask::pos2mask<uint32_t>(TLV493D::one),        
        // properties
        {{
            &prop01
        }}
#else
        // maskofsupported
        mask::pos2mask<uint32_t>(TLV493D::one) |  mask::pos2mask<uint32_t>(TLV493D::two) |  mask::pos2mask<uint32_t>(TLV493D::three) |
        mask::pos2mask<uint32_t>(TLV493D::four) |  mask::pos2mask<uint32_t>(TLV493D::five) |  mask::pos2mask<uint32_t>(TLV493D::six),        
        // properties
        {{
            &prop01, &prop02fake, &prop03fake, &prop04fake, &prop05fake, &prop06fake 
        }}        
#endif        
    };
    
#endif    
    
    void BSP::init(embot::hw::TLV493D h) const {}
        
    #else
        #error embot::hw::tlv493d::thebsp must be defined    
    #endif
    
    const BSP& getBSP() 
    {
        return thebsp;
    }
              
}}} // namespace embot { namespace hw { namespace tlv493d {

#endif // tlv493d

// - support map: end of embot::hw::tlv493d

// - end-of-file (leave a blank line after)----------------------------------------------------------------------------

