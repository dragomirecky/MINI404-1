/*
    stm32f407xx.h - Chip variant definition for the STM32F407xx
	Copyright 2022 VintagePC <https://github.com/vintagepc/>

 	This file is part of Mini404.

	Mini404 is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Mini404 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Mini404.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HW_ARM_PRUSA_STM32F407XX_H
#define HW_ARM_PRUSA_STM32F407XX_H

#include "../stm32_common/stm32_chip_macros.h"
#include "../stm32_common/stm32_types.h"
#include "hw/misc/stm32f4xx_syscfg.h"
#include "hw/timer/stm32f2xx_timer.h"
#include "hw/misc/stm32f4xx_exti.h"
#include "hw/or-irq.h"
#include "../stm32f407/stm32f4xx_adcc.h"
#include "../stm32f407/stm32f2xx_i2c.h"
#include "../stm32f407/stm32f2xx_pwr.h"
#include "../stm32f407/stm32f2xx_rcc.h"
#include "../stm32f407/stm32f2xx_rtc.h"
#include "../stm32f407/stm32f2xx_tim.h"
#include "../stm32f407/stm32f4xx_rng.h"
#include "../stm32f407/stm32f4xx_usb.h"
#include "../stm32f407/stm32_uart.h"
#include "stm32f4xx_irqs.h"
#include "qemu/units.h"

static const stm32_soc_cfg_t stm32f407xx_cfg =
{
	.nvic_irqs = F4xx_F407_COUNT_IRQ,
	.rcc_hsi_freq = 16000000,
	.rcc_hse_freq = 12000000,
	.rcc_lse_freq = 32768,
	.rcc_lsi_freq = 32000,
	.flash_base = 0x08000000,
	.flash_variants = {
		{TYPE_STM32F407xE_SOC, 512*KiB},
		{TYPE_STM32F407xG_SOC, 1U*MiB},
		{NULL},
	},
	.sram_base = 0x20000000,
	.sram_variants = {
		{TYPE_STM32F407xE_SOC, 192U*KiB},
		{TYPE_STM32F407xG_SOC, 192U*KiB},
		{NULL},
	},
	.ccmsram_base = 0x10000000,
	.ccmsram_variants = {
		{TYPE_STM32F407xE_SOC, 64U*KiB},
		{TYPE_STM32F407xG_SOC, 64U*KiB},
		{NULL},
	},
	.perhipherals = {
		PER_LNI(P_FINT, TYPE_STM32F4xx_FINT, 0x40023C00, F4xx_FLASH_IRQ),

		PER_LNI(P_UART1, TYPE_STM32_UART, 0x40011000, F4xx_USART1_IRQ),
		PER_LNI(P_UART2, TYPE_STM32_UART, 0x40004400, F4xx_USART2_IRQ),
		PER_LNI(P_UART3, TYPE_STM32_UART, 0x40004800, F4xx_USART3_IRQ),
		PER_LNI(P_UART4, TYPE_STM32_UART, 0x40004C00, F4xx_UART4_IRQ),
		PER_LNI(P_UART5, TYPE_STM32_UART, 0x40005000, F4xx_UART5_IRQ),
		PER_LNI(P_UART6, TYPE_STM32_UART, 0x40011400, F4xx_USART6_IRQ),

		PER_LNI(P_ADC1, TYPE_STM32F4xx_ADC, 0x40012000, F4xx_ADC_1_2_3_IRQ),
		PER_LNI(P_ADC2, TYPE_STM32F4xx_ADC, 0x40012100, F4xx_ADC_1_2_3_IRQ),
		PER_LNI(P_ADC3, TYPE_STM32F4xx_ADC, 0x40012200, F4xx_ADC_1_2_3_IRQ),

		PER_LNI(P_SPI1, TYPE_STM32F4xx_SPI, 0x40013000, F4xx_SPI1_IRQ),
		PER_LNI(P_SPI2, TYPE_STM32F4xx_SPI, 0x40003800, F4xx_SPI2_IRQ),
		PER_LNI(P_SPI3, TYPE_STM32F4xx_SPI, 0x40003C00, F4xx_SPI3_IRQ),

		PER_LNI(P_I2C1, TYPE_STM32F2XX_I2C, 0x40005400, F4xx_I2C1_EV_IRQ, F4xx_I2C1_ER_IRQ),
		PER_LNI(P_I2C2, TYPE_STM32F2XX_I2C, 0x40005800, F4xx_I2C2_EV_IRQ, F4xx_I2C2_ER_IRQ),
		PER_LNI(P_I2C3, TYPE_STM32F2XX_I2C, 0x40005C00, F4xx_I2C3_EV_IRQ, F4xx_I2C3_ER_IRQ),

		PER_LN(P_GPIOA, TYPE_STM32F4xx_GPIO, 0x40020000),
		PER_LN(P_GPIOB, TYPE_STM32F4xx_GPIO, 0x40020400),
		PER_LN(P_GPIOC, TYPE_STM32F4xx_GPIO, 0x40020800),
		PER_LN(P_GPIOD, TYPE_STM32F4xx_GPIO, 0x40020C00),
		PER_LN(P_GPIOE, TYPE_STM32F4xx_GPIO, 0x40021000),
		PER_LN(P_GPIOF, TYPE_STM32F4xx_GPIO, 0x40021400),
		PER_LN(P_GPIOG, TYPE_STM32F4xx_GPIO, 0x40021800),
		PER_LN(P_GPIOH, TYPE_STM32F4xx_GPIO, 0x40021C00),
		PER_LN(P_GPIOI, TYPE_STM32F4xx_GPIO, 0x40022000),
		PER_LN(P_GPIOJ, TYPE_STM32F4xx_GPIO, 0x40022400),
		PER_LN(P_GPIOK, TYPE_STM32F4xx_GPIO, 0x40022800),

		PER_LNI(P_DMA1, TYPE_STM32F4xx_DMA, 0x40026000,
			F4xx_DMA1_S0_IRQ, F4xx_DMA1_S1_IRQ, F4xx_DMA1_S2_IRQ, F4xx_DMA1_S3_IRQ,
			F4xx_DMA1_S4_IRQ, F4xx_DMA1_S5_IRQ, F4xx_DMA1_S6_IRQ, F4xx_DMA1_S7_IRQ),
		PER_LNI(P_DMA2, TYPE_STM32F4xx_DMA, 0x40026400,
			F4xx_DMA2_S0_IRQ, F4xx_DMA2_S1_IRQ, F4xx_DMA2_S2_IRQ, F4xx_DMA2_S3_IRQ,
			F4xx_DMA2_S4_IRQ, F4xx_DMA2_S5_IRQ, F4xx_DMA2_S6_IRQ, F4xx_DMA2_S7_IRQ),

		PER_LN(P_TIM1, 	TYPE_STM32F4XX_TIMER, 0x40010000), // TIM1 FIXME: TIM1 is a complex timer w/ multiple IRQs
		PER_LNI(P_TIM2, 	TYPE_STM32F4XX_TIMER, 0x40000000, F4xx_TIM2_IRQ),
		PER_LNI(P_TIM3, 	TYPE_STM32F4XX_TIMER, 0x40000400, F4xx_TIM3_IRQ),
		PER_LNI(P_TIM4, 	TYPE_STM32F4XX_TIMER, 0x40000800, F4xx_TIM4_IRQ),
		PER_LNI(P_TIM5, 	TYPE_STM32F4XX_TIMER, 0x40000C00, F4xx_TIM5_IRQ),
		PER_LNI(P_TIM6, 	TYPE_STM32F4XX_TIMER, 0x40001000, F4xx_TIM6_DAC_IRQ),
		PER_LNI(P_TIM7, 	TYPE_STM32F4XX_TIMER, 0x40001400, F4xx_TIM7_IRQ),
		PER_LN(P_TIM8, 	TYPE_STM32F4XX_TIMER, 0x40010400),
		PER_LNI(P_TIM9, 	TYPE_STM32F4XX_TIMER, 0x40014000, F4xx_TIM1_BRK_TIM9_IRQ),
		PER_LNI(P_TIM10, 	TYPE_STM32F4XX_TIMER, 0x40014400, F4xx_TIM1_UP_TIM10_IRQ),
		PER_LNI(P_TIM11, 	TYPE_STM32F4XX_TIMER, 0x40014800, F4xx_TIM1_TRG_COM_TIM11_IRQ),
		PER_LNI(P_TIM12, 	TYPE_STM32F4XX_TIMER, 0x40001800, F4xx_TIM8_BRK_TIM12_IRQ),
		PER_LNI(P_TIM13, 	TYPE_STM32F4XX_TIMER, 0x40001C00, F4xx_TIM8_UP_TIM13_IRQ),
		PER_LNI(P_TIM14, 	TYPE_STM32F4XX_TIMER, 0x40002000, F4xx_TIM8_TRG_COM_TIM14_IRQ),

		PER_LNI(P_EXTI, TYPE_STM32F4XX_EXTI, 0x40013C00,
			F4xx_EXTI0_IRQ, F4xx_EXTI1_IRQ, F4xx_EXTI2_IRQ, F4xx_EXTI3_IRQ,
			F4xx_EXTI4_IRQ, [5 ... 9] = F4xx_EXTI_5_9_IRQ,
			[10 ... 15] = F4xx_EXTI_10_15_IRQ
			),
		PER_LNI(P_ETH, "stm32f4xx-ethernet", 0x40028000, F4xx_ETH_IRQ, F4xx_ETH_WKUP_IRQ),
		PER_LNI(P_RCC, TYPE_STM32F407_RCC, 0x40023800, F4xx_RCC_IRQ),
		PER_LNI(P_FINT, TYPE_STM32F40x_F41x_FINT, 0x40023C00, F4xx_FLASH_IRQ),
		PER_LN(P_IWDG, TYPE_STM32F4xx_IWDG, 0x40003000),
		PER_LN(P_CRC, TYPE_STM32F4xx_CRC, 0x40023000),
		PER_LN(P_RTC, TYPE_STM32F2XX_RTC, 0x40002800),
		PER_LN(P_ITM, TYPE_STM32F4xx_ITM, 0xE0000000),
		PER_LN(P_PWR, TYPE_STM32F2XX_PWR, 0x40007000),
		PER_LNI(P_RNG, TYPE_STM32F4XX_RNG, 0x50060800, F4xx_HASH_RNG_IRQ),
		PER_LN(P_OTP, TYPE_STM32F4xx_OTP, 0x1FFF7800),
		PER_LNI(P_USBHS, TYPE_STM32F4xx_USB, 0x40040000, F4xx_OTG_HS_IRQ),
		PER_LNI(P_USBFS, TYPE_STM32F4xx_USB, 0x50000000, F4xx_OTG_FS_IRQ),
		PER_LN(P_ADCC, TYPE_STM32F4XX_ADCC, 0x40012300),

		PER_LN(P_SYSCFG, TYPE_STM32F40x_F41x_SYSCFG, 0x40013800),

	}
} ;

#endif // HW_ARM_PRUSA_STM32F407XX_H