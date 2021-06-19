/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <tcillard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:47:55 by tcillard          #+#    #+#             */
/*   Updated: 2021/06/19 17:18:05 by tcillard         ###   ########.fr       */
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


typedef enum
{
    B32,
    B64,
}       e_arch;

typedef struct  s_elf
{
    Elf32_Ehdr  *fileContent32;
    Elf64_Ehdr  *fileContent64;
    size_t      size;
    e_arch      arch;
}               t_elf;

void    checkAndDisplayFileContent();
t_elf   *getFileStruct();
t_elf   *initElfStruct();
int     getFileContentAndSaveInStruct(char *path);
void    freeFileContent();
void    displaySectionTable32B(Elf32_Ehdr *fileContent);
void    displaySectionTable64B(Elf64_Ehdr *fileContent);

#endif