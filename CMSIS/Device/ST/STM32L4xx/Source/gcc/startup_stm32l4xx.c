/******************************************************************************
 * @file     startup_<Device>.c
 * @brief    CMSIS-Core(M) Device Startup File for
 *           Device <Device>
 * @version  V1.0.0
 * @date     20. January 2021
 ******************************************************************************/
/*
 * Copyright (c) 2009-2021 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "stm32l4xx.h"

/*---------------------------------------------------------------------------
  External References
 *---------------------------------------------------------------------------*/
extern uint32_t __INITIAL_SP;
extern uint32_t __STACK_LIMIT;
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
extern uint32_t __STACK_SEAL;
#endif

extern __NO_RETURN void __PROGRAM_START(void);

/*---------------------------------------------------------------------------
  Internal References
 *---------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler  (void);
__NO_RETURN void Default_Handler(void);

/*---------------------------------------------------------------------------
  Exception / Interrupt Handler
 *---------------------------------------------------------------------------*/
/* Exceptions */
__NO_RETURN void NMI_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void HardFault_Handler      (void) __attribute__ ((weak));
__NO_RETURN void MemManage_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void BusFault_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void UsageFault_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SecureFault_Handler    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SVC_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DebugMon_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void PendSV_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SysTick_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));

/* TODO: Add your device specific interrupt handler */
// void <DeviceInterrupt first>_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
// ...
// void <DeviceInterrupt last>_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));


/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/

#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

extern const void *  __VECTOR_TABLE[];
       const void *  __VECTOR_TABLE[] __VECTOR_TABLE_ATTRIBUTE = {
  (&__INITIAL_SP),          /*     Initial Stack Pointer */
  Reset_Handler,            /*     Reset Handler */
  NMI_Handler,              /* -14 NMI Handler */
  HardFault_Handler,        /* -13 Hard Fault Handler */
  MemManage_Handler,        /* -12 MPU Fault Handler */
  BusFault_Handler,         /* -11 Bus Fault Handler */
  UsageFault_Handler,       /* -10 Usage Fault Handler */
  SecureFault_Handler,      /*  -9 Secure Fault Handler */
  0,                        /*     Reserved */
  0,                        /*     Reserved */
  0,                        /*     Reserved */
  SVC_Handler,              /*  -5 SVCall Handler */
  DebugMon_Handler,         /*  -4 Debug Monitor Handler */
  0,                        /*     Reserved */
  PendSV_Handler,           /*  -2 PendSV Handler */
  SysTick_Handler,          /*  -1 SysTick Handler */

/* TODO: Add your device specific interrupt vectors */
  /* Interrupts */
  // <DeviceInterrupt first>_Handler,     /* first Device Interrupt */
  // ...
  // <DeviceInterrupt last>_Handler       /* last Device Interrupt */
};

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

/*---------------------------------------------------------------------------
  Reset Handler called on controller reset
 *---------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler(void)
{
  __set_PSP((uint32_t)(&__INITIAL_SP));

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  __TZ_set_STACKSEAL_S((uint32_t *)(&__STACK_SEAL));
#endif

  SystemInit();                    /* CMSIS System Initialization */
  __PROGRAM_START();               /* Enter PreMain (C library entry point) */
}


#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif

/*---------------------------------------------------------------------------
  Hard Fault Handler
 *---------------------------------------------------------------------------*/
void HardFault_Handler(void)
{
  while(1);
}

/*---------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *---------------------------------------------------------------------------*/
void Default_Handler(void)
{
  while(1);
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#endif
