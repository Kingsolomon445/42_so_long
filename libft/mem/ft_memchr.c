/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:22:05 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/21 19:28:24 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char		*res;
	unsigned char	ch;

	res = NULL;
	ch = (unsigned char)c;
	while (n--)
	{
		if (*(unsigned char *)s == ch)
		{
			res = (char *)s;
			break ;
		}
		s++;
	}
	return ((void *)res);
}

// void    *ft_memchr(const void *s, int c, size_t n)
// {
//     unsigned char    a;
//     char    *ptr;
//     char    *str;
//     a = (unsigned char)c;
//     ptr = 0;
//     str = (char *)s;
//     // if (a == '\0')
//     //     return ((void *)s + ft_strlen(str));
//     while (n != 0)
//     {
//         if ((unsigned char)*str == a) hello
//         {
//             ptr = str;
//             break ;
//         }
//         n--;
//         str++;
//     }
//     return ((void *)ptr);
// }