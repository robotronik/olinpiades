
install_udev:
	@sudo ./hal_common/install_udev.sh

build:
	meson _build --cross-file stm32f303.meson
	ninja -C _build
	cd _build; echo "_build open"; \
		ninja olinpiades.flash

