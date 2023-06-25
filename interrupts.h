#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "types.h"
#include "port.h"

    class InterruptManger
    {
    public:
        static uint32_t handleInterrupt(uint8_t interruptNumber, uint32_t esp);
    };

#endif