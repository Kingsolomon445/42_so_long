/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:59:23 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/28 19:21:13 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"


void	check_if_collide_with_enemy(t_mlx *mlx_game)
{
	int	i;
	int	enemy_cnt;

	i = 0;
	enemy_cnt = mlx_game->enemy_img->count;
	while (i < enemy_cnt)
	{
		if (mlx_game->player->player_img->instances[0].x == \
		mlx_game->enemy_img->instances[i].x && \
		mlx_game->player->player_img->instances[0].y == \
		mlx_game->enemy_img->instances[i].y)
			end_game(mlx_game, "You lose!");
		i++;
	}
}

int	check_if_fire_hit_wall(t_mlx *mlx_game, int x, int y)
{
	int	i;
	int	wall_cnt;

	i = 0;
	wall_cnt = mlx_game->wall_img->count;
	while (i < wall_cnt)
	{
		if (mlx_game->wall_img->instances[i].x == x && \
		mlx_game->wall_img->instances[i].y == y)
		{
			mlx_delete_image(mlx_game->mlx, mlx_game->fire_img);
			mlx_game->fire_img = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

void	check_if_enemy_hit(t_mlx *mlx_game)
{
	int	i;
	int	enemy_cnt;

	i = 0;
	enemy_cnt = mlx_game->enemy_img->count;
	while (i < enemy_cnt)
	{
		if (mlx_game->enemy_img->instances[i].x == \
		mlx_game->fire_img->instances[0].x \
		&& mlx_game->enemy_img->instances[i].y == \
		mlx_game->fire_img->instances[0].y)
		{
			mlx_delete_image(mlx_game->mlx, mlx_game->fire_img);
			mlx_game->fire_img = NULL;
			mlx_game->enemy_img->instances[i].x += \
			mlx_game->winsize->width * 20;
			mlx_game->enemy_img->instances[i].y += \
			mlx_game->winsize->height * 20;
			break ;
		}
		i++;
	}
}
