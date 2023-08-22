/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:08:35 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/30 13:59:55 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	update_player_img(t_mlx *mlx_game, int x, int y)
{
	char	*path;

	if (mlx_game->player->side_facing == 'f')
		path = "resources/hero/4.png";
	else if (mlx_game->player->side_facing == 'b')
		path = "resources/hero/1.png";
	else if (mlx_game->player->side_facing == 'u')
		path = "resources/hero/5.png";
	else
		path = "resources/hero/3.png";
	mlx_delete_image(mlx_game->mlx, mlx_game->player->player_img);
	mlx_game->player->player_texture = mlx_load_png(path);
	mlx_game->player->player_img = mlx_texture_to_image(\
	mlx_game->mlx, mlx_game->player->player_texture);
	mlx_resize_image(mlx_game->player->player_img, \
	mlx_game->img_size, mlx_game->img_size);
	mlx_image_to_window(mlx_game->mlx, mlx_game->player->player_img, x, y);
	mlx_delete_texture(mlx_game->player->player_texture);
}

void	update_str_img(t_mlx *mlx_game)
{
	char	*str;
	char	*score_str;
	char	*player_moves_str;
	char	*score;
	char	*str_to_put;

	player_moves_str = ft_itoa(mlx_game->player->total_moves);
	str = ft_strjoin("  Moves: ", player_moves_str);
	score_str = ft_itoa(mlx_game->player->score);
	score = ft_strjoin("Score: ", score_str);
	ft_free(score_str);
	ft_free(player_moves_str);
	mlx_delete_image(mlx_game->mlx, mlx_game->str_img);
	str_to_put = ft_strjoin(score, str);
	mlx_game->str_img = mlx_put_string(mlx_game->mlx, \
	(const char *)str_to_put, 0, 0);
	ft_free(str);
	ft_free(score);
	ft_free(str_to_put);
}

static void	update_and_display_moves(t_mlx *mlx_game, \
mlx_instance_t *instances, int move_size, char axis)
{
	mlx_delete_image(mlx_game->mlx, mlx_game->fire_img);
	mlx_game->fire_img = NULL;
	if (axis == 'x')
		instances[0].x += move_size;
	else
		instances[0].y += move_size;
	if (axis == 'x' && move_size > 0)
		mlx_game->player->side_facing = 'f';
	else if (axis == 'x' && move_size < 0)
		mlx_game->player->side_facing = 'b';
	else if (axis == 'y' && move_size > 0)
		mlx_game->player->side_facing = 'd';
	else
		mlx_game->player->side_facing = 'u';
	update_player_img(mlx_game, instances[0].x, instances[0].y);
	mlx_game->player->total_moves++;
	update_str_img(mlx_game);
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
