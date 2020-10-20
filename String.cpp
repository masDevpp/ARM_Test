#include "String.h"
#include "Kernel.h"
#include "Trace.h"

String::String() {
    Trace::Add("StrDef");
}

String::String(const void *source, uint32 length) {
    Buffer = (uint8 *)Memory::Allocate(BUFFER_LENGTH, *(uint32 *)source);

    Trace::Add("StrBuf", (uint32)Buffer);

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
        value /= base;
    }

    // Reverse workBuffer char order
    for (uint32 i = 0; i < workBufferIndex; i++) {
        Buffer[i] = workBuffer[workBufferIndex - i - 1];
    }

    Length = workBufferIndex;
}
/*
String::~String() {
    Trace::Add("StrRelea", (uint32)Buffer);
    Memory::Release((uint32)Buffer);
}
*/
void String::Release() {
    if (Buffer != nullptr) {
        Memory::Release((uint32)Buffer);
    }
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

bool String::Equal(const void *target, uint32 length) {
    bool isEqual = false;
    uint8 *targ = (uint8 *)target;

    for (uint32 i = 0; i < length; i++) {
        isEqual = Buffer[i] == targ[i];

        if (!isEqual) break;

        if (Buffer[i] == '\0' || targ[i] == '\0') break;
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

bool String::ToUInt32(uint32 &value, uint32 base) {
    bool success = true;
    uint32 index = 0;
    value = 0;

    if (base == 0) {
        if (Buffer[0] == '0' && Buffer[1] == 'x') {
            base = 16;
            index = 2;
        } else {
            base = 10;
        }
    }

    if (!(base == 10 || base == 16)) return false;

    while (index < Length && Buffer[index] != '\0' && Buffer[index] != '\n' && Buffer[index] != '\r') {
        uint32 i = 0;
        for (; i < base; i++) {
            if (Buffer[index] == "0123456789ABCDEF"[i]) break;
            if (Buffer[index] == "0123456789abcdef"[i]) break;
        }

        success = i < base;
        if (!success) break;

        value *= base;
        value += i;

        index++;
    }

    return success;
}