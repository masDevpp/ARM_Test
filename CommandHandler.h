#pragma once
#include "DataType.h"

class CommandHandler {
public:
    static void Setup();
    static void Loop();

    static void SerialInterrupt();
};