/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkElf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <tcillard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 15:29:45 by tcillard          #+#    #+#             */
/*   Updated: 2021/06/23 16:53:22 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int     handleElfErrors() {
    return (true);
}

void    checkAndDisplayFileContent() {
    t_elf *elf;

    elf = getFileStruct();
    if (!handleElfErrors())
        return ;
    if (elf->arch == B_64)
        treatAndDisplaySymboles64(elf->elfHeader64);
    else if (elf->arch == B_32)
        displaySectionTable32B(elf->elfHeader32);
}