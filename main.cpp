//#pragma G++ target ("thumb")
#include "main.h"
#include "Startup.h"
#include "LED.h"

int GlobalInt = 3;
int GlobalInt2 = 3;
int GlobalIntUninit;

int main() {
    Startup::Run();

    int a = 0;
    int b = 2;
    GlobalIntUninit = a + b + GlobalInt;
    GlobalInt2 = GlobalIntUninit * 2;
    
    LEDManager::SetupLED();
    
    for (int i = 0; ; i++) {
        LEDManager::SetLED((i % 2) == 0);

        int waitLoop = (i < 50) ? 50000 : 500000;

        for (int i = 0; i < waitLoop; i++);
    }

    return 0;
}

