/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:45:22 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/30 13:48:30 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	count_occurences(t_list *headref, char ch)
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

static int	is_map_rectangular(t_list *headref)
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

static int	is_wall(char *line)
{
	int	i;

	i = 0;
	while (*(line + i))
	{
		if (*(line + i) != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	is_surrounded_by_wall(t_list *headref)
{
	t_list	*current;
	t_list	*last;

	last = ft_lstlast(headref);
	if (!is_wall(headref->content) || !is_wall(last->content))
		return (0);
	current = headref;
	while (current)
	{
		if (*(char *)(current->content) != '1' || *(char *) \
		(current->content + ft_strlen(current->content) - 1) != '1')
			return (0);
		current = current->next;
	}
	return (1);
}

void	is_map_valid(t_mlx *mlx_game, char exit)
{
	t_list	*headref;

	headref = mlx_game->headref;
	mlx_game->winsize->rows = ft_lstsize(headref);
	mlx_game->winsize->cols = ft_strlen((char *)headref->content);
	if (count_occurences(headref, exit) != 1)
		ft_error(mlx_game, "No Exit or Too many Exit!\n");
	if (count_occurences(headref, 'C') < 1)
		ft_error(mlx_game, "There are no collectibles\n");
	if (count_occurences(headref, 'P') != 1)
		ft_error(mlx_game, "No player starting position or too many!\n");
	if (!is_map_rectangular(headref))
		ft_error(mlx_game, "Map isn't rectangular!\n");
	if (!is_surrounded_by_wall(headref))
		ft_error(mlx_game, "Map is not surrounded by wall!\n");
	if (!has_valid_path(&headref, mlx_game->winsize, exit))
		ft_error(mlx_game, "Map doesn't have a valid path!\n");
}

