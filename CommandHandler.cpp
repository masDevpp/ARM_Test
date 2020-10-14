#include "CommandHandler.h"
#include "SerialHandler.h"

void CommandHandler::Setup() {
    SerialHandler::Setup();

    SerialHandler::SendString((char *)"\n\rSystem start\n\r");
    Loop();
}

void CommandHandler::Loop() {
   while (true) {
       if (SerialHandler::IsReceiveComplete) {
           SerialHandler::SendString((char *)SerialHandler::SerialBuffer);
           SerialHandler::SendString((char *)"\n\r");
           SerialHandler::IsReceiveComplete = false;
       }
   }
}

void CommandHandler::SerialInterrupt() {
    SerialHandler::SerialInterrupt();
}