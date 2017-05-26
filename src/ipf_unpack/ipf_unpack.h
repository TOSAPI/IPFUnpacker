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

// === Includes ===
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// === Types ===
typedef enum {
    ACTION_ENCRYPT,
    ACTION_DECRYPT,
    ACTION_EXTRACT,
}   PackAction;

// === Prototypes ===
void keys_generate (uint32_t *keys);
void keys_update   (uint32_t *keys, char b);
void ipf_decrypt (uint8_t *buffer, size_t size);
void ipf_encrypt (uint8_t *buffer, size_t size);

// === Defines ===
#ifndef LOBYTE
#define LOBYTE(w) ((uint8_t)(w))
#endif

#define BYTEN(x, n) (* ((uint8_t*)& (x)+n))
#define BYTE3(x)    BYTEN (x,  3)
