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

extern "C" {
//    void SystemClock_Config(void);
//    void MX_GPIO_Init(void);
//    void MX_DMA_Init(void);
    // void MX_ADC1_Init(void);
    // void MX_ADC2_Init(void);
    // void MX_COMP6_Init(void);
    // void MX_DAC1_Init(void);
    // void MX_FDCAN1_Init(void);
    // void MX_FDCAN2_Init(void);
    // void MX_FMAC_Init(void);
    // void MX_FMC_Init(void);
    // void MX_HRTIM1_Init(void);
    // void MX_I2C3_Init(void);
    // void MX_RNG_Init(void);
    // void MX_SPI2_Init(void);
    // void MX_TIM8_Init(void);
    // void MX_USART1_UART_Init(void);
    // void MX_USART3_SMARTCARD_Init(void);
    // void MX_USB_PCD_Init(void);
}


#if defined(EMBOT_REDEFINE_hw_bsp_DRIVER_init)

namespace {
    uint32_t _get1millitick()
    {
        return embot::core::now() / 1000;        
    }

    /**
      * @brief System Clock Configuration
      * @retval None
      */
    void SystemClock_Config(void)
    {
      RCC_OscInitTypeDef RCC_OscInitStruct = {0};
      RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

      /** Configure the main internal regulator output voltage
      */
      HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

      /** Initializes the RCC Oscillators according to the specified parameters
      * in the RCC_OscInitTypeDef structure.
      */
      RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
      RCC_OscInitStruct.HSEState = RCC_HSE_ON;
      RCC_OscInitStruct.HSIState = RCC_HSI_ON;
      RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
      RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
      RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
      RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
      RCC_OscInitStruct.PLL.PLLN = 40;
      RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
      RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
      RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
      if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
      {
        Error_Handler();
      }

      /** Initializes the CPU, AHB and APB buses clocks
      */
      RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
      RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
      RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
      RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
      RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

      if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_8) != HAL_OK)
      {
        Error_Handler();
      }
    }
}

namespace embot::hw::bsp::DRIVER {

    bool init(const embot::hw::Config &config)
    {
        // 1. configure the stm32hal
        stm32hal_config_t cfg = {0};
        cfg.tick1ms_init = config.initmicrotime;
        cfg.tick1ms_get = _get1millitick;
        stm32hal_config(&cfg);

        // 2. start the stm32hal. it does nothing, so we must call HAL_Init() explicitely
        stm32hal_start();
        
        HAL_Init();

        // 3. do all the rest of initialisation
        SystemClock_Config();
        SystemCoreClockUpdate();

        /* Initialize all configured peripherals */
        // MX_GPIO_Init();
        // MX_DMA_Init();
        // MX_ADC1_Init();
        // MX_ADC2_Init();
        // MX_COMP6_Init();
        // MX_DAC1_Init();
        // MX_FDCAN1_Init();
        // MX_FDCAN2_Init();
        // MX_FMAC_Init();
        // MX_FMC_Init();
        // MX_HRTIM1_Init();
        // MX_I2C3_Init();
        // MX_RNG_Init();
        // MX_SPI2_Init();
        // MX_TIM8_Init();
        // MX_USART1_UART_Init();
        // MX_USART3_SMARTCARD_Init();
        // MX_USB_PCD_Init();

        return true;
    }

} // namespace embot::hw::bsp::DRIVER

#endif // EMBOT_REDEFINE_hw_bsp_DRIVER_init

// - end-of-file (leave a blank line after)----------------------------------------------------------------------------

