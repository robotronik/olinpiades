project('we_will_win_olinpiades',
  'c', 'cpp',
  default_options: [
    'buildtype=plain',
    'b_lto=false',
    'warning_level=3',
    'c_std=gnu11',
    'cpp_std=gnu++17',
  ],
)

libopencm3_mcu = 'stm32f3'
linkscript_mcu = 'stm32f303'

cc = meson.get_compiler('c')

c_args = []

###############################################################################
# Some low level definitions
cpu = host_machine.cpu() == 'cortex-m0+' ? 'cortex-m0plus' : host_machine.cpu()
c_args += '-mcpu=@0@'.format( cpu )

objcopy = meson.get_cross_property('objcopy')
size    = meson.get_cross_property('size')
openocd = find_program('openocd')

system_libraries = [
  cc.find_library('nosys'),
  cc.find_library('stdc++_nano'),
  cc.find_library('m'),
  cc.find_library('c'),
  cc.find_library('g'),
  cc.find_library('rdimon'),
]


add_project_arguments([
    '-Werror=implicit-function-declaration',
  ],
  language: [ 'c', 'cpp' ],
)

###############################################################################
# Libopencm3

libopencm3_dir = 'hal_common/libopencm3'

run_target('libopencm3',
  command: [ 'make', '-C', libopencm3_dir,
    '-j', 'lib/stm32/f3',
  ],
)

libopencm3_include = include_directories(libopencm3_dir / 'include')
libopencm3_defines = [ '-D@0@'.format(libopencm3_mcu.to_upper()) ]
libopencm3_library = cc.find_library(
  'opencm3_@0@'.format(libopencm3_mcu),
  dirs: meson.source_root() / libopencm3_dir / 'lib',
  required: false,
)

if not libopencm3_library.found()
  warning('Libopencm3 library not found, please run "ninja libopencm3"')
endif

libopencm3 = declare_dependency(
  compile_args:         libopencm3_defines,
  include_directories:  libopencm3_include,
  dependencies:         libopencm3_library,
)

###############################################################################
# Linking

linker_script_dir = meson.source_root() / 'hal_common/linker_scripts'
linker_script_link = [
  '-T', linker_script_dir / '@0@.ld'.format(linkscript_mcu),
  '-L' + meson.source_root() / libopencm3_dir / 'lib',
]

###############################################################################
# Flashing

openocd_config = '/usr/share/openocd/scripts/board/st_nucleo_f3.cfg'

run_target('install_udev',
  command: [ meson.source_root() / 'install_udev.sh' ],
)

###############################################################################
# Project


lowlevel = static_library('lowlevel',
  'lowlevel/clock.c',
  'lowlevel/matrix_driver.c',
  'lowlevel/uart.c',
  dependencies: libopencm3,
  pic: false,
)

subdir('frames_generator')

#############################
# Final executables

executables = []

executables += executable('olinpiades.elf',
  'main.c',
  'synchronize.c',
  link_with: [
    lowlevel,
    lib_frames,
  ],
  dependencies: [
    system_libraries,
    libopencm3,
  ],
  link_args: linker_script_link,
)



foreach exe : executables
  exe_name = exe.full_path().split('/')[-1].split('.elf')[0]
  message(exe_name)

  bin_name  = '@0@.bin'.format(exe_name)
  hex_name  = '@0@.hex'.format(exe_name)
  size_name = '@0@.siz'.format(exe_name)

  bin = custom_target(bin_name,
    input : exe,
    output: bin_name,
    command: [ objcopy, '-O', 'binary', '@INPUT@', '@OUTPUT@' ],
    build_by_default: true,
  )

  hex = custom_target(hex_name,
    input : exe,
    output: hex_name,
    command: [ objcopy, '-O', 'ihex', '@INPUT@', '@OUTPUT@' ],
    build_by_default : true,
  )

  custom_target(size_name,
    input : exe,
    output: size_name,
    command: [ size, '--format=berkeley', '@INPUT@' ],
    capture: true,
    build_by_default: true,
  )


  custom_target('@0@.flash'.format(exe_name),
    input : hex,
    output: '@0@.flash'.format(exe_name),
    depends: hex,
    console: true,
    command: [
      openocd, '-f', openocd_config,
      '-c', 'init',
      '-c', 'reset init',
      '-c', 'flash write_image erase @0@'.format(hex.full_path()),
      '-c', 'reset',
      '-c', 'shutdown',
    ],
  )
endforeach


executable('tests_native',
  'main_tests_native.cpp',
  'synchronize.c',
  native: true,
)
