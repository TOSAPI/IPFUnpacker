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

#include "ipf.h"
#include "dbg/dbg.h"

#pragma pack (push, 1)
typedef struct {
    uint16_t fileCount;
    uint32_t filetableOffset;
    uint16_t unk;
    uint32_t filefooterOffset;
    uint32_t magic;
    uint32_t baseRevision;
    uint32_t revision;
} ArchiveHeader;
#pragma pack (pop)

#pragma pack (push, 1)
typedef struct {
    uint16_t filenameLength;
    uint32_t crc;
    uint32_t compressedLength;
    uint32_t uncompressedLength;
    uint32_t dataOffset;
    uint16_t archivenameLength;
} IpfInfo;
#pragma pack (pop)

char *remove_ext(char* filename) {
    char *retstr;
    char *lastdot;

    retstr = malloc(strlen(filename)+1);
    strcpy(retstr, filename);

    lastdot = strrchr(retstr, '.');

    if(lastdot != NULL)
    {
        *lastdot = '\0';
    }

    return retstr;
}

bool ipf_read (uint8_t *ipf, size_t size, IpfCallback callback, void *userdata)
{
    uint8_t *header = &ipf[size-24];
    bool status = false;

    ArchiveHeader *archiveHeader = (void *) header;
    char magic[] = {0x50, 0x4b, 0x05, 0x06};

    if (memcmp (&archiveHeader->magic, magic, sizeof(magic)) != 0) {
        error ("Wrong magic word : %#x", archiveHeader->magic);
        goto cleanup;
    }

    IpfInfo *ipfInfo = (void *) &ipf[archiveHeader->filetableOffset];
    char *cursor = (void *) ipfInfo;

    // Iterate through all the files
    for (int i = 0; i < archiveHeader->fileCount; i++, ipfInfo = (void *) cursor)
    {
        // Get the current file data
        uint8_t *data = &ipf[ipfInfo->dataOffset];
        size_t dataSize = ipfInfo->compressedLength;

        char *archive_ptr = cursor + sizeof(*ipfInfo);
        char archive[ipfInfo->archivenameLength + 1];
        memset (archive, 0, sizeof(archive));
        strncpy (archive, archive_ptr, ipfInfo->archivenameLength);

        char *filename_ptr = archive_ptr + ipfInfo->archivenameLength;
        char filename[ipfInfo->filenameLength + 1];
        memset (filename, 0, sizeof(filename));
        strncpy (filename, filename_ptr, ipfInfo->filenameLength);

        if (!(callback (data, dataSize, remove_ext(archive), filename, userdata))) {
            error ("callback failed for '%s:%s'", remove_ext(archive), filename);
        }

        cursor += sizeof(*ipfInfo);
        cursor += ipfInfo->archivenameLength;
        cursor += ipfInfo->filenameLength;
    }

    status = true;
cleanup:
    return status;
}
