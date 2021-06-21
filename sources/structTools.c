/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structTools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <tcillard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:08:40 by tcillard          #+#    #+#             */
/*   Updated: 2021/06/21 18:11:27 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_elf   *getFileStruct() {
    static t_elf elf;
 
    return &elf;
}

t_elf   *initElfStruct() {
    t_elf *elf;

    elf = getFileStruct();
    elf->arch = 0;
    elf->elfHeader32 = NULL;
    elf->elfHeader64 = NULL;
    elf->size = 0;
    return elf;
}

int    mapFileContentAndSaveInStruct(char *path) {
    char        *file;
    struct stat stat;
    int         fd;
    t_elf       *elf;

    fd = 0;
    file = NULL;
    elf = initElfStruct();
    fd = open(path, O_RDONLY);
    fstat(fd, &stat);
    file = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    elf->size = stat.st_size;
    if (file[0] != 0x7f || file[1] != 'E' || file[2] != 'L' || file[3] != 'F')
        return false;
    if (file[4] == ELFCLASS32) {
        elf->elfHeader32 = (Elf32_Ehdr*) file;
        elf->arch = B_32;
    } else if (file[4] == ELFCLASS64) {
        elf->elfHeader64 = (Elf64_Ehdr*) file;
        elf->arch = B_64;
    }
    return true;
}

void freeElfHeader() {
    t_elf *elf;

    elf = getFileStruct();
    if (elf->arch == B_32)
        munmap(elf->elfHeader32, elf->size);
    else if (elf->arch == B_64)
        munmap(elf->elfHeader64, elf->size);
}