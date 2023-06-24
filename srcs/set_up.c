/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:16:32 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/23 20:50:04 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_player_img(t_mlx *mlx_game, char side, int x, int y)
{
	char	*path;
	
	if (side == 'f')
		path = "../resources/hero/4.png";
	else if (side == 'b')
		path = "../resources/hero/1.png";
	else if (side == 'u')
		path = "../resources/hero/5.png";
	else
		path = "../resources/hero/3.png";
	mlx_delete_image(mlx_game->mlx, mlx_game->player->player_img);
	mlx_game->player->player_texture = mlx_load_png(path);
	mlx_game->player->player_img = mlx_texture_to_image(mlx_game->mlx, mlx_game->player->player_texture);
	mlx_resize_image(mlx_game->player->player_img, mlx_game->img_size, mlx_game->img_size);
	mlx_image_to_window(mlx_game->mlx, mlx_game->player->player_img, x, y);
	mlx_delete_texture(mlx_game->player->player_texture);
}

void	set_up_images(t_mlx *mlx_game)
{
	
	mlx_game->background_texture = mlx_load_png("../resources/background2.png");
	mlx_game->background_img = mlx_texture_to_image(mlx_game->mlx, mlx_game->background_texture);
	mlx_delete_texture(mlx_game->background_texture);
	mlx_resize_image(mlx_game->background_img, mlx_game->img_size, mlx_game->img_size);
	// mlx_resize_image(mlx_game->background_img, mlx_game->winsize->width, mlx_game->winsize->height);
	mlx_game->wall_texture = mlx_load_png("../resources/wall.png");
	mlx_game->wall_img = mlx_texture_to_image(mlx_game->mlx, mlx_game->wall_texture);
	mlx_delete_texture(mlx_game->wall_texture);
	mlx_resize_image(mlx_game->wall_img, mlx_game->img_size, mlx_game->img_size);
	mlx_game->player->player_texture = mlx_load_png("../resources/hero/1.png");
	mlx_game->player->player_img = mlx_texture_to_image(mlx_game->mlx, mlx_game->player->player_texture);
	mlx_game->player->total_moves = 0;
	mlx_game->player->have_enemy = 0;
	mlx_game->player->move_size = mlx_game->img_size;
	mlx_game->player->player_can_exit = 0;
	mlx_resize_image(mlx_game->player->player_img, mlx_game->img_size, mlx_game->img_size);
	mlx_delete_texture(mlx_game->player->player_texture);
	mlx_game->enemy_texture = mlx_load_png("../resources/enemy/idle1.png");
	mlx_game->enemy_img = mlx_texture_to_image(mlx_game->mlx, mlx_game->enemy_texture);
	mlx_resize_image(mlx_game->enemy_img, mlx_game->img_size, mlx_game->img_size);
	mlx_delete_texture(mlx_game->enemy_texture);
	mlx_game->collectible_texture = mlx_load_png("../resources/coin1.png");
	mlx_game->collectible_img = mlx_texture_to_image(mlx_game->mlx, mlx_game->collectible_texture);
	mlx_resize_image(mlx_game->collectible_img, mlx_game->img_size - 40, mlx_game->img_size - 40);
	mlx_delete_texture(mlx_game->collectible_texture);
	mlx_game->exit_texture = mlx_load_png("../resources/exit.png");
	mlx_game->exit_img = mlx_texture_to_image(mlx_game->mlx, mlx_game->exit_texture);
	mlx_resize_image(mlx_game->exit_img, mlx_game->img_size, mlx_game->img_size);
	mlx_delete_texture(mlx_game->exit_texture);
	// mlx_image_to_window(mlx_game->mlx, mlx_game->background_img, 0, 0);
}

void	set_up_img_pos(t_mlx *mlx_game)
{
	t_list	*current;
	char	*hor_map;
	int		j;
	int		x;
	int		y;
	
	current = mlx_game->headref;
	y = 0;
	mlx_game->str_img = mlx_put_string(mlx_game->mlx, "Moves: 0", 100, 100);
	while (current)
	{
		hor_map = current->content;
		j = 0;
		x = 0;
		while (*(hor_map + j))
		{
			mlx_image_to_window(mlx_game->mlx, mlx_game->background_img, x, y);
			if (*(hor_map + j) == '1')
				mlx_image_to_window(mlx_game->mlx, mlx_game->wall_img, x, y);
			else if (*(hor_map + j) == 'P')
				mlx_image_to_window(mlx_game->mlx, mlx_game->player->player_img, x, y);
			else if (*(hor_map + j) == 'C')
				mlx_image_to_window(mlx_game->mlx, mlx_game->collectible_img, x, y);
			else if (*(hor_map + j) == 'E')
				mlx_image_to_window(mlx_game->mlx, mlx_game->exit_img, x, y);
			else if (*(hor_map + j) == 'X')
			{
				mlx_image_to_window(mlx_game->mlx, mlx_game->enemy_img, x, y);
				mlx_game->player->have_enemy = 1;
			}
			// else if (*(hor_map + j) == '0')
			// 	mlx_image_to_window(mlx_game->mlx, mlx_game->background_img, x, y);
			x += mlx_game->img_size;
			j++;
		}
		y += mlx_game->img_size;
		current = current->next;
	}
}


void	set_window_size(t_mlx *mlx_game)
{
	int	hor_wall;
	int	ver_wall;

	hor_wall = -1;
	ver_wall = 0;
	get_wall_size(&hor_wall, &ver_wall, mlx_game->headref);
	ft_printf("The hor wall: %d && the ver wall: %d\n", hor_wall, ver_wall);
	mlx_game->winsize->width = (hor_wall) * mlx_game->img_size;
	mlx_game->winsize->height = (ver_wall) * mlx_game->img_size;
}