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

/*
It is to be noted that 1400 and 2590 here represents \
the max of the screen where this program was coded
*/
int	get_img_size(t_mlx *mlx_game)
{
	int	img_size;
	int	img_size_by_col;

	img_size = 70;
	img_size_by_col = 0;
	if (mlx_game->winsize->rows > 20)
		img_size = 1400 / mlx_game->winsize->rows;
	if (mlx_game->winsize->cols > 37)
		img_size_by_col = 2590 / mlx_game->winsize->cols;
	if (img_size_by_col && img_size_by_col < img_size)
		return (img_size_by_col);
	return (img_size);
}

void	get_side_face_start(t_mlx *mlx_game)
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

void	play_game(t_mlx *mlx_game)
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
	is_map_valid(mlx_game);
	play_game(mlx_game);
	mlx_terminate(mlx_game->mlx);
	return (0);
}
