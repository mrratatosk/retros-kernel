unsigned int gpio_call(unsigned int pin_number, unsigned int value, unsigned int base, unsigned int field_size, unsigned int field_max);

unsigned int gpio_set(unsigned int pin_number, unsigned int value);
unsigned int gpio_clear(unsigned int pin_number, unsigned int value);
unsigned int gpio_pull(unsigned int pin_number, unsigned int value);
unsigned int gpio_function(unsigned int pin_number, unsigned int value);

void gpio_useAsAlt5(unsigned int pin_number);