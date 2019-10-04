project('display_test', 'c')

add_project_arguments('-D uint_8=unsigned char', language: 'c')
add_project_arguments('-D uint_32=unsigned int', language: 'c')

executable('display_test', ['PC_decode_test.c', '../frames_get.c', '../frames_definition.c'])
