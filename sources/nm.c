#include "nm.h"

int     main(int ac, char **av) {
    if (ac < 2) {
        if (!mapFileContentAndSaveInStruct("a.out"))
            return 0;
    } else {
        for (int i = 1; i < ac; i++)
        if (!mapFileContentAndSaveInStruct(av[i]))
            return 0;
    }
    checkAndDisplayFileContent();
    freeElfHeader();
}