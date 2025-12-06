#include "driverlib.h"
#include "device.h"

#define RED_LED 20

void main(void)
{
    // Initialize device clock and peripherals
    Device_init();

    // Initialize GPIO
    Device_initGPIO();

    // Configure LED GPIO
    GPIO_setPadConfig(RED_LED, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(RED_LED, GPIO_DIR_MODE_OUT);

    while(1)
    {
        GPIO_togglePin(RED_LED);  // Toggle LED
        DEVICE_DELAY_US(1000000); // 1 Sec delay
    }
}
