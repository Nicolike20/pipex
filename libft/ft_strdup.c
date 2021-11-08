/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:58:20 by nortolan          #+#    #+#             */
/*   Updated: 2021/09/14 17:45:22 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (s1[i] != '\0')
	{
		i++;
	}
	res = (char *) malloc(sizeof(char) * (i + 1));
	if (!(res))
		return (NULL);
	j = 0;
	while (s1[j] != '\0')
	{
		res[j] = s1[j];
		j++;
	}
	res[j] = s1[j];
	return (res);
}
