/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:37:03 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/24 19:36:54 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		if (player->player_img->instances[0].x == collectible->instances[i].x && player->player_img->instances[0].y == collectible->instances[i].y)
		{
			ft_printf("Player x: %d Player y: %d Collectible x: %d Collectible y: %d\n", player->player_img->instances[0].x, player->player_img->instances[0].y, collectible->instances[i].x, collectible->instances[i].y);
			collectible->instances[i].x += mlx_game->winsize->width * 20;
			collectible->instances[i].y += mlx_game->winsize->height * 20;
			collectible->count--;
			mlx_game->player->score++;
			break;
		}
		i++;
	}
}