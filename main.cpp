//#pragma G++ target ("thumb")
#include "main.h"
#include "Startup.h"
#include "LED.h"
#include "Timer.h"

int GlobalInt = 3;
int GlobalInt2 = 3;
int GlobalIntUninit;
int LEDBlinkOverride = 0;
uint32 TimerElapse;

int main() {
    Startup::Run();

    int a = 0;
    int b = 2;
    GlobalIntUninit = a + b + GlobalInt;
    GlobalInt2 = GlobalIntUninit * 2;

    Timer timer;
    timer.Setup();
    timer.Start();
    for (int i = 0; i< 2000000; i++) ;
    TimerElapse = timer.GetElapseMs();
    timer.Stop();
    
    LEDManager::SetupLED();
    
    for (int i = 0; ; i++) {
        LEDManager::SetLED((i % 2) == 0);

        int waitLoop = (i < 50) ? 50000 : 500000;
        waitLoop = (LEDBlinkOverride == 0) ? waitLoop : LEDBlinkOverride;

        for (int i = 0; i < waitLoop; i++);
    }

    return 0;
}

