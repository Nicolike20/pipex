/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:12:09 by nortolan          #+#    #+#             */
/*   Updated: 2021/09/17 19:40:02 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		l;

	if (c == '\0')
	{
		while (*s)
			s++;
		return ((char *) s);
	}
	l = 0;
	while (*s)
	{
		l++;
		s++;
	}
	while (l-- >= 0)
	{
		if (*s == (char) c)
		{
			return ((char *) s);
		}
		s--;
	}
	return (0);
}
