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

#include <zlib.h>
#include <stdint.h>

#define ZLIB_MAGIC_HEADER 0xFA8D

#define ZLIB_GET_COMPRESSED_PACKET_SIZE(_zlib, _pktSize) \
    (_zlib)->header.size + sizeof(ZlibHeader) + (_pktSize - sizeof(Zlib));

typedef struct {
uint16_t magic;
    uint32_t size;
} ZlibHeader;

typedef struct {
    ZlibHeader header;
    uint8_t buffer [1024 * 1024 * 100]; // Maximum decompressed file : 100Mo
} Zlib;

/**
 * @brief : Compress a given data to a Zlib
 */
int zlibCompress(Zlib *self, void *data, size_t dataSize);

/**
 * @brief : Decompress a given data to a Zlib
 */
int zlibDecompress(Zlib *self, void *data, size_t dataSize);
