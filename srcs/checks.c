/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:37:03 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/26 16:06:11 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	check_if_collectible_taken(t_mlx *mlx_game)
{
	int			i;
	t_player	*player;
	mlx_image_t	*collectible;

	player = mlx_game->player;
	collectible = mlx_game->collectible_img;
	i = 0;
	while (i <= mlx_game->collectible_cnt)
	{
		if (player->player_img->instances[0].x == \
		collectible->instances[i].x && player->player_img->instances[0].y \
		== collectible->instances[i].y)
		{
			collectible->instances[i].y += mlx_game->winsize->height * 20;
			collectible->count--;
			break ;
		}
		i++;
	}
}

int	check_key(mlx_key_data_t keydata)
{
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) && \
	(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		return ('w');
	if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_DOWN) && \
	(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		return ('a');
	if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_LEFT) && \
	(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		return ('s');
	if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT) && \
	(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		return ('d');
	else
		return ('\0');
}
