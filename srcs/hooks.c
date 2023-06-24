/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:18:36 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/24 17:06:51 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_if_collide_with_enemy(t_mlx *mlx_game)
{
	if (mlx_game->player->player_img->instances[0].x == mlx_game->enemy_img->instances[0].x && mlx_game->player->player_img->instances[0].y == mlx_game->enemy_img->instances[0].y)
		end_game(mlx_game, "You lose!");
}

void my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_mlx		*mlx_game;

	mlx_game = (t_mlx*)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		end_game(mlx_game, "You quit!");
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

	mlx_game = (t_mlx*)param;
	collectible = ((t_mlx*)(param))->collectible_img;
	player = ((t_mlx*)(param))->player;
	previous_score = player->score;
	exit = ((t_mlx*)(param))->exit_img;
	if (collectible->count == 0 && player->player_img->instances[0].x == exit->instances[0].x && player->player_img->instances[0].y == exit->instances[0].y && player->player_can_exit)
		end_game(mlx_game, "You win!");
	check_if_collectible_taken(mlx_game);
	if (previous_score < player->score)
		update_str_img(mlx_game);
	if (player->have_enemy)
		check_if_collide_with_enemy(mlx_game);
	if (collectible->count <= 0)
		open_exit_door(mlx_game, mlx_game->exit_img->instances[0].x, mlx_game->exit_img->instances[0].y);
}