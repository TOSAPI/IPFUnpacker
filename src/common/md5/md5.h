/*
 * IPFUnpacker is a free tool for extract and decrypt ipf files
 *
 * Spl3en <spl3en.contact@gmail.com> 2015 ~ 2016
 * Lara Maia <dev@lara.click> 2017
 *
 * IPFUnpacker is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * IPFUnpacker is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with IPFUnpacker.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdio.h>
#include <stdint.h>

// Size of MD5
#define MD5_SIZE 32

// ---------- Includes ------------
char * MD5_string (char *string);
void   MD5_stringEx (char *string, char *result);
char * MD5_buffer (uint8_t *buffer, size_t size);
void   MD5_bufferEx (uint8_t *buffer, size_t size, char *result);
char * MD5_file   (FILE *file);
