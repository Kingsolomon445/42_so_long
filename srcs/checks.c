/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:37:03 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/23 20:06:19 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_if_collectible_taken(t_mlx *mlx_game)
{
	int			i;
	int			collectible_cnt;
	t_player	*player;
	mlx_image_t	*collectible;

	player = mlx_game->player;
	collectible = mlx_game->collectible_img;
	i = 0;
	collectible_cnt = collectible->count;
	while (i <= collectible_cnt + 1)
	{
		if (player->player_img->instances[0].x == collectible->instances[i].x && player->player_img->instances[0].y == collectible->instances[i].y)
		{
			collectible->instances[i].x += mlx_game->winsize->width * 20;
			collectible->instances[i].y += mlx_game->winsize->height * 20;
			collectible->count--;
			break;
		}
		i++;
	}
}