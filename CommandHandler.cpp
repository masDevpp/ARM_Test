#include "CommandHandler.h"
#include "SerialHandler.h"

void CommandHandler::Setup() {
    SerialHandler::Setup();

    SerialHandler::SendString((char *)"\n\r");
    Loop();
}

void CommandHandler::Loop() {
    for (uint32 i = 0; ; i++) {
        SerialHandler::SendByte((uint8)"0123456789ABCDEF"[(i&0xf)]);

        for (int i = 0; i < 400000; i++);
    }
}