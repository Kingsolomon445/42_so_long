/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:07:57 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/21 19:28:24 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		dstlen;
	size_t		res;

	dstlen = ft_strlen (dst);
	dst += dstlen;
	if (dstsize > dstlen)
		res = ft_strlen (src) + dstlen;
	else
		res = ft_strlen(src) + dstsize;
	if (dstsize != 0)
	{
		while (++dstlen < dstsize && *src)
		{
			*dst++ = *src++;
		}
		*dst = '\0';
	}
	return (res);
}
