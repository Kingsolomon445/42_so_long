/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus_utils_two.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:48:06 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/28 19:16:30 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	update_fire_img(t_mlx *mlx_game, int x, int y)
{
	mlx_delete_image(mlx_game->mlx, mlx_game->fire_img);
	mlx_game->fire_xpm = mlx_load_xpm42("resources/fire.xpm42");
	mlx_game->fire_img = mlx_texture_to_image(mlx_game->mlx, \
	&(mlx_game->fire_xpm->texture));
	mlx_resize_image(mlx_game->fire_img, \
	mlx_game->img_size - 20, mlx_game->img_size - 20);
	mlx_delete_xpm42(mlx_game->fire_xpm);
	if (check_if_fire_hit_wall(mlx_game, x, y))
		return ;
	mlx_image_to_window(mlx_game->mlx, mlx_game->fire_img, x, y);
}

void	update_fire(t_mlx *mlx_game)
{
	int	move_size;

	if (ft_strchr("fb", mlx_game->player->fire_side_facing))
	{
		if (mlx_game->player->fire_side_facing == 'f')
			move_size = mlx_game->player->move_size;
		else
			move_size = mlx_game->player->move_size * -1;
		update_fire_img(mlx_game, mlx_game->fire_img->instances[0].x + \
		move_size, mlx_game->fire_img->instances[0].y);
	}
	else
	{
		if (mlx_game->player->fire_side_facing == 'u')
			move_size = mlx_game->player->move_size * -1;
		else
			move_size = mlx_game->player->move_size;
		update_fire_img(mlx_game, mlx_game->fire_img->instances[0].x, \
		mlx_game->fire_img->instances[0].y + move_size);
	}
}

void	shoot_fire(t_mlx *mlx_game)
{
	mlx_image_t	*player_img;
	int			x;
	int			y;

	if (mlx_game->fire_img)
		mlx_delete_image(mlx_game->mlx, mlx_game->fire_img);
	player_img = mlx_game->player->player_img;
	mlx_game->fire_xpm = mlx_load_xpm42("resources/fire.xpm42");
	mlx_game->fire_img = mlx_texture_to_image(mlx_game->mlx, \
	&(mlx_game->fire_xpm->texture));
	mlx_resize_image(mlx_game->fire_img, \
	mlx_game->img_size, mlx_game->img_size);
	mlx_delete_xpm42(mlx_game->fire_xpm);
	x = player_img->instances[0].x;
	y = player_img->instances[0].y;
	mlx_image_to_window(mlx_game->mlx, mlx_game->fire_img, x, y);
	mlx_game->player->fire_stopped = 0;
	if (mlx_game->player->side_facing == 'f')
		mlx_game->player->fire_side_facing = 'f';
	else if (mlx_game->player->side_facing == 'b')
		mlx_game->player->fire_side_facing = 'b';
	else if (mlx_game->player->side_facing == 'u')
		mlx_game->player->fire_side_facing = 'u';
	else if (mlx_game->player->side_facing == 'd')
		mlx_game->player->fire_side_facing = 'd';
}

int	is_move_valid(t_mlx *mlx_game, int x, int y)
{
	int	wall_count;
	int	i;

	i = 0;
	wall_count = mlx_game->wall_img->count;
	while (i < wall_count)
	{
		if (x == mlx_game->wall_img->instances[i].x && \
		y == mlx_game->wall_img->instances[i].y)
			return (0);
		i++;
	}
	if (x == mlx_game->exit_img->instances[0].x && y == \
	mlx_game->exit_img->instances[0].y && !mlx_game->player->player_can_exit)
		return (0);
	return (1);
}
