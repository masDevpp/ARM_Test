#pragma once
#include "DataType.h"
#include "String.h"

class CommandHandler {
public:
    static void Setup();
    static void Loop();

    static void SerialInterrupt();
};

class CommandParser {
public:
    CommandParser(const void *data);
    ~CommandParser();

    static const uint32 MAX_NUM_PARAMETER = 6;
    uint32 NumOfParameter;

    String Command;
    String Parameter[MAX_NUM_PARAMETER];
};
