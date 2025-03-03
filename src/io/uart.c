#include "io/map.h"
#include "io/uart.h"
#include "io/mmio.h"
#include "io/gpio.h"

#define AUX_MU_BAUD(baud) ((AUX_UART_CLOCK/(baud*8))-1)

void uart_init() {
  mmio_write(AUX_ENABLES, 1); // enable UART1
  mmio_write(AUX_MU_IER_REG, 0);
  mmio_write(AUX_MU_CNTL_REG, 0);
  mmio_write(AUX_MU_LCR_REG, 3); // 8 bits
  mmio_write(AUX_MU_MCR_REG, 0);
  mmio_write(AUX_MU_IER_REG, 0);
  mmio_write(AUX_MU_IIR_REG, 0xC6); // disable interrupts
  mmio_write(AUX_MU_BAUD_REG, AUX_MU_BAUD(115200));
  gpio_useAsAlt5(14);
  gpio_useAsAlt5(15);
  mmio_write(AUX_MU_CNTL_REG, 3); // enable RX/TX
}

void uart_writeText(char *buffer) {
  while (*buffer) {
    if (*buffer == '\n') uart_writeByteBlockingActual('\r');
    uart_writeByteBlockingActual(*buffer++);
 }
}

unsigned int uart_isWriteByteReady() { 
  return mmio_read(AUX_MU_LSR_REG) & 0x20; 
}

void uart_writeByteBlockingActual(unsigned char ch) {
  while (!uart_isWriteByteReady()); 
  mmio_write(AUX_MU_IO_REG, (unsigned int)ch);
}
