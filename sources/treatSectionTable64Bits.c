/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatSectionTable64Bits.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <tcillard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:02:41 by tcillard          #+#    #+#             */
/*   Updated: 2021/06/23 20:08:30 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

Elf64_Shdr *getSectionByName(char *name) {
    t_elf *elfStruct;

    elfStruct = getFileStruct();
    Elf64_Shdr  *section = (Elf64_Shdr*) ((void*)elfStruct->elfHeader64 + elfStruct->elfHeader64->e_shoff);
    char *sectionName = (char*)((void*)elfStruct->elfHeader64 + section[elfStruct->elfHeader64->e_shstrndx].sh_offset);
    for (int i = 0; i < elfStruct->elfHeader64->e_shnum; i++) {
        if (ft_strcmp(sectionName + section[i].sh_name, name) == 0) {
            return section + i;
        }
    }
    return NULL;
}

char        *convertSymbolesValue(uint64_t value) {
    char    *valueConverted;
    size_t  bytesValue;

    bytesValue = 0;
    valueConverted = NULL;
    if (value == 0) {
        return NULL;
    }
    if (!(valueConverted = (char*)malloc(sizeof(char) * 16 + 1))) {
        return NULL;
    }
    for (int i = 15; i > -1 ; i--) {
        bytesValue = value & 15;
        valueConverted[i] = "0123456789abcdef"[bytesValue];
        value = value >> 4;
    }
    valueConverted[16] = '\0';
    return valueConverted;
}

t_symbolesList  *treatSymboles(Elf64_Shdr *symbolesSection, Elf64_Shdr *strTabSection) {
    char        *strTab;
    Elf64_Sym   *symTab;
    t_symbolesList  *firstLink;
    t_symbolesList  *actualLink;

    firstLink = NULL;
    actualLink = NULL;
    strTab = (char*) ((void*)getFileStruct()->elfHeader64 + strTabSection->sh_offset);
    symTab = (Elf64_Sym*) ((void*)getFileStruct()->elfHeader64 + symbolesSection->sh_offset);
    for (size_t i = 0; i < (symbolesSection->sh_size / symbolesSection->sh_entsize); i++) {
        if (symTab[i].st_name != 0) {
            if (!(actualLink = addAnElementToSymbolesList(strTab + symTab[i].st_name,
                    convertSymbolesValue(symTab[i].st_value), '?', actualLink))) {
                freeSymbolesList(firstLink);
                return NULL;
            }
            if (firstLink == NULL) {
                firstLink = actualLink;
            }
        }
    }
    t_symbolesList *tmp = firstLink;
    while (tmp) {
        printf("%16s %c %s\n", tmp->value, tmp->type, tmp->name);
        tmp = tmp->next;
    }
    return firstLink;
}    

void    treatAndDisplaySymboles64() {
    Elf64_Shdr  *symbolesSection;
    Elf64_Shdr  *strTabSection;
    t_symbolesList  *symbolesList;

    (void) symbolesList;
    symbolesList = NULL;
    symbolesSection = getSectionByName(".symtab");
    strTabSection = getSectionByName(".strtab");
    if (symbolesSection == NULL || strTabSection == NULL) {
        return ;
    }
    symbolesList = treatSymboles(symbolesSection, strTabSection);
}