#include "CommandHandler.h"
#include "SerialHandler.h"
#include "Kernel.h"
#include "String.h"

void CommandHandler::Setup() {
    SerialHandler::Setup();

    SerialHandler::SendString("\n\rSystem start\n\r");
    SerialHandler::SendString(">");
    Loop();
}

void CommandHandler::Loop() {
    while (true) {
        if (!SerialHandler::IsReceiveComplete) continue;
        
        SerialHandler::SendString("\n\r");
        SerialHandler::SendString(SerialHandler::SerialBuffer);
        SerialHandler::SendString("\n\r");

        String receiveString(SerialHandler::SerialBuffer);
        String command = nullptr;
        String parameter = nullptr;

        if (receiveString.IndexOf(' ') > 0) {
            command = String(SerialHandler::SerialBuffer, receiveString.IndexOf(' '));
            parameter = String(&SerialHandler::SerialBuffer[receiveString.IndexOf(' ') + 1]);
        } else {
            command = receiveString;
        }

        SerialHandler::SendString(command.GetBuffer());
        SerialHandler::SendString("\n\r");

        if (command.Equal(String("echo"))) {
            SerialHandler::SendString(parameter.GetBuffer());
        }

        SerialHandler::SendString("\n\r>");
        SerialHandler::IsReceiveComplete = false;
    }
}

void CommandHandler::SerialInterrupt() {
    SerialHandler::SerialInterrupt();

    if (SerialHandler::LastReceiveByte != 0) {
        SerialHandler::SendByte(SerialHandler::LastReceiveByte);
    }
}