#pragma once
#include "DataType.h"

typedef struct SegmentStruct {
    uint32 AddressLow : 28;
    uint32 Used       : 1;
    uint32 Last       : 1;
    uint32 Reserved   : 2;
    uint32 Owner;
} Segment;

class Memory {
public:
    static void Setup();
    static uint32 Allocate(uint32 size, uint32 owner = 0xffffffff);
    static void Release(uint32 address);

    static const uint32 SEGMENT_NOT_AVAILABLE = 0xffffffff;
    static const uint32 SEGMENT_SIZE = 0x80;

private:
    static Segment *SegmentTable;
    static uint32 SegmentTableLength;

    static const uint32 ADDRESS_HIGH_MASK = 0xf0000000;
    static const uint32 ADDRESS_LOW_MASK  = 0x0fffffff;

    // To save memory, SegmentTable contains lower 28bit of heap address;
    // Higher 4bit is stored here
    static uint32 AddressHigh;

    static uint32 HeapStartAddress;
    static uint32 HeapSize;
};

