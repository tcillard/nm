/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <tcillard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:08:55 by tcillard          #+#    #+#             */
/*   Updated: 2021/06/23 18:25:02 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int     ft_strlen(const char *s) {
    int i;

    i = 0;
    while (s[i]) {
        i++;
    }
    return i;
}

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*cpy;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (!(cpy = (char*)malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (0);
	while (s[i])
	{
		cpy[i] = (*f)(s[i]);
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
