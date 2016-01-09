#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#ifdef WIN32
    #include <windows.h>
#else
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <sys/mman.h>
#endif

uint8_t *file_map (char *filename, size_t *_size);
int file_flush (char *filename, void *data, size_t size);
int file_write (char *filename, uint8_t *buffer, size_t size);
int file_is_extension (char *filename, char *extension);