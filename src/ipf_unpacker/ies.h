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

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#pragma pack (push, 1)
typedef struct {
    char tableName[128];

    uint32_t unk1;
    uint32_t dataOffset;
    uint32_t resourceOffset;
    uint32_t fileSize;
    
    uint16_t unk2;
    uint16_t rowsCount;
    uint16_t colsCount;
    uint16_t intColsCount;
    uint16_t strColsCount;
    uint16_t unk3;
} IesHeader;
#pragma pack (pop)

#pragma pack (push, 1)
typedef struct {
    char name[64];
    char name2[64];
    uint16_t type;
    uint16_t unk1;
    uint16_t unk2;
    uint16_t position;
} IesColumn;
#pragma pack (pop)

#define IesCellOpt(_optSize)    \
struct {                        \
    uint32_t unk;               \
    uint16_t size;              \
    char name[_optSize];        \
}

#define IesCell(_optSize, _strSize)         \
struct {                                    \
    size_t optSize; size_t strSize;         \
    IesColumn *col;                         \
    IesCellOpt(_optSize) opt;               \
    union {                                 \
        struct {                            \
            float value;                    \
        } flt;                              \
        struct {                            \
            uint16_t size;                  \
            char value[_strSize + 1];       \
        } str;                              \
    };                                      \
}      

typedef struct {
    size_t cellsCount;
    IesCell(0, 0) **cells;
}   IesRow;

typedef struct {
    IesHeader *header;
    IesRow *rows;
    IesColumn *columns;
}   IesTable;

// Callback type
typedef bool (*IesCallback) (IesTable *table, void *userdata);

// Prototypes
bool ies_read (uint8_t *ies, size_t size, IesCallback callback, void *userdata);
