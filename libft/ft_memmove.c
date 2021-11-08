/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 17:34:35 by nortolan          #+#    #+#             */
/*   Updated: 2021/09/15 13:45:42 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*cd;
	const char	*cs;

	if (dst == NULL && src == NULL)
		return (NULL);
	cd = dst;
	cs = src;
	if (cs < cd)
	{
		cd += len;
		cs += len;
		while (len-- > 0)
			*--cd = *--cs;
	}
	else
	{
		while (len-- > 0)
			*cd++ = *cs++;
	}
	return (dst);
}
