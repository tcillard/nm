#include "nm.h"
void    printStruct(t_elf *elf) {
    printf("architectur -> %i\n", elf->arch);
    printf("size -> %li\n", elf->size);
    printf("e_machine -> %i\n", elf->fileContent32->e_machine);
    // printf("e_version -> %i\n", elf->pe_version);
    // printf("e_entry -> %i\n", elf->e_entry);
    // printf("p_paddr -> %i\n", elf->p_paddr);
    // printf("p_filesz -> %i\n", elf->filesz);
}
//  Elf32_Half	e_type;			/* Object file type */
//   Elf32_Half	e_machine;		/* Architecture */
//   Elf32_Word	e_version;		/* Object file version */
//   Elf32_Addr	e_entry;		/* Entry point virtual address */
//   Elf32_Off	e_phoff;		/* Program header table file offset */
//   Elf32_Off	e_shoff;		/* Section header table file offset */
//   Elf32_Word	e_flags;		/* Processor-specific flags */
//   Elf32_Half	e_ehsize;		/* ELF header size in bytes */
//   Elf32_Half	e_phentsize;		/* Program header table entry size */
//   Elf32_Half	e_phnum;		/* Program header table entry count */
//   Elf32_Half	e_shentsize;		/* Section header table entry size */
//   Elf32_Half	e_shnum;		/* Section header table entry count */
//   Elf32_Half	e_shstrndx;		/* Section header string table index */