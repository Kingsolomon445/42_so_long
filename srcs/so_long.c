/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:19:09 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/24 20:28:18 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void ft_error(t_mlx *mlx_game, const char *message)
{
	ft_free_lst(&(mlx_game->headref));
	ft_free(mlx_game);
	write(2, "Error\n", 6);
	ft_printf("%s\n", message);
	exit(EXIT_FAILURE);
}

void	set_ups(t_mlx *mlx_game)
{
	ft_printf("I got here\n");
	set_window_size(mlx_game);
	mlx_game->mlx = mlx_init(mlx_game->winsize->width, mlx_game->winsize->height, "so long", 0);
	if (!mlx_game->mlx)
		ft_error(mlx_game, "mlx initialization failed!");
	set_up_images(mlx_game);
	set_up_img_pos(mlx_game);
}

//200 width is 5 walls in size
void	init_mlx_game(t_mlx *mlx_game)
{
	mlx_game->player = malloc(sizeof(t_player));
	mlx_game->winsize = malloc(sizeof(t_winsize));
	if (!mlx_game->player || !mlx_game->winsize)
		ft_error(mlx_game, "Allocation failed!");
	mlx_game->img_size = 70;
}

int main(void)
{
	int		fd;
	t_mlx	*mlx_game;
	char	*path;

	mlx_game = malloc(sizeof(t_mlx));
	if (!mlx_game)
		return(ft_printf("Error\nAllocation failed!\n"), 1);
	mlx_game->headref = NULL;
	path = "maps/valid/4.ber";
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error(mlx_game, "Error opening file");
	read_map(mlx_game, fd);
	close(fd);
	print_map(mlx_game);
	is_map_valid(mlx_game);
	init_mlx_game(mlx_game);
	set_ups(mlx_game);
	mlx_key_hook(mlx_game->mlx, &my_keyhook, mlx_game);
	mlx_loop_hook(mlx_game->mlx, &my_loophook, mlx_game);
	mlx_close_hook(mlx_game->mlx, &my_closehook, mlx_game);
	mlx_loop(mlx_game->mlx);
	mlx_close_window(mlx_game->mlx);
	mlx_terminate(mlx_game->mlx);
	return (0);
}