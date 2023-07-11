#include "keyboard.h"

KeyboardDriver::KeyboardDriver(InterruptManager* manager)
:InterruptHandler(0x21,manager),
dataport(0x60),
commandport(0x64)
{}

KeyboardDriver::~KeyboardDriver(){}

void printf(char*);
void printfHex(uint8_t);

void KeyboardDriver::Activate()
{
    while(commandport.Read() & 0x1)
        dataport.Read();
    commandport.Write(0xAE);                        //activate interrupts
    commandport.Write(0x20);                        //get current state
    uint8_t status = (dataport.Read() | 1) & ~0x10;
    commandport.Write(0x60);                        //set state
    dataport.Write(status);

    dataport.Write(0xF4);
}

uint8_t KeyboardDriver::ScancodeToAsciicode(bool shift,uint8_t key)
{
    switch (key)
    {
    case 0x2A: return 0x10;break; 
    case 0x29: if(shift) return '~'; else return '`';break; //`
    case 0x02: if(shift) return '!'; else return '1';break; //1
    case 0x03: if(shift) return '@'; else return '2';break; //2
    case 0x04: if(shift) return '#'; else return '3';break;
    case 0x05: if(shift) return '$'; else return '4';break;
    case 0x06: if(shift) return '%'; else return '5';break;
    case 0x07: if(shift) return '^'; else return '6';break;
    case 0x08: if(shift) return '&'; else return '7';break;
    case 0x09: if(shift) return '*'; else return '8';break;
    case 0x0A: if(shift) return '('; else return '9';break;
    case 0x0B: if(shift) return ')'; else return '0';break; //0
    case 0x0C: if(shift) return '_'; else return '-';break; //-
    case 0x0D: if(shift) return '+'; else return '=';break; //=
    case 0x0E: return 0x08;break; //backspace
    case 0x0F: return 0x09;break; //tab
    case 0x35: return 0x2F;break; //'/'
    case 0x37: return 0x2A;break; //'*'
    case 0x4A: return 0x2D;break; //-
    case 0x10: if(shift) return 'Q'; else return 'q';break;
    case 0x11: if(shift) return 'W'; else return 'w';break;
    case 0x12: if(shift) return 'E'; else return 'e';break;
    case 0x13: if(shift) return 'R'; else return 'r';break;
    case 0x14: if(shift) return 'T'; else return 't';break;
    case 0x15: if(shift) return 'Y'; else return 'y';break;
    case 0x16: if(shift) return 'U'; else return 'u';break;
    case 0x17: if(shift) return 'I'; else return 'i';break;
    case 0x18: if(shift) return 'O'; else return 'o';break;
    case 0x19: if(shift) return 'P'; else return 'p';break;
    case 0x1A: if(shift) return '{'; else return '[';break;
    case 0x1B: if(shift) return '}'; else return ']';break;
    case 0x2B: if(shift) return '|'; else return '\\';break;
    case 0x47: return '7';break;
    case 0x48: return '8';break;
    case 0x49: return '9';break;
    case 0x4E: return '+';break;
    case 0x3A: return 0x14;break;   //CapsLk
    case 0x1E: if(shift) return 'A'; else return 'a';break;
    case 0x1F: if(shift) return 'S'; else return 's';break;
    case 0x20: if(shift) return 'D'; else return 'd';break;
    case 0x21: if(shift) return 'F'; else return 'f';break;
    case 0x22: if(shift) return 'G'; else return 'g';break;
    case 0x23: if(shift) return 'H'; else return 'h';break;
    case 0x24: if(shift) return 'J'; else return 'j';break;
    case 0x25: if(shift) return 'K'; else return 'k';break;
    case 0x26: if(shift) return 'L'; else return 'l';break;
    case 0x27: if(shift) return ':'; else return ';';break;
    case 0x28: if(shift) return '\"'; else return '\'';break;
    case 0x1C: return '\n';break;
    case 0x4B: return '4';break;
    case 0x4C: return '5';break;
    case 0x4D: return '6';break;
    case 0x2C: if(shift) return 'Z'; else return 'z';break;
    case 0x2D: if(shift) return 'X'; else return 'x';break;
    case 0x2E: if(shift) return 'C'; else return 'c';break;
    case 0x2F: if(shift) return 'V'; else return 'v';break;
    case 0x30: if(shift) return 'B'; else return 'b';break;
    case 0x31: if(shift) return 'N'; else return 'n';break;
    case 0x32: if(shift) return 'M'; else return 'm';break;
    case 0x33: if(shift) return '<'; else return ',';break;
    case 0x34: if(shift) return '>'; else return '.';break;
    
    default:
        return 0;
        break;
    }
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t key = dataport.Read();

     if(key < 0x80)
    {
        switch (key)
        {
        case 0xFA: break;
        case 0x45:
        case 0xC5: break;
  
        default:
            char* scan_ = " ";
            static bool shift = false;
            char asciicode = ScancodeToAsciicode(shift,key);
            if(asciicode == 0x10)
            {
                scan_ = "shift!";
                shift = !shift;
                printf(scan_);
            }
            else if(asciicode == '\n')
            {
                scan_[0] = '\n';
                printf(scan_);
            } 
            else if(asciicode >= 0x20)
            {
                scan_[0] = asciicode;
                printf(scan_);
            }
            else
            {
                printf("KETBOARD 0x");
                printfHex(key);
            }   
            break;
        }
    } 
    
    
    return esp;
}
