/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:08:35 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/24 20:36:31 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_move_valid(mlx_image_t *wall, mlx_image_t *exit, int x, int y, int player_can_exit)
{
	int 		wall_count;
	int			i;

	i = 0;
	wall_count = wall->count;
	while (i < wall_count)
	{
		if (x == wall->instances[i].x && y == wall->instances[i].y)
			return (0);
		i++;
	}
	if (x == exit->instances[0].x && y == exit->instances[0].y && !player_can_exit)
		return (0);
	return (1);
}

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
	mlx_game->player->player_img = mlx_texture_to_image(mlx_game->mlx, mlx_game->player->player_texture);
	mlx_resize_image(mlx_game->player->player_img, mlx_game->img_size, mlx_game->img_size);
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
	mlx_game->str_img = mlx_put_string(mlx_game->mlx, (const char *)str_to_put, 0, 0);
	ft_free(str);
	ft_free(score);
	ft_free(str_to_put);
}

void	update_and_display_moves(t_mlx *mlx_game, mlx_instance_t *instances, int move_size, char axis)
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
	update_str_img(mlx_game);
}
void	player_moves(t_mlx *mlx_game, mlx_key_data_t keydata)
{
	mlx_instance_t	*instances;
	int				move_size;

	instances = mlx_game->player->player_img->instances;
	move_size = mlx_game->player->move_size;
	
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (is_move_valid(mlx_game->wall_img, mlx_game->exit_img, instances[0].x, instances[0].y - move_size, mlx_game->player->player_can_exit))
			update_and_display_moves(mlx_game, instances, -1 * move_size, 'y');
	}
	if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_DOWN) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (is_move_valid(mlx_game->wall_img, mlx_game->exit_img, instances[0].x, instances[0].y + move_size, mlx_game->player->player_can_exit))
			update_and_display_moves(mlx_game, instances, move_size, 'y');
	}
	if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_LEFT) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (is_move_valid(mlx_game->wall_img, mlx_game->exit_img, instances[0].x - move_size, instances[0].y, mlx_game->player->player_can_exit))
			update_and_display_moves(mlx_game, instances, -1 * move_size, 'x');
	}
	if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (is_move_valid(mlx_game->wall_img, mlx_game->exit_img, instances[0].x + move_size, instances[0].y, mlx_game->player->player_can_exit))
			update_and_display_moves(mlx_game, instances, move_size, 'x');
	}
}