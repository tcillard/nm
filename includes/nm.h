/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <tcillard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:47:55 by tcillard          #+#    #+#             */
/*   Updated: 2021/06/17 21:36:58 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <elf.h>
# include <stdio.h>

# define B32    1
# define B64    2

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

void    printStruct(t_elf *elf);
#endif