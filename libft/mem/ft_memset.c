/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:15:12 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/21 19:28:24 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	char	*tmp;

	tmp = (char *)s;
	while (len--)
	{
		*((char *)tmp) = c;
		tmp++;
	}
	return (s);
}
