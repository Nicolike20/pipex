/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:22:22 by nortolan          #+#    #+#             */
/*   Updated: 2021/09/14 18:12:36 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	check;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		check = 0;
		while (haystack[i + check] && needle[check] == haystack[i + check]
			&& i + check < len)
		{
			if (needle[check + 1] == '\0')
				return ((char *)&haystack[i]);
			check++;
		}
		i++;
	}
	return (0);
}
