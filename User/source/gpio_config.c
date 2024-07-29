#include "stm32l476xx.h"

#include "gpio_config.h"

/**
 * This function configures GPIO PA5 as follows:
 *   - Output mode
 *   - Output push-pull                 (default)
 *   - Output speed low                 (default)
 *   - No pull-up or pull-down resistor (default)
 *
 * @note GPIO PA5 is used to toggle the LED.
 */
void GPIO_PA5_config() {
    // Enable the GPIO port A AHB2 interface clock
    RCC->AHB2ENR |= 1 << RCC_AHB2ENR_GPIOAEN_Pos;
    
    // Configure GPIO port A pin 5 as output mode (0b01)
    GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk;
    GPIOA->MODER |= 0b01 << GPIO_MODER_MODE5_Pos;
}


/**
 * This function configures GPIO PA2 as USART2 transmitter (output):
 *   - Alternate function mode          (alternate function 7)
 *   - Output push-pull                 (default)
 *   - Output speed high
 *   - No pull-up or pull-down resistor (default)
 *
 * @note Alternate function number refer to [DS10198, p.92]
 */
void GPIO_PA2_config() {
    // Enable the GPIO port A AHB2 interface clock
    RCC->AHB2ENR |= 1 << RCC_AHB2ENR_GPIOAEN_Pos;
    
    // Configure GPIO port A pin 2 as alternate function mode (0b10)
    GPIOA->MODER &= ~GPIO_MODER_MODE2_Msk;
    GPIOA->MODER |= 0b10 << GPIO_MODER_MODE2_Pos;
    
    // Select alternate function 7 (0b0111)
    GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL2_Msk;
    GPIOA->AFR[0] |= 0b0111 << GPIO_AFRL_AFSEL2_Pos;
    
    // Set output speed to high (0b10)
    GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED2_Msk;
    GPIOA->OSPEEDR |= 0b10 << GPIO_OSPEEDR_OSPEED2_Pos;
}


/**
 * This function configures GPIO PA3 as USART2 receiver (input):
 *   - Alternate function mode (alternate function 7)
 *   - Don't care about the rest since this is an input
 *
 * @note Alternate function number refer to [DS10198, p.92]
 */
void GPIO_PA3_config() {
    // Enable the GPIO port A AHB2 interface clock
    RCC->AHB2ENR |= 1 << RCC_AHB2ENR_GPIOAEN_Pos;
    
    // Configure GPIO port A pin 3 as alternate function mode (0b10)
    GPIOA->MODER &= ~GPIO_MODER_MODE3_Msk;
    GPIOA->MODER |= 0b10 << GPIO_MODER_MODE3_Pos;
    
    // Select alternate function 7 (0b0111)
    GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL3_Msk;
    GPIOA->AFR[0] |= 0b0111 << GPIO_AFRL_AFSEL3_Pos;
}