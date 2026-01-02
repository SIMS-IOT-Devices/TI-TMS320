#include "driverlib.h"
#include "device.h"

void initSCI(void);
void SCI_writeString(const char *msg);

void main(void)
{
    Device_init();
    Device_initGPIO();

    initSCI();

    while(1)
    {
        SCI_writeString("Serial Communication Interface (SCI) Console\r\n");
        DEVICE_DELAY_US(1000000);   // 1 second
    }
}

void initSCI(void)
{
    // Configure SCI pins
    GPIO_setPinConfig(GPIO_28_SCIA_RX);
    GPIO_setPinConfig(GPIO_29_SCIA_TX);

    GPIO_setDirectionMode(28, GPIO_DIR_MODE_IN);
    GPIO_setDirectionMode(29, GPIO_DIR_MODE_OUT);

    // Reset SCI
    SCI_performSoftwareReset(SCIA_BASE);

    // Configure SCI
    SCI_setConfig(SCIA_BASE,
                  DEVICE_LSPCLK_FREQ,
                  115200,
                  (SCI_CONFIG_WLEN_8 |
                   SCI_CONFIG_STOP_ONE |
                   SCI_CONFIG_PAR_NONE));

    // Enable FIFO
    SCI_enableFIFO(SCIA_BASE);
    SCI_resetTxFIFO(SCIA_BASE);
    SCI_resetRxFIFO(SCIA_BASE);

    // Enable SCI module
    SCI_enableModule(SCIA_BASE);
}

void SCI_writeString(const char *msg)
{
    while(*msg)
    {
        SCI_writeCharBlockingFIFO(SCIA_BASE, *msg++);
    }
}
