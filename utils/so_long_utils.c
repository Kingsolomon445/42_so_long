/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:12:07 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/30 15:06:47 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	open_exit_door(t_mlx *mlx_game, int x, int y)
{
	mlx_delete_image(mlx_game->mlx, mlx_game->exit_img);
	mlx_game->exit_xpm = mlx_load_xpm42("resources/door_open.xpm42");
	mlx_game->exit_img = mlx_texture_to_image(\
	mlx_game->mlx, &(mlx_game->exit_xpm->texture));
	mlx_resize_image(\
	mlx_game->exit_img, mlx_game->img_size, mlx_game->img_size);
	mlx_image_to_window(mlx_game->mlx, mlx_game->exit_img, x, y);
	mlx_delete_xpm42(mlx_game->exit_xpm);
	mlx_game->player->player_can_exit = 1;
}

int	check_key(mlx_key_data_t keydata)
{
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) && \
	(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		return ('w');
	if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_DOWN) && \
	(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		return ('a');
	if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_LEFT) && \
	(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		return ('s');
	if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT) && \
	(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		return ('d');
	else
		return ('\0');
}

void	check_if_collectible_taken(t_mlx *mlx_game)
{
	int			i;
	t_player	*player;
	mlx_image_t	*collectible;

	player = mlx_game->player;
	collectible = mlx_game->collectible_img;
	i = 0;
	while (i < mlx_game->collectible_cnt)
	{
		if (player->player_img->instances[0].x == \
		collectible->instances[i].x && player->player_img->instances[0].y == \
		collectible->instances[i].y)
		{
			collectible->instances[i].x += mlx_game->winsize->width * 20;
			collectible->instances[i].y += mlx_game->winsize->height * 20;
			collectible->count--;
			mlx_game->player->score++;
			break ;
		}
		i++;
	}
}

void	my_closehook(void *param)
{
	end_game((t_mlx *)param, "You quit!");
}

void	end_game(t_mlx *mlx_game, const char *message)
{
	ft_printf("Total moves -------> %d\n", mlx_game->player->total_moves);
	ft_printf("%s\n", message);
	mlx_terminate(mlx_game->mlx);
	ft_free_ptr_all(mlx_game);
	exit(EXIT_SUCCESS);
}