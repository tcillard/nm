#include "nm.h"

t_elf   *getFileStruct() {
    static t_elf elf;
 
    return &elf;
}

t_elf   *initElfStruct() {
    t_elf *elf;

    elf = getFileStruct();
    elf->arch = 0;
    elf->fileContent32 = NULL;
    elf->fileContent64 = NULL;
    elf->size = 0;
    return elf;
}

void    getFileContentAndInitElfStruct(char *path) {
    char        *file;
    struct stat stat;
    int         fd;

    t_elf       *elf;

    fd = 0;
    file = NULL;
    elf = initElfStruct();
    fd = open(path, O_RDONLY);
    fstat(fd, &stat);
    file = mmap(NULL, stat.st_size, PROT_READ, MA§1P_PRIVATE, fd, 0);
    close(fd);
    elf->size = stat.st_size;
    if (file[0] != 0x7f || file[1] != 'E' || file[2] != 'L' || file[3] != 'F') {
        return ;
    }
    if (file[4] == ELFCLASS32) {
        elf->fileContent32 = (Elf32_Ehdr*) file;
        elf->arch = B32;
    } else if (file[4] == ELFCLASS64) {
        elf->fileContent64 = (Elf64_Ehdr*) file;
        elf->arch = B64;
    }
}


int     main(int ac, char **av) {
    if (ac < 2) {
        getFileContentAndInitElfStruct("a.out");
    } else {
        for (int i = 1; i < ac; i++)
        getFileContentAndInitElfStruct(av[i]);
    }
    printf("%s\n", getFileStruct()->arch);
}