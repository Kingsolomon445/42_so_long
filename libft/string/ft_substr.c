/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:37:02 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/21 19:28:24 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*res;
	char	*endptr;
	char	*tmp;

	if (!s)
		return (0);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	// if (len > (size_t)ft_strlen(s))
	// 	len = ft_strlen(s);
	endptr = (char *)s;
	while (*endptr)
		endptr++;
	tmp = (char *)s + start;
	if ((size_t)(endptr - tmp) < len)
		len = (endptr - tmp);
	str = (char *)malloc((len + 1) * sizeof(char));
	res = str;
	if (str != NULL)
	{
		while (len-- && *tmp)
			*str++ = *tmp++;
		*str = '\0';
	}
	return (res);
}

// char *ft_substr(char const *s, unsigned int start, size_t len)
// {
//     char *sbstr;
//     size_t i;
//     size_t j;
// 	if (!s)
// 		return (0);
// 	if (start > (size_t)ft_strlen((char *)s))
// 		return ft_strdup("");
// 	if ((size_t)ft_strlen((char *)s) - start < len)
// 		len = ft_strlen((char *)s) - start;
// 	sbstr = malloc(sizeof(char) * (len + 1));
// 	if (!sbstr)
// 		return (NULL);
//     i = start;
//     j = 0;
//     while (s[i] != '\0' && len--)
//     {
//         sbstr[j] = s[i];
//         i++;
//         j++;
//     }
//     sbstr[j] = '\0';
//     return(sbstr);
// }
