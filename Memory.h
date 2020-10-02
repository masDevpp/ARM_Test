#include "DataType.h"

void memset(void *buf, int ch, uint32 n);

class Segment {
public:
    // Lower 16bit of heap address
    uint16 AddressLow;
    bool Used = false;
    bool Last = false;
};

class Memory {
public:
    static void Setup();
    static uint32 Allocate(uint32 size);
    static void Release(uint32 address);

    static const uint32 SEGMENT_NOT_AVAILABLE = 0xffffffff;

private:
    static const uint32 SEGMENT_SIZE = 0x80;
    static Segment *SegmentTable;
    static uint32 SegmentTableLength;

    // To save memory, SegmentTable contains lower 16bit of heap address;
    // Higher 16bit is stored here
    static uint32 AddressHigh;

    static uint32 HeapStartAddress;
    static uint32 HeapSize;
};

