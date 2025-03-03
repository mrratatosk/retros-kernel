void uart_init();
unsigned int uart_isWriteByteReady();
void uart_writeByteBlockingActual(unsigned char ch);
void uart_writeText(char *buffer);