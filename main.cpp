//#pragma G++ target ("thumb")
#include "main.h"
#include "Startup.h"
#include "LED.h"
#include "Timer.h"
#include "SerialHandler.h"

int LEDBlinkOverride = 0;
uint32 TimerElapse;

int main() {
    Startup::Run();

    LEDManager::Setup();
    LEDManager::SetLED(true);

    SerialHandler::Setup();
    SerialHandler::SendString((char *)"\n\rSystem start\n\r");

    Timer timer;
    timer.Setup();
    timer.Start();
    for (int i = 0; i< 1000000; i++) ;
    TimerElapse = timer.GetElapseMs();
    timer.Stop();

    SerialHandler::SendString((char *)"LED ready\n\r");
    
    for (int i = 0; ; i++) {
        LEDManager::SetLED(!LEDManager::GetLED());

        int waitLoop = (i < 50) ? 50000 : 500000;
        waitLoop = (LEDBlinkOverride == 0) ? waitLoop : LEDBlinkOverride;

        for (int i = 0; i < waitLoop; i++);
        SerialHandler::SendByte((uint8)"0123456789ABCDEF"[(i&0xf)]);
    }

    return 0;
}

void SerialInterrupt() {
    SerialHandler::SerialInterrupt();
    
    if (SerialHandler::IsReceiveComplete) {
        SerialHandler::SendString((char *)"\n\r");
        SerialHandler::SendString((char *)SerialHandler::SerialBuffer);
        SerialHandler::SendString((char *)"\n\r");
    }
}