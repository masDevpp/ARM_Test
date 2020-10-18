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
        if (!SerialHandler::IsReceiveComplete) {
            Kernel::ThreadSleep();
            continue;
        }
        
        Trace::Add("Recv", *(uint32 *)SerialHandler::SerialBuffer);

        String receiveString(SerialHandler::SerialBuffer);
        String command;
        String parameter;

        Trace::Add("IdxOfSps", receiveString.IndexOf(' '));

        if (receiveString.IndexOf(' ') > 0) {
            Trace::Add("Cmd Ptr", *(uint32 *)SerialHandler::SerialBuffer);
            command = String(SerialHandler::SerialBuffer, receiveString.IndexOf(' '));

            Trace::Add("Parm Ptr", *(uint32 *)&SerialHandler::SerialBuffer[receiveString.IndexOf(' ') + 1]);
            parameter = String(&SerialHandler::SerialBuffer[receiveString.IndexOf(' ') + 1]);
        } else {
            command = receiveString;
        }

        if (command.Equal("echo")) {
            SerialHandler::SendString("\n\r");
            SerialHandler::SendString(parameter);
        }

        SerialHandler::SendString("\n\r>");
        SerialHandler::IsReceiveComplete = false;

        receiveString.Release();
        command.Release();
        parameter.Release();
    }
}

void CommandHandler::SerialInterrupt() {
    SerialHandler::SerialInterrupt();

    if (SerialHandler::LastReceiveByte != 0) {
        SerialHandler::SendByte(SerialHandler::LastReceiveByte);
    }
}