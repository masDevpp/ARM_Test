#include "CommandHandler.h"
#include "SerialHandler.h"

void CommandHandler::Setup() {
    SerialHandler::Setup();

    SerialHandler::SendString("\n\rSystem start\n\r");
    SerialHandler::SendString(">");
    Loop();
}

void CommandHandler::Loop() {
   while (true) {
       if (SerialHandler::IsReceiveComplete) {
           SerialHandler::SendString("\n\r");
           SerialHandler::SendString(SerialHandler::SerialBuffer);
           SerialHandler::SendString("\n\r>");
           SerialHandler::IsReceiveComplete = false;
       }
   }
}

void CommandHandler::SerialInterrupt() {
    SerialHandler::SerialInterrupt();

    if (SerialHandler::LastReceiveByte != 0) {
        SerialHandler::SendByte(SerialHandler::LastReceiveByte);
    }
}