/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 16:57:31 by nortolan          #+#    #+#             */
/*   Updated: 2021/09/18 00:52:59 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*cd;
	const char	*cs;

	if (dst == NULL && src == NULL)
		return (NULL);
	cd = dst;
	cs = src;
	while (n-- > 0)
	{
		*cd = *cs;
		cd++;
		cs++;
	}
	return (dst);
}
