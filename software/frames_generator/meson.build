
run_target('regenerate_frames_files',
  command: [ find_program('generate.py') ],
)


executable('display_test',
  'PC_decode_test.c',
  'frames_definition.c',
  'frames_get.c',
  native: true,
)


lib_frames = static_library('frames',
  'frames_definition.c',
  'frames_get.c',
  pic: false,
)
