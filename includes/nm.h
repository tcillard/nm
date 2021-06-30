/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <tcillard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:47:55 by tcillard          #+#    #+#             */
/*   Updated: 2021/06/27 17:16:31 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# define B_32   1
# define B_64   2
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <elf.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_bool {FALSE, TRUE} boolean;

typedef enum
{
        B32,
        B64,
}       e_arch;

typedef struct  s_elf
{
    Elf32_Ehdr  *elfHeader32;
    Elf64_Ehdr  *elfHeader64;
    size_t      size;
    e_arch      arch;
    short       endian;
}               t_elf;

typedef struct          s_symbolesList
{
    char                    *name;
    char                    *valueHexa;
    char                    type;
    uint64_t            valueDec;
    struct s_symbolesList   *next;
    struct s_symbolesList   *prev;
}                       t_symbolesList;

void            checkAndDisplayFileContent();
t_elf           *getFileStruct();
t_elf           *initElfStruct();
boolean             mapFileContentAndSaveInStruct(char *path);
void            freeElfHeader();
void            treatAndDisplaySymboles64();
void            treatAndDisplaySymboles32();
int		        ft_strcmp(const char *s1, const char *s2);
t_symbolesList  *addAnElementToSymbolesList(char *name, char *value, char type, t_symbolesList *prev);
void            freeSymbolesList(t_symbolesList *symbolesList);
t_symbolesList  *sortSymbolesList(t_symbolesList *list);
char            charToLower(char c);
#endif