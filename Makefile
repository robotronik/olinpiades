PROJECT=ol'inpiades
default: all
# Default Options
export ARCH  ?= dsPIC33F

export SDL   ?= yes
export DEBUG ?= _WARNING_

PARENT_DIR = ../

# Constantes de compilation
EXEC    = yeux_char
PIC_ELF = $(EXEC).elf
PIC_HEX = $(EXEC).hex
include $(PARENT_DIR)/hardware/common.mk
################################################################################
# Fichiers du projet

FICHIERS_C =	\
	main.c		\
	affichage.c

# Fichier de hardware dépendant de l'architecture
HARDWARE_C = hardware_$(ARCH).c
FICHIERS_C+= $(HARDWARE_C) main.c

FICHIERS_O  += $(addprefix $(BUILD_DIR)/, $(FICHIERS_C:.c=.o) )

################################################################################
# Cibles du projet

.PHONY: all flash run

# Exécution pour le PIC.
$(PIC_HEX):$(EXEC)
	@echo "Converting to Intel HEX Format…"
	@/opt/xc16-toolchain-bin/bin/xc16-bin2hex $^ -a -omf=elf
	@echo "Done !"


ifeq ($(ARCH), PC)
# Exécution pour le PC.
run: all
	./$(EXEC)
endif

################################################################################
# Compilation

# The dependency for the hardware lib
$(HARDW_LIB): hardware_lib

all:$(EXEC)

$(EXEC): $(FICHIERS_O) $(COMMUNICATION_DIR)/$(BUILD_DIR)/libCommAsser.a $(HARDW_LIB)
	@echo "	CC	$(PROJECT)|$@"
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Librairies
.PHONY: $(COMMUNICATION_DIR)/$(BUILD_DIR)/libCommAsser.a

$(COMMUNICATION_DIR)/$(BUILD_DIR)/libCommAsser.a:
	@$(MAKE) -C $(COMMUNICATION_DIR) libCommAsser

################################################################################
# Cibles génériques

mrproper: clean
	@echo "Hard-cleaning $(PROJECT) directory…"
	@rm $(EXEC) $(PIC_HEX) $(PIC_ELF)
