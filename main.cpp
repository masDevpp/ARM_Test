//#pragma G++ target ("thumb")
#include "main.h"
#include "Startup.h"
#include "LED.h"
#include "Timer.h"
#include "SerialHandler.h"

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
    
    SerialHandler serial;
    serial.Setup();
    serial.SendString("\n\rSystem start\n\r");

    Timer timer;
    timer.Setup();
    timer.Start();
    for (int i = 0; i< 2000000; i++) ;
    TimerElapse = timer.GetElapseMs();
    timer.Stop();

    LEDManager::SetupLED();
    serial.SendString("LED ready\n\r");
    
    for (int i = 0; ; i++) {
        LEDManager::SetLED((i % 2) == 0);

        int waitLoop = (i < 50) ? 50000 : 500000;
        waitLoop = (LEDBlinkOverride == 0) ? waitLoop : LEDBlinkOverride;

        for (int i = 0; i < waitLoop; i++);
        serial.SendByte((uint8)"0123456789ABCDEF"[(i&0xf)]);
    }

    return 0;
}

