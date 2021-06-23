/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <tcillard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:47:55 by tcillard          #+#    #+#             */
/*   Updated: 2021/06/23 20:06:16 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# define B_32   1
# define B_64   2
# define false  0
# define true   1
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <elf.h>
# include <stdio.h>
# include <stdlib.h>


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
}               t_elf;

typedef struct          s_symbolesList
{
    char                *name;
    char                *value;
    char                type;
    struct s_symbolesList   *next;
}                       t_symbolesList;

void            checkAndDisplayFileContent();
t_elf           *getFileStruct();
t_elf           *initElfStruct();
int             mapFileContentAndSaveInStruct(char *path);
void            freeElfHeader();
void            displaySectionTable32B(Elf32_Ehdr *elfHeader);
void            treatAndDisplaySymboles64();
int		        ft_strcmp(const char *s1, const char *s2);
t_symbolesList  *addAnElementToSymbolesList(char *name, char *value, char type, t_symbolesList *prev);
void            freeSymbolesList(t_symbolesList *symbolesList);

#endif