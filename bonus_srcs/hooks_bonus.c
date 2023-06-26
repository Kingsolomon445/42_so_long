/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:18:36 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/26 18:53:16 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

// void	check_collision_with_wall

void	update_fire_img(t_mlx *mlx_game, int x, int y)
{
	mlx_delete_image(mlx_game->mlx, mlx_game->fire_img);
	mlx_game->fire_xpm = mlx_load_xpm42("resources/fire.xpm42");
	mlx_game->fire_img = mlx_texture_to_image(mlx_game->mlx, \
	&(mlx_game->fire_xpm->texture));
	mlx_resize_image(mlx_game->fire_img, \
	mlx_game->img_size - 20, mlx_game->img_size - 20);
	mlx_image_to_window(mlx_game->mlx, mlx_game->fire_img, x, y);
	mlx_delete_xpm42(mlx_game->fire_xpm);
}

void	update_fire(t_mlx *mlx_game)
{
	int move_size;

	if (ft_strchr("fb", mlx_game->player->fire_side_facing))
	{
		if (mlx_game->player->fire_side_facing == 'f')
			move_size = mlx_game->player->move_size;
		else
			move_size = mlx_game->player->move_size * -1;
		update_fire_img(mlx_game, mlx_game->fire_img->instances[0].x + move_size, mlx_game->fire_img->instances[0].y);
	}
	else
	{
		if (mlx_game->player->fire_side_facing == 'u')
			move_size = mlx_game->player->move_size * -1;
		else
			move_size = mlx_game->player->move_size;
		update_fire_img(mlx_game, mlx_game->fire_img->instances[0].x, mlx_game->fire_img->instances[0].y + move_size);
	}
}

void	shoot_fire(t_mlx *mlx_game)
{
	mlx_image_t	*player_img;
	int	x;
	int	y;

	if (mlx_game->fire_img)
		mlx_delete_image(mlx_game->mlx, mlx_game->fire_img);
	player_img = mlx_game->player->player_img;
	mlx_game->fire_xpm = mlx_load_xpm42("resources/fire.xpm42");
	mlx_game->fire_img = mlx_texture_to_image(mlx_game->mlx, \
	&(mlx_game->fire_xpm->texture));
	mlx_resize_image(mlx_game->fire_img, \
	mlx_game->img_size, mlx_game->img_size);
	mlx_delete_xpm42(mlx_game->fire_xpm);
	x = player_img->instances[0].x;
	y = player_img->instances[0].y;
	mlx_image_to_window(mlx_game->mlx, mlx_game->fire_img, x, y);
	mlx_game->player->fire_stopped = 0;
	if (mlx_game->player->side_facing == 'f')
		mlx_game->player->fire_side_facing = 'f';
	else if (mlx_game->player->side_facing == 'b')
		mlx_game->player->fire_side_facing = 'b';
	else if (mlx_game->player->side_facing == 'u')
		mlx_game->player->fire_side_facing = 'u';
	else if (mlx_game->player->side_facing == 'd')
		mlx_game->player->fire_side_facing = 'd';
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_mlx		*mlx_game;

	mlx_game = (t_mlx *)param;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		end_game(mlx_game, "You quit!");
	else
		player_moves(mlx_game, keydata);
}

void	my_closehook(void *param)
{
	end_game((t_mlx *)param, "You quit!");
}

void	check_if_enemy_hit(t_mlx *mlx_game)
{
	int i;
	int	enemy_cnt;

	i = 0;
	enemy_cnt = mlx_game->enemy_img->count;
	while (i <= enemy_cnt)
	{
		if (mlx_game->enemy_img->instances[i].x == mlx_game->fire_img->instances[0].x && mlx_game->enemy_img->instances[i].y == mlx_game->fire_img->instances[0].y)
		{
			mlx_delete_image(mlx_game->mlx, mlx_game->fire_img);
			mlx_game->fire_img = NULL;
			mlx_game->enemy_img->instances[i].x += mlx_game->winsize->width * 20;
			mlx_game->enemy_img->instances[i].y += mlx_game->winsize->height * 20;
			break;
		}
		i++;
	}
	ft_printf("I hit my enemy\n");
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
