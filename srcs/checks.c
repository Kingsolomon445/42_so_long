/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:37:03 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/30 17:06:12 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_for_side_to_face(t_mlx *mlx_game, char *line, char *prev_line)
{
	int	j;

	j = 0;
	while (*(line + j))
	{
		if (*(line + j) == 'P')
		{
			if (*(line + j + 1) == '1')
				mlx_game->player->side_face_start = 'b';
			if (*(line + j - 1) == '1' && \
			mlx_game->player->side_face_start == 'b')
				mlx_game->player->side_face_start = 'u';
			if (prev_line && *(prev_line + j) == '1' && \
			mlx_game->player->side_face_start == 'u')
				mlx_game->player->side_face_start = 'd';
			return (1);
		}
		j++;
	}
	return (0);
}

void	get_side_face_start(t_mlx *mlx_game)
{
	t_list	*current;
	char	*line;
	char	*prev_line;

	current = mlx_game->headref;
	mlx_game->player->side_face_start = 'f';
	prev_line = NULL;
	while (current)
	{
		line = current->content;
		if (check_for_side_to_face(mlx_game, line, prev_line))
			break ;
		prev_line = line;
		current = current->next;
	}
}
