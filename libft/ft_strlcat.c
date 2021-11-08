/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 11:53:05 by nortolan          #+#    #+#             */
/*   Updated: 2021/09/18 00:53:45 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	c;
	size_t	ld;
	size_t	ls;

	i = 0;
	ld = ft_strlen(dst);
	ls = ft_strlen(src);
	if (dstsize == 0)
		return (ls);
	if (dstsize < ld)
		return (ls + dstsize);
	c = ld;
	while (c + 1 < dstsize && src[i])
	{
		dst[c] = src[i];
		c++;
		i++;
	}
	dst[c] = '\0';
	return (ls + ld);
}
