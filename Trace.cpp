#include "Trace.h"

uint32 Trace::CurrentIndex = 0;
bool Trace::Wrapped = false;
TraceEntry *Trace::TraceBuffer;

void Trace::Setup() {
    TraceBuffer = (TraceEntry *)Memory::Allocate(NUM_ENTRY * sizeof(TraceEntry));
}

void Trace::Add(const void *id, uint32 value0, uint32 value1) {
    TraceBuffer[CurrentIndex].ID0 = *(uint32 *)id;
    TraceBuffer[CurrentIndex].ID1 = *(((uint32 *)id) + 1);
    TraceBuffer[CurrentIndex].Value0 = value0;
    TraceBuffer[CurrentIndex].Value1 = value1;

    CurrentIndex++;
    if (CurrentIndex >= NUM_ENTRY) {
        Wrapped = true;
        CurrentIndex = 0;
    }
}