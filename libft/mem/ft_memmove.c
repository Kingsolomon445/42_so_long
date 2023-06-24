/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:16:44 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/21 19:28:24 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dsttmp;
	char	*srctmp;

	if (dst == NULL && src == NULL)
		return (NULL);
	dsttmp = (char *)dst;
	srctmp = (char *)src;
	if (dsttmp < srctmp)
	{
		while (len--)
			*((char *)dst++) = *((char *)src++);
	}
	else
	{
		dst += len;
		src += len;
		while (len--)
		{
			--dst;
			--src;
			*((char *)dst) = *((char *)src);
		}
	}
	return (dsttmp);
}
