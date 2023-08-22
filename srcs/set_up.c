/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:16:32 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/30 16:43:54 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	set_up_player_images(t_mlx *mlx_game)
{
	if (mlx_game->player->side_face_start == 'b')
		mlx_game->player->player_texture = mlx_load_png("resources/hero/1.png");
	else if (mlx_game->player->side_face_start == 'f')
		mlx_game->player->player_texture = mlx_load_png("resources/hero/4.png");
	else if (mlx_game->player->side_face_start == 'u')
		mlx_game->player->player_texture = mlx_load_png("resources/hero/5.png");
	else if (mlx_game->player->side_face_start == 'd')
		mlx_game->player->player_texture = mlx_load_png("resources/hero/3.png");
	mlx_game->player->player_img = mlx_texture_to_image(\
	mlx_game->mlx, mlx_game->player->player_texture);
	mlx_game->player->total_moves = 0;
	mlx_game->player->move_size = mlx_game->img_size;
	mlx_game->player->player_can_exit = 0;
	mlx_resize_image(mlx_game->player->player_img, mlx_game->img_size, \
	mlx_game->img_size);
	mlx_delete_texture(mlx_game->player->player_texture);
}

static void	set_up_images(t_mlx *mlx_game)
{
	mlx_game->background_texture = mlx_load_png("resources/background.png");
	mlx_game->background_img = mlx_texture_to_image(mlx_game->mlx, \
	mlx_game->background_texture);
	mlx_delete_texture(mlx_game->background_texture);
	mlx_resize_image(mlx_game->background_img, mlx_game->img_size, \
	mlx_game->img_size);
	mlx_game->wall_texture = mlx_load_png("resources/Grass.png");
	mlx_game->wall_img = mlx_texture_to_image(mlx_game->mlx, \
	mlx_game->wall_texture);
	mlx_delete_texture(mlx_game->wall_texture);
	mlx_resize_image(mlx_game->wall_img, mlx_game->img_size, \
	mlx_game->img_size);
	set_up_player_images(mlx_game);
	mlx_game->collectible_xpm = mlx_load_xpm42("resources/gem.xpm42");
	mlx_game->collectible_img = mlx_texture_to_image(mlx_game->mlx, \
	&(mlx_game->collectible_xpm->texture));
	mlx_resize_image(mlx_game->collectible_img, mlx_game->img_size, \
	mlx_game->img_size);
	mlx_delete_xpm42(mlx_game->collectible_xpm);
	mlx_game->exit_xpm = mlx_load_xpm42("resources/door.xpm42");
	mlx_game->exit_img = mlx_texture_to_image(mlx_game->mlx, \
	&(mlx_game->exit_xpm->texture));
	mlx_resize_image(mlx_game->exit_img, mlx_game->img_size, \
	mlx_game->img_size);
	mlx_delete_xpm42(mlx_game->exit_xpm);
}

static void	put_img_on_map(t_mlx *mlx_game, char *line, int y)
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
			mlx_image_to_window(mlx_game->mlx, \
			mlx_game->collectible_img, x, y);
		else if (*(line + j) == 'E')
			mlx_image_to_window(mlx_game->mlx, mlx_game->exit_img, x, y);
		x += mlx_game->img_size;
		j++;
	}
}

static void	set_up_img_pos(t_mlx *mlx_game)
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
}

void	set_ups(t_mlx *mlx_game)
{
	set_window_size(mlx_game);
	mlx_game->mlx = mlx_init(mlx_game->winsize->width, \
	mlx_game->winsize->height, "so long", 0);
	if (!mlx_game->mlx)
		ft_error(mlx_game, "mlx initialization failed!");
	set_up_images(mlx_game);
	set_up_img_pos(mlx_game);
}