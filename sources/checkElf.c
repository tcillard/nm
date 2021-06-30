/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkElf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <tcillard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 15:29:45 by tcillard          #+#    #+#             */
/*   Updated: 2021/06/27 17:14:20 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

boolean     handleElfErrors() {
    return (TRUE);
}

void    checkAndDisplayFileContent() {
    t_elf *elf;

    elf = getFileStruct();
    if (!handleElfErrors())
        return ;
    if (elf->arch == B_64) {
        printf("64B\n");
        treatAndDisplaySymboles64();
    }
    else if (elf->arch == B_32) {
        printf("32B\n");
        treatAndDisplaySymboles32();
    }
}