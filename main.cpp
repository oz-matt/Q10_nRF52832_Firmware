#include "mbed.h"
#include "BufferedSerial.h" // We need this library so that we can easily manage incoming UART data

Serial pc(USBTX, USBRX);

char ubx_command_1[8] = {0xF2, 0x65, 0x08, 0x06, 0x00, 0x00, 0x00, 0x04}; // Note: There are 0x00s (nulls) as part of the data! This will screw with any strlen, strcpy type of thing you do with this array!
char ubx_command_2[11] = {0xF2, 0x65, 0x18, 0x31, 0xBB, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x04};
char ubx_command_3[8] = {0xF2, 0x65, 0x0A, 0x3A, 0x02, 0x00, 0x00, 0x0F};

// Simply send UART characters to the EVAM8Q without killing our debug output.
void send_evam8q_chars_and_receive(char* response, int expected_response_length, char* sendstr, int length) {
  BufferedSerial EvaSerial(p3, p4); // Seize Hardware UART for the moment

  int i, j;

  for(i=0;i<length;i++) {
    EvaSerial.putc(sendstr[i]); // Send chars one at a time from the buffer to the Eva
    // Note, we can't do 'EvaSerial.printf(ubx_command_1)' because these commands contain NULLs (0x00). This will be
    // interpreted as 'This is the end of the string!' by printf, and stop sending after the first 0x00.
  }

  wait(1); // Wait for response from EVA.

  if (EvaSerial.readable()) { // Did we get at least one char from the eva?
    for(j=0;j<expected_response_length;j++) {
      response[j] = EvaSerial.getc(); // Copy the contents of the rx buffer to our local buffer;
    }
  }

  Serial dummy(USBTX, USBRX); // Change the hardware UART pins back to the debug port. Use 'pc.printf("hi");' as normal' after this
}

int main() {

  char response_buffer[256];
  int expected_length = 30; // This can be determined for each command you want to run from the dreaded document.
  int i;

  wait(1); // Wait 1 second

  pc.printf("Starting.\r\n");

  wait(1);

  send_evam8q_chars_and_receive(response_buffer, expected_length, ubx_command_1, 8); // Again, we can't use something like 'strlen(ubx_command_1)' for the length. We have to use 8.
  // This is cuz 'strlen' will get confused and stop counting at the first 0x00 character.

  pc.printf("Got response: \r\n");

  for(i=0;i<expected_length;i++) {
    pc.printf("%X ", response_buffer[i]);
  }

}
