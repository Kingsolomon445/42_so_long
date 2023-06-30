/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:18:36 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/30 19:57:23 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_mlx		*mlx_game;

	mlx_game = (t_mlx *)param;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || \
	keydata.action == MLX_REPEAT))
		end_game(mlx_game, "You quit!");
	else
		player_moves(mlx_game, keydata);
	check_if_collectible_taken(mlx_game);
}

void	my_closehook(void *param)
{
	end_game((t_mlx *)param, "You quit!");
}

void	my_loophook(void *param)
{
	t_mlx		*mlx_game;
	int			previous_score;

	mlx_game = (t_mlx *)param;
	previous_score = mlx_game->player->score;
	if (mlx_is_key_down(mlx_game->mlx, MLX_KEY_SPACE))
		shoot_fire(mlx_game);
	if (mlx_game->fire_img)
		update_fire(mlx_game);
	if (mlx_game->fire_img)
		check_if_enemy_hit(mlx_game);
	if (mlx_game->collectible_img->count == 0 && \
	mlx_game->player->player_img->instances[0].x == \
	mlx_game->exit_img->instances[0].x && \
	mlx_game->player->player_img->instances[0].y == \
	mlx_game->exit_img->instances[0].y && mlx_game->player->player_can_exit)
		end_game(mlx_game, "You win!");
	check_if_collectible_taken(mlx_game);
	if (previous_score < mlx_game->player->score)
		update_str_img(mlx_game);
	if (mlx_game->player->have_enemy)
		check_if_collide_with_enemy(mlx_game);
	if (mlx_game->collectible_img->count <= 0)
		open_exit_door(mlx_game, mlx_game->exit_img->instances[0].x, \
		mlx_game->exit_img->instances[0].y);
}
