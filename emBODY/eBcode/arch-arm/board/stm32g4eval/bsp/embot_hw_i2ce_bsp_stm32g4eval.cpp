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

// - support map: begin of embot::hw::i2ce

#include "embot_hw_i2ce.h"
#include "embot_hw_i2ce_bsp.h"
#include "embot_hw_gpio.h"

#if !defined(EMBOT_ENABLE_hw_i2ce)

namespace embot { namespace hw { namespace i2ce { namespace bsp {
    
    constexpr BSP thebsp { };
    bool BSP::init(embot::hw::I2CE h, const Config &config) const { return true;}
    bool BSP::deinit(embot::hw::I2CE h) const { return true;}
    const BSP& getBSP() 
    {
        return thebsp;
    }
    
}}}}

#else

namespace embot { namespace hw { namespace i2ce { namespace bsp {
    
    #if defined(STM32HAL_BOARD_STM32G4EVAL)
    
    constexpr std::array<embot::hw::GPIO, SignalsNumberOf> pinout1 = { {
        {embot::hw::GPIO::PORT::F, embot::hw::GPIO::PIN::eight},        // scl
        {embot::hw::GPIO::PORT::F, embot::hw::GPIO::PIN::nine}          // sda
    } };
    constexpr PROP i2ce1p = { Speed::standard100, pinout1 }; 
    
 #if 0   
 
    constexpr std::array<embot::hw::GPIO, SignalsNumberOf> pinout2 = { {
        {embot::hw::GPIO::PORT::A, embot::hw::GPIO::PIN::four},     // scl
        {embot::hw::GPIO::PORT::A, embot::hw::GPIO::PIN::seven}     // sda
    } };
    constexpr PROP i2ce2p = { Speed::standard100, pinout2 };     
    
    constexpr std::array<embot::hw::GPIO, SignalsNumberOf> pinout3 = { {
        {embot::hw::GPIO::PORT::A, embot::hw::GPIO::PIN::four},     // scl
        {embot::hw::GPIO::PORT::A, embot::hw::GPIO::PIN::six}       // sda
    } };
    constexpr PROP i2ce3p = { Speed::standard100, pinout3 };     
    
    constexpr std::array<embot::hw::GPIO, SignalsNumberOf> pinout4 = { {
        {embot::hw::GPIO::PORT::A, embot::hw::GPIO::PIN::four},     // scl
        {embot::hw::GPIO::PORT::A, embot::hw::GPIO::PIN::five}      // sda
    } };
    constexpr PROP i2ce4p = { Speed::standard100, pinout4 }; 
    
#endif   

    
        constexpr BSP thebsp {        
        // maskofsupported
//        mask::pos2mask<uint32_t>(I2CE::one) | mask::pos2mask<uint32_t>(I2CE::two) | 
//        mask::pos2mask<uint32_t>(I2CE::three) | mask::pos2mask<uint32_t>(I2CE::four),    
        mask::pos2mask<uint32_t>(I2CE::one),
        // properties
        {{
//            &i2ce1p, &i2ce2p, &i2ce3p, &i2ce4p  
        &i2ce1p, nullptr, nullptr, nullptr           
        }}        
    };
     
    
    
    bool BSP::init(embot::hw::I2CE h, const Config &config) const
    { 
        static constexpr embot::hw::gpio::Config out 
        { 
            embot::hw::gpio::Mode::OUTPUTpushpull, 
            embot::hw::gpio::Pull::nopull, 
            embot::hw::gpio::Speed::veryhigh 
        };    
        
        embot::hw::GPIO scl = embot::hw::i2ce::bsp::getBSP().getPROP(h)->pinout[0];
        embot::hw::GPIO sda = embot::hw::i2ce::bsp::getBSP().getPROP(h)->pinout[1];
        
        switch(h)
        {
            case I2CE::one:
            case I2CE::two:
            case I2CE::three:
            case I2CE::four:
            {
                embot::hw::gpio::init(scl, out);
                embot::hw::gpio::init(sda, out);
            } break;
            
            default: {} break;                            
        }
        
        return true; 
    }

    bool BSP::deinit(embot::hw::I2CE h) const
    { 

        embot::hw::GPIO scl = embot::hw::i2ce::bsp::getBSP().getPROP(h)->pinout[0];
        embot::hw::GPIO sda = embot::hw::i2ce::bsp::getBSP().getPROP(h)->pinout[1];
        
        switch(h)
        {
            case I2CE::one:
            case I2CE::two:
            case I2CE::three:
            case I2CE::four:
            {
                embot::hw::gpio::deinit(scl);
                embot::hw::gpio::deinit(sda);
            } break;
            
            default: {} break;                            
        }        
        
        return true;        
    }
    
    #else
        #error embot::hw::bsp::spi::thebsp must be defined    
    #endif
    
    const BSP& getBSP() 
    {
        return thebsp;
    }
    
}}}}

extern "C"
{
    // TODO: add in here any C function we may need
    
}

extern "C"
{
    // TODO: add in here any irq handler we may beed
}

#endif // i2ce

// - support map: end of embot::hw::i2ce

// - end-of-file (leave a blank line after)----------------------------------------------------------------------------

 