/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbolesListTools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <tcillard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 18:39:48 by tcillard          #+#    #+#             */
/*   Updated: 2021/06/23 20:06:40 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_symbolesList  *createASymbolesListElement() {
    t_symbolesList  *symbolesList;

    if (!(symbolesList = (t_symbolesList*)malloc(sizeof(t_symbolesList)))) {
        return NULL;
    }
    symbolesList->value = NULL;
    symbolesList->name = NULL;
    symbolesList->type = 0;
    symbolesList->next = NULL;
    return (symbolesList);
}

t_symbolesList  *addAnElementToSymbolesList(char *name, char *value, char type, t_symbolesList *prev) {
    t_symbolesList  *newElement;

    if (!(newElement = createASymbolesListElement())) {
        return NULL;
    }
    newElement->value = value;
    newElement->name = name;
    newElement->type = type;
    if (prev == NULL) {
        return newElement;
    }
    prev->next = newElement;
    return newElement;
}

void            freeSymbolesList(t_symbolesList *symbolesList) {
    t_symbolesList  *tmp;

    tmp = NULL;
    while (symbolesList) {
        free(symbolesList->name);
        free(symbolesList->value);
        tmp = symbolesList;
        symbolesList = symbolesList->next;
        free(tmp);
    }
}

// void            sortSymboleList(const t_symbolesList *symbolesList) {
//     t_symbolesList  *listSorter;

//     listSorter = symbolesList
//     if (symbolesList == NULL) {
//         return ;
//     }
//     firstLink = symbolesList;
// }