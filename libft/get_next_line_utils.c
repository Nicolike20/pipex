/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:58:08 by nortolan          #+#    #+#             */
/*   Updated: 2021/09/25 17:55:46 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	if (dstsize == 0)
	{
		while (src[i] != '\0')
			i++;
		return (i);
	}
	while (src[l])
		++l;
	while (src[i] && i < dstsize - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (l);
}

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, ft_strlen(s1) + 1);
	ft_strlcat(res, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	if (c == '\0')
	{
		while (*s)
			s++;
		return ((char *) s);
	}
	while (*s)
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	if (start <= ft_strlen(s))
		ft_strlcpy(res, s + start, len + 1);
	return (res);
}
