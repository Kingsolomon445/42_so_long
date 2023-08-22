/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgs_and_sizes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:12:07 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/30 15:06:47 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	get_wall_size(int *hor_wall, int *ver_wall, t_list *headref)
{
	*hor_wall += ft_strlen(headref->content);
	*ver_wall += ft_lstsize(headref);
}

void	set_window_size(t_mlx *mlx_game)
{
	int	hor_wall;
	int	ver_wall;

	hor_wall = 0;
	ver_wall = 0;
	get_wall_size(&hor_wall, &ver_wall, mlx_game->headref);
	mlx_game->winsize->width = (hor_wall) * mlx_game->img_size;
	mlx_game->winsize->height = (ver_wall) * mlx_game->img_size;
}

/*
It is to be noted that 1400 and 2590 here represents \
the max of the screen where this program was coded
*/
int	get_img_size(t_mlx *mlx_game)
{
	int	img_size;
	int	img_size_by_col;

	img_size = 70;
	img_size_by_col = 0;
	if (mlx_game->winsize->rows > 20)
		img_size = 1400 / mlx_game->winsize->rows;
	if (mlx_game->winsize->cols > 37)
		img_size_by_col = 2590 / mlx_game->winsize->cols;
	if (img_size_by_col && img_size_by_col < img_size)
		return (img_size_by_col);
	return (img_size);
}
