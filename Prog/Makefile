BOARD= nucleo_f303k8

# Couleur script shell à utiliser avec ${rouge}Bonjour${fin} et un @echo -e
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
	cd matrices ;\
	make all
	cd $(ori);\

	@echo "${rouge}+----------------[ Compilation terminée ]---------------+ ${fin}"

flash:
	@echo "${rouge}+---------------------[ Transfert ]---------------------+ ${fin}"
	openocd -f openocd/st_nucleo_f303k8.cfg -c "program /home/maxime/Bureau/mat/matrices/build/matrix.bin exit 0x08000000 reset"
	@echo "${rouge}+----------------[ Transfert terminé ]------------------+ ${fin}"

debug:
	@echo "${rouge}+-----------------------[ Debug ]-----------------------+ ${fin}"
	arm-none-eabi-gdb /home/maxime/Bureau/mat/matrices/build/matrix.elf --command=openocd/attach.gdb
	@echo "${rouge}+-------------------[ Debug terminé ]-------------------+ ${fin}"

doc:
	xreader /home/maxime/Bureau/Robotique/docHAL-F4.pdf& #à adapter en fonction de la machine

new:
	mkdir lib src

clean:
	cd matrices ;\
	make clean
	cd $(ori);\
	rm -f openocd/openocd.log
