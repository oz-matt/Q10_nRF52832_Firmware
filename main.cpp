#include "mbed.h"

DigitalOut led1(LED1);
Serial pc(USBTX, USBRX);
I2C i2c(p4, p3); //sda, scl

bool readI2cByte(uint8_t slave_addr, uint8_t mem_addr, char* data) {
    char cmd[1];
    cmd[0] = mem_addr;
    int ret = i2c.write(slave_addr, cmd, 1, false);
    wait(0.1);
    if (ret == 0) {
        ret = i2c.read(slave_addr, data, 1, false);
        if (ret == 0) return true;
    }
    return false;
}

int main() {
    while (true) {
        led1 = !led1;
        char data, data2;
        
        readI2cByte(0x84, 0xFD, &data);
        readI2cByte(0x84, 0xFE, &data2);
        
        pc.printf("yo123: %X, %X\r\n", data, data2);
        wait(1);
    }
}

