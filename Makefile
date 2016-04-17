PROJECT=ol'inpiades
default: all
# Default Options
export ARCH  ?= dsPIC33F

export SDL   ?= yes
export DEBUG ?= _WARNING_

PARENT_DIR = ../


FLIP = no

EXESUFFIX = left
ifeq ($(FLIP), yes)
	CFLAGS+=-DFLIP
	EXESUFFIX = right
endif

# Constantes de compilation
EXEC    = yeux_char_$(EXESUFFIX)

include $(PARENT_DIR)/hardware/common.rules
################################################################################
# Fichiers du projet

FICHIERS_C =	\
	main.c		\
	affichage.c \
	framebuffer.c \
	sprite.c \
	keyanimation.c \
	eyedevil_sprites.c \
	eyedevil.c \
	demo_eyedevil.c \
	hardware_$(ARCH).c \
	font.c

FICHIERS_O  += $(addprefix $(BUILD_DIR)/, $(FICHIERS_C:.c=.o) )


################################################################################
# Compilation

all:$(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/$(EXEC): $(FICHIERS_O) libCommAsser libHardware
	@echo "	CC	$(PROJECT)|$@"
	@$(CC) -o $@ $(FICHIERS_O) $(CFLAGS) -lCommAsser -lHardware $(LDFLAGS)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
