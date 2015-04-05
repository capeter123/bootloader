//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include "cortexm/ExceptionHandlers.h"

// ----------------------------------------------------------------------------

extern void
__attribute__((noreturn))
bootloader_main(void);

// ----------------------------------------------------------------------------
// Default exception handlers. Override the ones here by defining your own
// handler routines in your application code.
// ----------------------------------------------------------------------------

#if defined(DEBUG)

// The DEBUG version is not naked, to allow breakpoints at Reset_Handler
void __attribute__ ((section(".after_vectors"),noreturn))
Reset_Handler (void)
  {
    bootloader_main();
  }

#else

// The Release version is optimised to a quick branch to bootloader_main.
void __attribute__ ((section(".after_vectors"),naked))
Reset_Handler(void)
{
  asm volatile
  (
      " ldr     r0,=bootloader_main \n"
      " bx      r0"
      :
      :
      :
  );
}

#endif

void __attribute__ ((section(".after_vectors"),weak))
NMI_Handler(void)
{
  while (1)
    {
    }
}

void __attribute__ ((section(".after_vectors"),weak))
HardFault_Handler(void)
{
  while (1)
    {
    }
}

#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)

void __attribute__ ((section(".after_vectors"),weak))
MemManage_Handler(void)
  {
    while (1)
      {
      }
  }

void __attribute__ ((section(".after_vectors"),weak))
BusFault_Handler(void)
  {
    while (1)
      {
      }
  }

void __attribute__ ((section(".after_vectors"),weak))
UsageFault_Handler(void)
  {
    while (1)
      {
      }
  }

#endif

void __attribute__ ((section(".after_vectors"),weak))
SVC_Handler(void)
{
  while (1)
    {
    }
}

#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)

void __attribute__ ((section(".after_vectors"),weak))
DebugMon_Handler(void)
{
  while (1)
    {
    }
}

#endif

void __attribute__ ((section(".after_vectors"),weak))
PendSV_Handler(void)
{
  while (1)
    {
    }
}

void __attribute__ ((section(".after_vectors"),weak))
SysTick_Handler(void)
{
  while (1)
    {
    }
}

