/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbolesListTools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <tcillard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 18:39:48 by tcillard          #+#    #+#             */
/*   Updated: 2021/06/27 17:29:30 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_symbolesList  *createASymbolesListElement() {
    t_symbolesList  *symbolesList;

    if (!(symbolesList = (t_symbolesList*)malloc(sizeof(t_symbolesList)))) {
        return NULL;
    }
    symbolesList->valueHexa = NULL;
    symbolesList->name = NULL;
    symbolesList->type = 0;
    symbolesList->next = NULL;
    symbolesList->prev =  NULL;
    symbolesList->valueDec = 0;
    return (symbolesList);
}

t_symbolesList  *addAnElementToSymbolesList(char *name, char *value, char type, t_symbolesList *prev) {
    t_symbolesList  *newElement;

    if (!(newElement = createASymbolesListElement())) {
        return NULL;
    }
    newElement->valueHexa = value;
    newElement->name = name;
    newElement->type = type;
    newElement->prev = prev;
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
        free(symbolesList->valueHexa);
        tmp = symbolesList;
        symbolesList = symbolesList->next;
        free(tmp);
    }
}

int             symbolesNameCmp(char *s1, char *s2) {
    int		i;

	i = 0;
    while (*s1 == '_') {
        s1++;
    }
    while (*s2 == '_') {
        s2++;
    }
	while (charToLower(s1[i]) == charToLower(s2[i]) && s1[i] && s2[i]) {
		i++;
    }
	return (charToLower((unsigned char)s1[i]) - charToLower((unsigned char)s2[i]));
}

boolean             symbolesListIsSorted(t_symbolesList *list) {
    int     ret;

    ret = 0;
    while (list->next != NULL) {
        ret = symbolesNameCmp(list->name, list->next->name);
        if (ret > 0 || (ret == 0 && list->valueDec > list->next->valueDec)) {
            return FALSE;
        }
        list = list->next;
    }
    return TRUE;
}

void                    switchSymboleElements(t_symbolesList *list) {
    t_symbolesList  *tmp;

    tmp = list->next;
    if (list->prev != NULL) {
        list->prev->next = tmp; 
    }
    list->next = tmp->next;
    tmp->prev = list->prev;
    list->prev = tmp;
    tmp->next = list;
    if (list->next) {
        list->next->prev = list;
    }
}

t_symbolesList           *sortSymbolesList(t_symbolesList *list) {
    int             ret;

    ret = 0;
    if (list == NULL) {
        return NULL;
    }
    list = list;
    while (!symbolesListIsSorted(list)) {
        while (list->next != NULL) {
            ret = symbolesNameCmp(list->name, list->next->name);
            if (ret > 0 || (ret == 0 && list->valueDec > list->next->valueDec)){
                switchSymboleElements(list);
            }
            if (list->next != NULL) {
                list = list->next;
            }
        }
        while (list->prev != NULL) {
            list = list->prev;
        }
    }
    return list;
}