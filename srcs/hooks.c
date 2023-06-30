/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:18:36 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/30 19:56:36 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_mlx		*mlx_game;

	mlx_game = (t_mlx *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		end_game(mlx_game, "You quit!");
	player_moves(mlx_game, keydata);
	check_if_collectible_taken(mlx_game);
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

	mlx_game = (t_mlx *)param;
	collectible = ((t_mlx *)(param))->collectible_img;
	player = ((t_mlx *)(param))->player;
	exit = ((t_mlx *)(param))->exit_img;
	if (collectible->count == 0 && player->player_img->instances[0].x \
	== exit->instances[0].x && player->player_img->instances[0].y == \
	exit->instances[0].y && player->player_can_exit)
		end_game(mlx_game, "You win!");
	check_if_collectible_taken(mlx_game);
	if (collectible->count <= 0)
		open_exit_door(mlx_game, mlx_game->exit_img->instances[0].x, \
		mlx_game->exit_img->instances[0].y);
}
