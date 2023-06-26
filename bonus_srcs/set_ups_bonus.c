/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ups_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:16:32 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/26 18:42:30 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	set_up_player_and_enemy_images(t_mlx *mlx_game)
{
	mlx_game->player->player_texture = mlx_load_png("resources/hero/4.png");
	mlx_game->player->player_img = mlx_texture_to_image(mlx_game->mlx, \
	mlx_game->player->player_texture);
	mlx_game->player->total_moves = 0;
	mlx_game->player->score = 0;
	mlx_game->player->have_enemy = 0;
	mlx_game->player->move_size = mlx_game->img_size;
	mlx_game->player->player_can_exit = 0;
	mlx_game->player->side_facing = 'f';
	mlx_game->fire_img = NULL;
	mlx_resize_image(mlx_game->player->player_img, mlx_game->img_size, \
	mlx_game->img_size);
	mlx_delete_texture(mlx_game->player->player_texture);
	mlx_game->enemy_texture = mlx_load_png("resources/enemy/idle1.png");
	mlx_game->enemy_img = mlx_texture_to_image(mlx_game->mlx, \
	mlx_game->enemy_texture);
	mlx_resize_image(mlx_game->enemy_img, \
	mlx_game->img_size, mlx_game->img_size);
	mlx_delete_texture(mlx_game->enemy_texture);
}

void	set_up_images(t_mlx *mlx_game)
{
	mlx_game->background_texture = mlx_load_png("resources/background.png");
	mlx_game->background_img = mlx_texture_to_image(mlx_game->mlx, \
	mlx_game->background_texture);
	mlx_delete_texture(mlx_game->background_texture);
	mlx_resize_image(mlx_game->background_img, \
	mlx_game->img_size, mlx_game->img_size);
	mlx_game->wall_texture = mlx_load_png("resources/wall.png");
	mlx_game->wall_img = mlx_texture_to_image(\
	mlx_game->mlx, mlx_game->wall_texture);
	mlx_delete_texture(mlx_game->wall_texture);
	mlx_resize_image(mlx_game->wall_img, \
	mlx_game->img_size, mlx_game->img_size);
	set_up_player_and_enemy_images(mlx_game);
	mlx_game->collectible_xpm = mlx_load_xpm42("resources/gem.xpm42");
	mlx_game->collectible_img = mlx_texture_to_image(mlx_game->mlx, \
	&(mlx_game->collectible_xpm->texture));
	mlx_resize_image(mlx_game->collectible_img, \
	mlx_game->img_size, mlx_game->img_size);
	mlx_delete_xpm42(mlx_game->collectible_xpm);
	mlx_game->exit_texture = mlx_load_png("resources/exit.png");
	mlx_game->exit_img = mlx_texture_to_image(\
	mlx_game->mlx, mlx_game->exit_texture);
	mlx_resize_image(mlx_game->exit_img, \
	mlx_game->img_size, mlx_game->img_size);
	mlx_delete_texture(mlx_game->exit_texture);
}

void	put_img_on_map(t_mlx *mlx_game, char *line, int y)
{
	int	j;
	int	x;

	x = 0;
	j = 0;
	while (*(line + j))
	{
		mlx_image_to_window(mlx_game->mlx, mlx_game->background_img, x, y);
		if (*(line + j) == '1')
			mlx_image_to_window(mlx_game->mlx, mlx_game->wall_img, x, y);
		else if (*(line + j) == 'P')
			mlx_image_to_window(mlx_game->mlx, \
			mlx_game->player->player_img, x, y);
		else if (*(line + j) == 'C')
			mlx_image_to_window(mlx_game->mlx, mlx_game->collectible_img, x, y);
		else if (*(line + j) == 'X')
			mlx_image_to_window(mlx_game->mlx, mlx_game->exit_img, x, y);
		else if (*(line + j) == 'E')
		{
			mlx_image_to_window(mlx_game->mlx, mlx_game->enemy_img, x, y);
			mlx_game->player->have_enemy = 1;
		}
		x += mlx_game->img_size;
		j++;
	}
}

void	set_up_img_pos(t_mlx *mlx_game)
{
	t_list	*current;
	char	*line;
	int		y;

	current = mlx_game->headref;
	y = 0;
	while (current)
	{
		line = current->content;
		put_img_on_map(mlx_game, line, y);
		y += mlx_game->img_size;
		current = current->next;
	}
	mlx_game->collectible_cnt = mlx_game->collectible_img->count;
	mlx_game->str_img = mlx_put_string(mlx_game->mlx, \
	"Score: 0  Moves: 0", 0, 0);
}

void	set_window_size(t_mlx *mlx_game)
{
	int	hor_wall;
	int	ver_wall;

	hor_wall = 0;
	ver_wall = 0;
	get_wall_size(&hor_wall, &ver_wall, mlx_game->headref);
	mlx_game->winsize->width = (hor_wall) * mlx_game->img_size;
	mlx_game->winsize->height = (ver_wall) * mlx_game->img_size;
}
