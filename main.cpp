#include "mbed.h"

DigitalOut led1(LED1);
Serial DONT_USE_SERIAL_PORT_LIKE_THIS(USBTX, p3);

int main() {

  while (true) {
    DONT_USE_SERIAL_PORT_LIKE_THIS.putc(DONT_USE_SERIAL_PORT_LIKE_THIS.getc());
  }
}
