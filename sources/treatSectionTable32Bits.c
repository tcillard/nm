/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatSectionTable32Bits.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <tcillard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:02:54 by tcillard          #+#    #+#             */
/*   Updated: 2021/07/02 20:24:08 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

Elf32_Shdr *getSectionByName32(char *name) {
    t_elf *elfStruct;

    elfStruct = getFileStruct();
    Elf32_Shdr  *section = (Elf32_Shdr*) ((void*)elfStruct->elfHeader32 + elfStruct->elfHeader32->e_shoff);
    char *sectionName = (char*)((void*)elfStruct->elfHeader32 + section[elfStruct->elfHeader32->e_shstrndx].sh_offset);
    for (int i = 0; i < elfStruct->elfHeader32->e_shnum; i++) {
        if (ft_strcmp(sectionName + section[i].sh_name, name) == 0) {
            return section + i;
        }
    }
    return NULL;
}

char        *convertSymbolesValue32(uint32_t value) {
    char    *valueConverted;
    size_t  bytesValue;

    bytesValue = 0;
    valueConverted = NULL;
    if (value == 0) {
        return NULL;
    }
    if (!(valueConverted = (char*)malloc(sizeof(char) * 8 + 1))) {
        return NULL;
    }
    for (int i = 7; i > -1 ; i--) {
        bytesValue = value & 15;
        valueConverted[i] = "0123456789abcdef"[bytesValue];
        value = value >> 4;
    }
    valueConverted[8] = '\0';
    return valueConverted;
}

char getSymboleType32(Elf32_Sym sym)
{
	boolean local = ELF32_ST_BIND(sym.st_info) == STB_LOCAL;
    // printf("%i - %i\n", STB_WEAK, ELF32_ST_BIND(sym.st_info));
    // printf("%i\n", STB_LOCAL);
    Elf32_Shdr  *sections = (Elf32_Shdr*) ((void*)getFileStruct()->elfHeader32 + getFileStruct()->elfHeader32->e_shoff);
    if (sym.st_shndx == SHN_ABS) {
        return local == TRUE ? 'a' : 'A';
    }
    else if (sections[sym.st_shndx].sh_type == SHT_NOBITS) {
        return local == TRUE ? 'b' : 'B';
    }
    else if (sym.st_shndx == SHN_COMMON) {
        return local == TRUE ? 'c' : 'C';
    }
    else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK && ELF32_ST_TYPE(sym.st_info) == STT_OBJECT)
    {
      if (sym.st_shndx == SHN_UNDEF) {
        return 'v';
      }
      return 'V';
    }
    else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK) {
        if (sections[sym.st_shndx].sh_type == SHN_UNDEF) {
            return 'w';
        }
        return 'W';
    }
    else if (sections[sym.st_shndx].sh_type == SHN_UNDEF) {
        return local == TRUE ? 'u' : 'U';
    }
    else if (sections[sym.st_shndx].sh_type == SHT_PROGBITS && ELF32_ST_TYPE(sym.st_info) == STT_OBJECT) {
        return local == TRUE ? 'g' : 'G';
    }
    else if (sections[sym.st_shndx].sh_type == SHT_PROGBITS) {
        return local == TRUE ? 'd' : 'D';
    }
    return '?';
}

t_symbolesList  *treatSymboles32(Elf32_Shdr *symbolesSection, Elf32_Shdr *strTabSection) {
    char        *strTab;
    Elf32_Sym   *symTab;
    t_symbolesList  *firstLink;
    t_symbolesList  *actualLink;

    firstLink = NULL;
    actualLink = NULL;
    strTab = (char*) ((void*)getFileStruct()->elfHeader32 + strTabSection->sh_offset);
    symTab = (Elf32_Sym*) ((void*)getFileStruct()->elfHeader32 + symbolesSection->sh_offset);
    for (size_t i = 0; i < (symbolesSection->sh_size / symbolesSection->sh_entsize); i++) {
        if (symTab[i].st_name != 0 && symTab[i].st_info != STT_FILE) {
            if (!(actualLink = addAnElementToSymbolesList(strTab + symTab[i].st_name,
                    convertSymbolesValue32(symTab[i].st_value), getSymboleType32(symTab[i]), actualLink))) {
                freeSymbolesList(firstLink);
                return NULL;
            }
            actualLink->valueDec = (uint32_t) symTab[i].st_value;
            if (firstLink == NULL) {
                firstLink = actualLink;
            }
        }
    }
    return firstLink;
}    

void    treatAndDisplaySymboles32() {
    Elf32_Shdr  *symbolesSection;
    Elf32_Shdr  *strTabSection;
    t_symbolesList  *symbolesList;

    (void) symbolesList;
    symbolesList = NULL;
    symbolesSection = getSectionByName32(".symtab");
    strTabSection = getSectionByName32(".strtab");
    if (symbolesSection == NULL || strTabSection == NULL) {
        return ;
    }
    symbolesList = treatSymboles32(symbolesSection, strTabSection);
    t_symbolesList *tmp = symbolesList;
    symbolesList = sortSymbolesList(symbolesList);
    tmp = symbolesList;
    while (tmp) {
        printf("%8s %c %s\n", tmp->valueHexa == NULL ? "" : tmp->valueHexa, tmp->type, tmp->name);
        tmp = tmp->next;
    }
}