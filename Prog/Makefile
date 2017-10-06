BOARD= f4
PROJECT_DIR= matrices
PROJECT_NAME= matrix

rouge = \033[0;31m
vert = \033[0;32m
bleu = \033[0;34m
fin = \033[0m
vert_gras = \033[0;1;4;32m
fin_gras = \033[0;21m

ori=$(CURDIR)

c:
	make comp

f:
	make flash

d:
	make debug

cf:
	make comp
	make flash

comp:
	@echo "${rouge}+--------------------[ Compilation ]--------------------+ ${fin}"
	cd $(PROJECT_DIR) ;\
	make all
	cd $(ori);\

	@echo "${rouge}+----------------[ Compilation terminée ]---------------+ ${fin}"

flash:
	@echo "${rouge}+---------------------[ Transfert ]---------------------+ ${fin}"
	openocd -f openocd/$(BOARD).cfg -c "program $(PROJECT_DIR)/build/$(PROJECT_NAME).bin exit 0x08000000 reset"
	@echo "${rouge}+----------------[ Transfert terminé ]------------------+ ${fin}"

debug:
	@echo "${rouge}+-----------------------[ Debug ]-----------------------+ ${fin}"
	arm-none-eabi-gdb $(PROJECT_DIR)/build/$(PROJECT_NAME).elf --command=openocd/attach_$(BOARD).gdb
	@echo "${rouge}+-------------------[ Debug terminé ]-------------------+ ${fin}"

doc:
	xreader /home/maxime/Documents/docHAL/docHAL-$(BOARD).pdf &

clean:
	cd $(PROJECT_DIR) ;\
	make clean
	cd $(ori);\
	rm -f openocd/openocd.log
