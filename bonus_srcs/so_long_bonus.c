/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:19:09 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/30 17:08:33 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	get_side_face_start(t_mlx *mlx_game)
{
	t_list	*current;
	char	*line;
	char	*prev_line;

	current = mlx_game->headref;
	mlx_game->player->side_face_start = 'f';
	prev_line = NULL;
	while (current)
	{
		line = current->content;
		if (check_for_side_to_face(mlx_game, line, prev_line))
			break ;
		prev_line = line;
		current = current->next;
	}
}

static void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_mlx		*mlx_game;

	mlx_game = (t_mlx *)param;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || \
	keydata.action == MLX_REPEAT))
		end_game(mlx_game, "You quit!");
	else
		player_moves(mlx_game, keydata);
	check_if_collectible_taken(mlx_game);
}

static void	my_loophook(void *param)
{
	t_mlx		*mlx_game;
	int			previous_score;

	mlx_game = (t_mlx *)param;
	previous_score = mlx_game->player->score;
	if (mlx_is_key_down(mlx_game->mlx, MLX_KEY_SPACE))
		shoot_fire(mlx_game);
	if (mlx_game->fire_img)
		update_fire(mlx_game);
	if (mlx_game->fire_img)
		check_if_enemy_hit(mlx_game);
	if (mlx_game->collectible_img->count == 0 && \
	mlx_game->player->player_img->instances[0].x == \
	mlx_game->exit_img->instances[0].x && \
	mlx_game->player->player_img->instances[0].y == \
	mlx_game->exit_img->instances[0].y && mlx_game->player->player_can_exit)
		end_game(mlx_game, "You win!");
	check_if_collectible_taken(mlx_game);
	if (previous_score < mlx_game->player->score)
		update_str_img(mlx_game);
	if (mlx_game->player->have_enemy)
		check_if_collide_with_enemy(mlx_game);
	if (mlx_game->collectible_img->count <= 0)
		open_exit_door(mlx_game, mlx_game->exit_img->instances[0].x, \
		mlx_game->exit_img->instances[0].y);
}


static void	play_game(t_mlx *mlx_game)
{
	mlx_game->player = malloc(sizeof(t_player));
	if (!mlx_game->player)
		ft_error(mlx_game, "Allocation failed!");
	mlx_game->img_size = get_img_size(mlx_game);
	get_side_face_start(mlx_game);
	mlx_game->player->side_facing = mlx_game->player->side_face_start;
	set_ups(mlx_game);
	mlx_key_hook(mlx_game->mlx, &my_keyhook, mlx_game);
	mlx_loop_hook(mlx_game->mlx, &my_loophook, mlx_game);
	mlx_close_hook(mlx_game->mlx, &my_closehook, mlx_game);
	mlx_loop(mlx_game->mlx);
	mlx_close_window(mlx_game->mlx);
}

int	main(int argc, char *argv[])
{
	int		fd;
	t_mlx	*mlx_game;
	char	*path;

	mlx_game = malloc(sizeof(t_mlx));
	if (!mlx_game)
		return (ft_printf("Error\nAllocation failed!\n"), 1);
	mlx_game->headref = NULL;
	mlx_game->winsize = NULL;
	mlx_game->valid_chars = "01ECPX";
	if (argc != 2)
		ft_error(mlx_game, "Invalid arguments!\n");
	path = argv[1];
	is_map_ext_ber(mlx_game, path);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error(mlx_game, "Error opening file");
	read_map(mlx_game, fd);
	close(fd);
	mlx_game->winsize = malloc(sizeof(t_winsize));
	if (!mlx_game->winsize)
		ft_error(mlx_game, "Allocation failed!");
	is_map_valid(mlx_game, 'X');
	play_game(mlx_game);
	mlx_terminate(mlx_game->mlx);
	return (0);
}
