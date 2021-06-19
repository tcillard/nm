/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatSectionTable64Bits.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <tcillard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:02:41 by tcillard          #+#    #+#             */
/*   Updated: 2021/06/19 22:39:44 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void displaySectionTable64B(Elf64_Ehdr *fileContent) {
    printf("fileContent->e_shoff -> %li\n", fileContent->e_shoff);
    Elf64_Shdr *section = (Elf64_Shdr*) ((void*)fileContent + fileContent->e_shoff);
    char *sectionsNames = (char*) fileContent + section[fileContent->e_shstrndx].sh_offset;
    for (int i = 0; i++ < fileContent->e_shnum;) {
        printf("section.shName -> %i\n", section[i].sh_name);
        printf("name = %s\n", sectionsNames + section[i].sh_name + 1);
    }
}