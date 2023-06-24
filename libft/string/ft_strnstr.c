/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:08:32 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/21 19:28:24 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	check_all(const char *haystack, const char *needle, int len)
{
	while (*haystack && *haystack == *needle && len--)
	{
		if (!(*(needle + 1)))
			return (1);
		haystack++;
		needle++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char		*res;
	char		*needletmp;
	size_t		lentmp;

	if (!(*needle) || haystack == needle)
		return ((char *)haystack);
	needletmp = (char *)needle;
	while (len-- && *haystack && *needle)
	{
		if (*haystack == *needle)
		{
			res = (char *)haystack;
			lentmp = len + 1;
			if (check_all(haystack, needle, lentmp))
				return (res);
			haystack = (const char *)res;
			needle = (const char *)needletmp;
		}
		haystack++;
	}
	return (0);
}
