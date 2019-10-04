
install_udev:
	@sudo ./install_udev.sh

build:
	meson _build --cross-file stm32f303.meson
	ninja -C _build
