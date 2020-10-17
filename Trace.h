#pragma once
#include "DataType.h"
#include "Memory.h"

class TraceEntry {
public:
    uint32 ID0;
    uint32 ID1;
    uint32 Value0;
    uint32 Value1;
};

class Trace {
public:
    static void Setup();
    static void Add(const void *id, uint32 value0=0, uint32 value1=0);

private:
    static const uint32 NUM_ENTRY = Memory::SEGMENT_SIZE * 16 / sizeof(TraceEntry);
    static uint32 CurrentIndex;
    static bool Wrapped;
    
    static TraceEntry *TraceBuffer;
};