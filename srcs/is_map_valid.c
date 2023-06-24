/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:45:22 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/23 16:49:55 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void ft_free_lst(t_list **headref)
{
	t_list	*current;

	if (!(*headref))
		return ;
	while ((*headref)->next)
	{
		current = *headref;
		*headref = (*headref)->next;
		ft_free(current->content);
		ft_free(current);
	}
	ft_free((*headref)->content);
	ft_free(*headref);
}

int count_occurences(t_list *headref, char ch)
{
	t_list	*current;
	char	*line;
	int		occ;
	int		i;

	occ = 0;
	current = headref;
	while (current)
	{
		i = 0;
		line = current->content;
		while (*(line + i))
		{
			if (*(line + i) == ch)
				occ++;
			i++;
		}
		current = current->next;
	}
	return (occ);
}

int is_map_rectangular(t_list *headref)
{
	t_list	*current;

	current = headref->next;
	while (current)
	{
		if (ft_strlen(current->content) != ft_strlen(headref->content))
			return (0);
		current = current->next;
	}
	return (1);
}

int is_wall(char *line)
{
	int i;

	i = 0;
	while (*(line + i))
	{
		if (*(line + i) != '1')
			return (0);
		i++;
	}
	return (1);
}

int	is_surrounded_by_wall(t_list *headref)
{
	t_list	*current;
	
	if (!is_wall(headref->content) || !is_wall(ft_lstlast(headref)->content))
		return (0);
	current = headref;
	while (current)
	{
		if (*(char *)(current->content) != '1' || *(char *)(current->content + ft_strlen(current->content - 1)) != '1')
			return (0);
		current = current->next;
	}
	return (1);
}

int	is_map_valid(t_list *headref)
{
	if (count_occurences(headref, 'E') != 1 || count_occurences(headref, 'C') < 1 || count_occurences(headref, 'P') != 1)
		return (0);
	if (!is_map_rectangular(headref) || !is_surrounded_by_wall(headref))
		return (0);
	return (1);
}