#pragma once
#include "DataType.h"
#include "Memory.h"

class String {
public:
    String();
    String(const void *source, uint32 length = 0xffffffff);
    String(uint32 value, uint32 base = 10);
    ~String();
    
    bool Equal(String target);
    bool Equal(const void *target, uint32 length = 0xffffffff);
    String SubString(uint32 start, uint32 length = 0xffffffff);
    int32 IndexOf(char c);
    const uint8 *GetBuffer();

    uint32 Length;

public:
    static const uint32 BUFFER_LENGTH = Memory::SEGMENT_SIZE;
    uint8 *Buffer = nullptr;
};