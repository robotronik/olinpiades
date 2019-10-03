default: _default
###############################################################################
# Project options

TARGET = matrix

DEBUG = 1

# optimization
OPT = -Og

BUILD_DIR = build

BOARD = st_nucleo_f3


###############################################################################
# Binaries

# PREFIX = arm-none-eabi-
PREFIX =
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
AR = $(PREFIX)ar
SZ = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

###############################################################################
# CFLAGS
CFLAGS =

# MCU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

CFLAGS += $(MCU)

CFLAGS += -Wall -fdata-sections -ffunction-sections

CFLAGS += -DUSE_HAL_DRIVER -DSTM32F303x8

# C includes
CFLAGS +=  \
	-Isrc \
	-IDrivers/CMSIS/Device/ST/STM32F3xx/Include \
	-IDrivers/CMSIS/Include \
	-IDrivers/STM32F3xx_HAL_Driver/Inc \
	-IDrivers/STM32F3xx_HAL_Driver/Inc/Legacy

CFLAGS += $(OPT)

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"


###############################################################################
# LDFLAGS
LDFLAGS =

LDSCRIPT = STM32F303K8Tx_FLASH.ld

LDFLAGS += $(MCU) -T$(LDSCRIPT)

LDFLAGS += -specs=nano.specs -Wl,--gc-sections

LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref

LDFLAGS += -lc -lm -lnosys

###############################################################################
# source

HAL_Sources = \
	Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.c \
	Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.c \
	Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.c \
	Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.c \
	Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.c \
	Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.c \
	Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c \
	Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.c \
	Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.c \
	Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.c \
	Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.c \
	Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim_ex.c \
	Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim.c \
	Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.c \
	Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c \
	Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.c \

C_SOURCES = $(HAL_Sources) \
	src/blink.c \
	src/main_hal.c \
	src/main.c \
	src/stm32f3xx_hal_msp.c \
	src/stm32f3xx_it.c \
	src/system_stm32f3xx.c \
	src/udelay.c\
	src/write_matrix.c

# ASM sources
ASM_SOURCES =  \
	src/startup_stm32f303x8.s


###############################################################################
# Compile rules

# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR):
	mkdir $@

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile | $(BUILD_DIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@


_default: $(BUILD_DIR)/$(TARGET).bin

###############################################################################
# clean up

clean:
	-rm -fR .dep $(BUILD_DIR)
	-rm -f openocd/openocd.log

###############################################################################
# dependencies

-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)


###############################################################################
# Custom rules

rouge = \033[0;31m
vert = \033[0;32m
bleu = \033[0;34m
fin = \033[0m
vert_gras = \033[0;1;4;32m
fin_gras = \033[0;21m


.PHONY: f
f: flash

flash:
	@echo "${rouge}+---------------------[ Transfert ]---------------------+ ${fin}"
	openocd -f openocd/$(BOARD).cfg \
		-c "program $(BUILD_DIR)/$(PROJECT_NAME).bin exit 0x08000000 reset"
	@echo "${rouge}+----------------[ Transfert terminé ]------------------+ ${fin}"


.PHONY: d
d: flash

debug:
	@echo "${rouge}+-----------------------[ Debug ]-----------------------+ ${fin}"
	arm-none-eabi-gdb "$(BUILD_DIR)/$(PROJECT_NAME).elf" \
		--command=openocd/attach_$(BOARD).gdb
	@echo "${rouge}+-------------------[ Debug terminé ]-------------------+ ${fin}"
