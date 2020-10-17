#include "String.h"
#include "Kernel.h"

String::String(const void *source, uint32 length) {
    Buffer = (uint8 *)Memory::Allocate(BUFFER_LENGTH, *(uint32 *)source);

    uint32 i = 0;
    for (; (i < BUFFER_LENGTH && i < length); i++) {
        Buffer[i] = ((uint8 *)source)[i];
        
        if (Buffer[i] == '\0') break;
    }

    Buffer[i] = '\0';

    Length = i;
}

String::String(uint32 value, uint32 base) {
    if (!(base == 10 || base == 16)) Kernel::Assert();

    Buffer = (uint8 *)Memory::Allocate(BUFFER_LENGTH);

    uint8 workBuffer[16];
    uint32 workBufferIndex = 0;

    while (value > 0) {
        workBuffer[workBufferIndex] = "0123456789ABCDEF"[value % base];
        workBufferIndex++;
    }

    // Reverse workBuffer char order
    for (uint32 i = 0; i < workBufferIndex; i++) {
        Buffer[i] = workBuffer[workBufferIndex - i - 1];
    }

    Length = workBufferIndex;
}

String::~String() {
    Memory::Release((uint32)Buffer);
}

bool String::Equal(String target) {
    bool isEqual = false;

    if (Length == target.Length) {
        for (uint32 i = 0; i < Length; i++) {
            isEqual = Buffer[i] == target.Buffer[i];
            if (!isEqual) break;
        }
    }

    return isEqual;
}

String String::SubString(uint32 start, uint32 length) {
    String subString(this->Buffer + start, length);

    return subString;
}

int32 String::IndexOf(char c) {
    int32 index = -1;

    for (int32 i = 0; i < (int32)Length; i++) {
        if (Buffer[i] == c) {
            index = i;
            break;
        }
    }

    return index;
}

const uint8 *String::GetBuffer() {
    return Buffer;
}