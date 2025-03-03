SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = out
OBJ_DIR = $(BUILD_DIR)/obj
ELF_DIR = $(BUILD_DIR)/elf

C_FILES = $(wildcard src/io/*.c src/kernel/*.c)
S_FILES = $(wildcard src/boot/*.S)

OBJ_FILES = $(subst src,$(OBJ_DIR),$(C_FILES:%.c=%.o) $(S_FILES:%.S=%.o))

GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles -I$(INCLUDE_DIR)

all: clean init kernel8.img

init:
	echo $(OBJ_FILES)
	mkdir -p $(ELF_DIR)

$(OBJ_DIR)/io/%.o: $(SRC_DIR)/io/%.c
	mkdir -p $(@D)
	gcc $(GCCFLAGS) -c $< -o $@
	
$(OBJ_DIR)/kernel/%.o: $(SRC_DIR)/kernel/%.c 
	mkdir -p $(@D)
	gcc $(GCCFLAGS) -c $< -o $@

$(OBJ_DIR)/boot/%.o: $(SRC_DIR)/boot/%.S
	mkdir -p $(@D)
	gcc $(GCCFLAGS) -c $< -o $@
	
kernel8.img: $(OBJ_FILES)
	ld -nostdlib $(OBJ_FILES) -T $(SRC_DIR)/boot/link.ld -o $(ELF_DIR)/kernel8.elf
	objcopy -O binary $(ELF_DIR)/kernel8.elf $(BUILD_DIR)/kernel8.img

clean:
	/bin/rm -rf $(BUILD_DIR) > /dev/null 2> /dev/null || true