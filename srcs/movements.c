/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:08:35 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/23 20:40:14 by ofadahun         ###   ########.fr       */
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

void	update_and_display_moves(t_mlx *mlx_game, mlx_instance_t *instances, int move_size, char axis)
{
	char	*str;
	char	*player_moves_str;
	
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
	player_moves_str = ft_itoa(mlx_game->player->total_moves);
	str = ft_strjoin("Moves: ", player_moves_str);
	ft_free(player_moves_str);
	mlx_delete_image(mlx_game->mlx, mlx_game->str_img);
	mlx_game->str_img = mlx_put_string(mlx_game->mlx, (const char *)str, 100, 100);
	ft_free(str);
	// ft_printf("Moves: %d\n", mlx_game->player->total_moves);
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