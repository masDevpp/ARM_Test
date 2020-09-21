#pragma GCC target ("thumb")
#include "main.h"

int GlobalInt = 3;
int GlobalInt2 = 3;
int GlobalIntUninit;

extern char* _data_load_source;
extern char* _data_load_size;
extern char* _data_load_destinatin;

int main() {
    loadMemory();

    int a = 0;
    int b = 2;
    GlobalIntUninit = a + b + GlobalInt;
    GlobalInt2 = GlobalIntUninit * 2;

    return 0;
}

void loadMemory() {
    for (int i = 0; i < (unsigned int)_data_load_size; i++) {
        _data_load_destinatin[i] = _data_load_source[i];
    }
}