/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:08:35 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/30 15:50:28 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_player_img(t_mlx *mlx_game, char side, int x, int y)
{
	char	*path;

	if (side == 'f')
		path = "resources/hero/4.png";
	else if (side == 'b')
		path = "resources/hero/1.png";
	else if (side == 'u')
		path = "resources/hero/5.png";
	else
		path = "resources/hero/3.png";
	mlx_delete_image(mlx_game->mlx, mlx_game->player->player_img);
	mlx_game->player->player_texture = mlx_load_png(path);
	mlx_game->player->player_img = mlx_texture_to_image(\
	mlx_game->mlx, mlx_game->player->player_texture);
	mlx_resize_image(\
	mlx_game->player->player_img, mlx_game->img_size, mlx_game->img_size);
	mlx_image_to_window(mlx_game->mlx, mlx_game->player->player_img, x, y);
	mlx_delete_texture(mlx_game->player->player_texture);
}

void	update_and_display_moves(t_mlx *mlx_game, \
mlx_instance_t *instances, int move_size, char axis)
{
	if (axis == 'x')
		instances[0].x += move_size;
	else
		instances[0].y += move_size;
	if (axis == 'x' && move_size > 0)
		update_player_img(mlx_game, 'f', instances[0].x, instances[0].y);
	else if (axis == 'x' && move_size < 0)
		update_player_img(mlx_game, 'b', instances[0].x, instances[0].y);
	else if (axis == 'y' && move_size > 0)
		update_player_img(mlx_game, 'd', instances[0].x, instances[0].y);
	else
		update_player_img(mlx_game, 'u', instances[0].x, instances[0].y);
	mlx_game->player->total_moves++;
	ft_printf("Current moves:  %d\n", mlx_game->player->total_moves);
}

void	player_moves(t_mlx *mlx_game, mlx_key_data_t keydata)
{
	mlx_instance_t	*instances;
	int				move_size;

	instances = mlx_game->player->player_img->instances;
	move_size = mlx_game->player->move_size;
	if (check_key(keydata) == 'w')
	{
		if (is_move_valid(mlx_game, instances[0].x, instances[0].y - move_size))
			update_and_display_moves(mlx_game, instances, -1 * move_size, 'y');
	}
	if (check_key(keydata) == 'a')
	{
		if (is_move_valid(mlx_game, instances[0].x, instances[0].y + move_size))
			update_and_display_moves(mlx_game, instances, move_size, 'y');
	}
	if (check_key(keydata) == 's')
	{
		if (is_move_valid(mlx_game, instances[0].x - move_size, instances[0].y))
			update_and_display_moves(mlx_game, instances, -1 * move_size, 'x');
	}
	if (check_key(keydata) == 'd')
	{
		if (is_move_valid(mlx_game, instances[0].x + move_size, instances[0].y))
			update_and_display_moves(mlx_game, instances, move_size, 'x');
	}
}
