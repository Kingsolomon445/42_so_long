/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:18:36 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/28 19:19:11 by ofadahun         ###   ########.fr       */
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
}

void	my_closehook(void *param)
{
	end_game((t_mlx *)param, "You quit!");
}

void	my_loophook(void *param)
{
	mlx_image_t	*collectible;
	t_player	*player;
	mlx_image_t	*exit;
	t_mlx		*mlx_game;
	int			previous_score;

	mlx_game = (t_mlx *)param;
	collectible = ((t_mlx *)(param))->collectible_img;
	player = ((t_mlx *)(param))->player;
	previous_score = player->score;
	exit = ((t_mlx *)(param))->exit_img;
	if (mlx_is_key_down(mlx_game->mlx, MLX_KEY_SPACE))
		shoot_fire(mlx_game);
	if (mlx_game->fire_img)
		update_fire(mlx_game);
	if (mlx_game->fire_img)
		check_if_enemy_hit(mlx_game);
	if (collectible->count == 0 && player->player_img->instances[0].x == \
	exit->instances[0].x && player->player_img->instances[0].y == \
	exit->instances[0].y && player->player_can_exit)
		end_game(mlx_game, "You win!");
	check_if_collectible_taken(mlx_game);
	if (previous_score < player->score)
		update_str_img(mlx_game);
	if (player->have_enemy)
		check_if_collide_with_enemy(mlx_game);
	if (collectible->count <= 0)
		open_exit_door(mlx_game, mlx_game->exit_img->instances[0].x, \
		mlx_game->exit_img->instances[0].y);
}
