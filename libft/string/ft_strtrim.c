/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:50:51 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/21 19:28:24 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	int	is_present(char c, char const *set)
{
	char	*ptr;

	ptr = (char *)set;
	while (*ptr)
	{
		if (*ptr == c)
			return (1);
		ptr++;
	}
	return (0);
}

static char	*get_first_position(char const *str, char const *set)
{
	char	*startptr;

	startptr = (char *)str;
	while (is_present(*startptr, set))
	{
		startptr++;
		if (*startptr == '\0')
			return (0);
	}
	return (startptr);
}

static char	*get_last_position(char const *str, char const *set)
{
	char	*endptr;

	endptr = (char *)str + (ft_strlen((char *)str) - 1);
	while (is_present(*endptr, set))
	{
		endptr--;
		if (*endptr == '\0')
			return (0);
	}
	return (endptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*startptr;
	char	*endptr;
	char	*res;
	char	*resstart;

	if (!(*s1) || !s1 || !set)
		return (ft_strdup((char *)s1));
	startptr = get_first_position(s1, set);
	endptr = get_last_position(s1, set);
	if (!startptr || !endptr)
		return (ft_strdup(""));
	res = (char *)malloc((((endptr - startptr) + 1) + 1) * sizeof(char));
	if (!res)
		return (0);
	resstart = res;
	while (*startptr)
	{
		*res++ = *startptr;
		if (startptr == endptr)
			break ;
		startptr++;
	}
	*res = '\0';
	return (resstart);
}
