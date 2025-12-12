#include DEVICE_HEADER
#include "hal_st/stm32fxxx/DefaultClockNucleoH753ZI.hpp"

/* The system Clock is configured as follows:
 *    System Clock source            = HSI
 *    SYSCLK(Hz)                     = 64000000
 *    HCLK1(Hz)                      = 64000000 (max 64000000)
 *    HCLK2(Hz)                      = 32000000 (max 32000000)
 *    HCLK4(Hz)                      = 64000000 (max 64000000)
 *    AHB Prescaler                  = 1
 *    APB1 Prescaler                 = 1
 *    APB2 Prescaler                 = 1
 *    HSI48 Frequency(Hz)            = 48MHz
 *    LSE Frequency(Hz)              = 32kHz
 *    HSE Frequency(Hz)              = 32MHz
 *    VDD(V)                         = 3.3
 *    Main regulator output voltage  = Scale1 mode
 */
void ConfigureDefaultClockNucleoH753ZI()
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
    RCC_OscInitTypeDef RCC_OscInitStruct = {};

    /** Supply configuration update enable
     */
    HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

    /** Configure the main internal regulator output voltage
     */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY))
    {
    }

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
    RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);
}
