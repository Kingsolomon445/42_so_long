/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:59:51 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/21 19:28:24 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	get_word_count(char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while ((*(++s) != c) && *s)
				;
		}
		else
		{
			s++;
		}
	}
	return (count);
}

static int	memory_allocation(char **res, char *start, \
int letter_count, int word_index)
{
	int	sucess;

	sucess = 0;
	*(res + word_index) = (char *)malloc((letter_count + 1) * sizeof(char));
	if (!(*(res + word_index)))
	{
		word_index--;
		while (word_index + 1)
		{
			free(*(res + word_index));
			*(res + word_index) = NULL;
			word_index--;
		}
		free(res);
		res = NULL;
		return (sucess);
	}
	ft_strlcpy(*(res + word_index), start, letter_count + 1);
	sucess++;
	return (sucess);
}

static char	**helper_func(char **res, char *str, \
char c, int word_index)
{
	int		letter_count;
	char	*start;
	

	while (*str)
	{
		letter_count = 0;
		start = str;
		while (*str != c && *str)
		{
			letter_count++;
			str++;
		}
		if (letter_count > 0)
		{
			if (!(memory_allocation(res, start, letter_count, word_index)))
				return (NULL);
			word_index++;
		}
		if (*str)
			str++;
	}
	*(res + word_index) = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**res;
	int		word_index;

	str = (char *)s;
	word_index = 0;
	res = (char **)malloc((get_word_count(str, c) + 1) * sizeof(char *));
	if (!res || !s)
		return (NULL);
	res = helper_func(res, str, c, word_index);
	return (res);
}
