/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatSectionTable64Bits.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <tcillard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:02:41 by tcillard          #+#    #+#             */
/*   Updated: 2021/06/21 18:29:25 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

Elf64_Shdr *getSectionByType(unsigned int type) {
    t_elf *elfStruct;

    elfStruct = getFileStruct();
    Elf64_Shdr  *section = (Elf64_Shdr*) ((void*)elfStruct->elfHeader64 + elfStruct->elfHeader64->e_shoff);
    for (int i = 0; i < elfStruct->elfHeader64->e_shnum; i++) {
        if (section[i].sh_type == type) {
            return section + i;
        }
    }
    return NULL;
}

void    displaySymboles64() {
    t_elf *elfStruct;
    Elf64_Shdr  *symbolesSection;
    Elf64_Sym   *symTab;
    char        *strTab;
    int numberOfSymboles;

    symbolesSection = getSectionByType(SHT_SYMTAB);
    numberOfSymboles = symbolesSection->sh_size / symbolesSection->sh_entsize;
    elfStruct = getFileStruct();
    strTab = (char*) ((void*)elfStruct->elfHeader64 + getSectionByType(SHT_STRTAB)->sh_offset);
    symTab = (Elf64_Sym*) ((void*)elfStruct->elfHeader64 + symbolesSection->sh_offset);
    printf("number of Symboles: %i\n", numberOfSymboles);
    for (int i = 0; i < numberOfSymboles; i++) {
        if (symTab[i].st_name != 0) {
            printf("%s\n", strTab + symTab[i].st_name);
        }
    }
}