//#pragma G++ target ("thumb")
#include "main.h"
#include "Startup.h"
#include "LED.h"
#include "Timer.h"
#include "SerialHandler.h"
#include "SystemRegister.hh"

int LEDBlinkOverride = 0;
uint32 TimerElapse;

int main() {
    Startup::Run();

    LED::Setup();
    LED::Set(true);

    SerialHandler::Setup();
    SerialHandler::SendString((char *)"\n\rSystem start\n\r");

    Timer timer;
    timer.Setup();
    timer.Start();
    for (int i = 0; i< 1000000; i++) ;
    TimerElapse = timer.GetElapseMs();
    timer.Stop();

    // SysTick
    volatile SYST_CSR_reg *SYST_CSR = (SYST_CSR_reg *)0xE000E010;
    volatile SYST_RVR_reg *SYST_RVR = (SYST_RVR_reg *)0xE000E014;
    volatile SYST_CVR_reg *SYST_CVR = (SYST_CVR_reg *)0xE000E018;

    SYST_RVR->RELOAD = 0x00ffffff;
    SYST_CVR->CURRENT = 0x00ffffff;
    SYST_CSR->CLKSOURCE = true;
    SYST_CSR->ENABLE = true;
    SYST_CSR->TICKINT = true;

    SerialHandler::SendString((char *)"LED ready\n\r");
    
    for (int i = 0; ; i++) {
        LED::Set(!LED::Get());

        int waitLoop = (i < 50) ? 50000 : 500000;
        waitLoop = (LEDBlinkOverride == 0) ? waitLoop : LEDBlinkOverride;

        for (int i = 0; i < waitLoop; i++);
        //SerialHandler::SendByte((uint8)"0123456789ABCDEF"[(i&0xf)]);
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

void SysTickInterrupt() {
    static int count = 0;
    SerialHandler::SendByte((uint8)"0123456789ABCDEF"[(count&0xf)]);
    count++;
}