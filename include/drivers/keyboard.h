#ifndef __MYOS__DRIVERS__KEYBOARD_H
#define __MYOS__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>

namespace myos
{
    namespace drivers
    {
        class KeyboardEventHandler
        {
        public:
            KeyboardEventHandler();

            virtual void OnKeyDown(char);
            virtual void OnKeyUp(char);
        };

        class KeyboardDriver : public myos::hardwarecommunication::InterruptHandler, public Driver
        {
            myos::hardwarecommunication::Port8Bit dataport;
            myos::hardwarecommunication::Port8Bit commandport;

            KeyboardEventHandler* handler;
        public:
            KeyboardDriver(myos::hardwarecommunication::InterruptManager* manager, KeyboardEventHandler* handler);
            ~KeyboardDriver();
            virtual myos::common::uint32_t HandleInterrupt(myos::common::uint32_t esp);
            char ScancodeToAsciicode(bool shift, myos::common::uint8_t key);
            virtual void Activate();
        };
    }
}


#endif