#include "CommandHandler.h"
#include "SerialHandler.h"
#include "Kernel.h"
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
        
        Trace::Add("Recv", ((uint32 *)SerialHandler::SerialBuffer)[0], ((uint32 *)SerialHandler::SerialBuffer)[1]);

        CommandParser cp(SerialHandler::SerialBuffer);

        if (cp.Command.Equal("echo")) {
            SerialHandler::SendString("\n\r");
            SerialHandler::SendString(cp.Parameter[0]);
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

CommandParser::CommandParser(const void *data) {
    char *chars = (char *)data;
    uint32 index = 0;
    NumOfParameter = 0;
    
    // Trim
    while (true) {
        if (chars[index] == '\0') {
            Command = String("");
            return;
        }

        if (chars[index] != ' ') break;
        index++;
    }

    // Command string
    uint32 commandStart = index;
    while (!(chars[index] == ' ' || chars[index] == '\0')) index++;
    uint32 commandEnd = index;

    Command = String(&chars[commandStart], commandEnd - commandStart);

    Trace::Add("CP Cmd", *(uint32 *)Command.GetBuffer());

    while (chars[index] == ' ') index++;

    // No parameter
    if (chars[index] == '\0') return;
    
    // Parameter string
    while (true) {
        uint32 parameterStart = index;
        while (!(chars[index] == ' ' || chars[index] == '\0')) index++;
        uint32 parameterEnd = index;

        Parameter[NumOfParameter] = String(&chars[parameterStart], parameterEnd - parameterStart);
        
        Trace::Add("CP Param", *(uint32 *)Parameter[NumOfParameter].GetBuffer());
        
        NumOfParameter++;

        // Skip space
        while (chars[index] == ' ') index++;
        if (chars[index] == '\0') break;

        if (NumOfParameter == MAX_NUM_PARAMETER) break;
    }
}

CommandParser::~CommandParser() {
    Command.Release();
    
    for (uint32 i = 0; i < NumOfParameter; i++) {
        Parameter[i].Release();
    }
}