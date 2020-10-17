#include "CommandHandler.h"
#include "SerialHandler.h"
#include "Kernel.h"
#include "String.h"
#include "Trace.h"

void CommandHandler::Setup() {
    SerialHandler::Setup();

    SerialHandler::SendString("\n\rSystem start\n\r");
    SerialHandler::SendString(">");
    Loop();
}

void CommandHandler::Loop() {
    while (true) {
        if (!SerialHandler::IsReceiveComplete) continue;
        
        Trace::Add("Recv", *(uint32 *)SerialHandler::SerialBuffer);

        SerialHandler::SendString("\n\r");
        SerialHandler::SendString(SerialHandler::SerialBuffer);
        SerialHandler::SendString("\n\r");

        String receiveString(SerialHandler::SerialBuffer);
        String command = nullptr;
        String parameter = nullptr;

        Trace::Add("IdxOfSps", receiveString.IndexOf(' '));

        if (receiveString.IndexOf(' ') > 0) {
            Trace::Add("Cmd Ptr", *(uint32 *)SerialHandler::SerialBuffer);
            command = String(SerialHandler::SerialBuffer, receiveString.IndexOf(' '));

            Trace::Add("Parm Ptr", *(uint32 *)&SerialHandler::SerialBuffer[receiveString.IndexOf(' ') + 1]);
            parameter = String(&SerialHandler::SerialBuffer[receiveString.IndexOf(' ') + 1]);
        } else {
            command = receiveString;
        }

        SerialHandler::SendString(command);
        SerialHandler::SendString("\n\r");

        if (command.Equal("echo")) {
            SerialHandler::SendString(parameter);
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