#include "Memory.h"
#include "Kernel.h"
#include "Trace.h"

Segment *Memory::SegmentTable;
uint32 Memory::SegmentTableLength;
uint32 Memory::AddressHigh;
uint32 Memory::HeapStartAddress;
uint32 Memory::HeapSize;

void Memory::Setup() {
    extern char _heap_start[];
    extern char _heap_size[];

    HeapStartAddress = (uint64)_heap_start;
    HeapSize = (uint64)_heap_size;

    // Heap area contains heap usage control (Segment class) and data area
    // So one segment entry cosumes SEGMENT_SIZE + sizeof(Segment)
    SegmentTableLength = (uint32)(HeapSize / (sizeof(Segment) + SEGMENT_SIZE));

    // Data area follow segment table
    uint32 dataStartAddress = HeapStartAddress + sizeof(Segment) * SegmentTableLength;
    AddressHigh = dataStartAddress & ADDRESS_HIGH_MASK;

    // SegmentTable locate at top of heap
    SegmentTable = (Segment *)HeapStartAddress;

    for (uint32 i = 0; i < SegmentTableLength; i++) {
        SegmentTable[i].AddressLow = ((dataStartAddress + (i * SEGMENT_SIZE)) & ADDRESS_LOW_MASK);
        SegmentTable[i].Used = false;
        SegmentTable[i].Last = false;
        SegmentTable[i].Reserved = 0;
    }
}

uint32 Memory::Allocate(uint32 size, uint32 owner) {
    Trace::Add("Malloc", size, owner);

    Segment *availableSegment;
    uint32 continuousFreeSize = 0;
    bool found = false;

    // Search continous free segment
    for (uint32 i = 0; i < SegmentTableLength; i++) {
        if (SegmentTable[i].Used) {
            continuousFreeSize = 0;

        } else {
            if (continuousFreeSize == 0) availableSegment = &SegmentTable[i];
            continuousFreeSize += SEGMENT_SIZE;
        }

        if (continuousFreeSize >= size) {
            SegmentTable[i].Last = true;
            found = true;
            break;
        }
    }

    if (!found) Kernel::Assert();

    Segment *currentSegment = availableSegment;
    
    while (true) {
        // Set segment table as used
        currentSegment->Used = true;

        // Zero clear
        uint8 *addr = (uint8 *)(AddressHigh + currentSegment->AddressLow);
        for (uint32 i = 0; i < SEGMENT_SIZE; i++) {
            addr[i] = 0;
        }

        // Last segment is already marked as last
        if (currentSegment->Last) break;
        currentSegment++;
    }

    Trace::Add("Malloced", AddressHigh + availableSegment->AddressLow);

    return AddressHigh + availableSegment->AddressLow;
}

void Memory::Release(uint32 address) {
    Trace::Add("MemReles", address);

    bool found = false;

    for (uint32 i = 0; i < SegmentTableLength; i++) {
        // Search segment table
        if (SegmentTable[i].AddressLow == (address & ADDRESS_LOW_MASK)) {
            found = true;
        }

        // Clear used bit and last bit
        if (found) {
            SegmentTable[i].Used = false;

            if (SegmentTable[i].Last) {
                SegmentTable[i].Last = false;
                break;
            }
        }
    }

    if (!found) Kernel::Assert();
}
