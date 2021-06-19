#include "nm.h"

int     main(int ac, char **av) {
    if (ac < 2) {
        if (!getFileContentAndSaveInStruct("a.out"))
            return 0;
    } else {
        for (int i = 1; i < ac; i++)
        if (!getFileContentAndSaveInStruct(av[i]))
            return 0;
    }
    checkAndDisplayFileContent();
    freeFileContent();
}