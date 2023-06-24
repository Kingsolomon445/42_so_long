/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:19:09 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/23 20:40:33 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void ft_error(t_mlx *mlx_game, const char *message)
{
	ft_free_ptr_all(mlx_game);
	write(2, "Error\n", 6);
	ft_printf("%s\n", message);
	exit(EXIT_FAILURE);
}

void	set_ups(t_mlx *mlx_game)
{
	set_window_size(mlx_game);
	mlx_game->mlx = mlx_init(mlx_game->winsize->width, mlx_game->winsize->height, "so long", 0);
	if (!mlx_game->mlx)
		ft_error(mlx_game, "mlx initialization failed!");
	set_up_images(mlx_game);
	set_up_img_pos(mlx_game);
}

void	read_map(t_mlx *mlx_game, int fd)
{
	char	*line;
	t_list	*new;

	line = get_next_line(fd);
	mlx_game->headref = ft_lstnew(line);
	while(line)
	{
		line = get_next_line(fd);
		if (!line)
			return ;
		new = ft_lstnew(line);
		ft_lstadd_back(&(mlx_game->headref), new);
	}
}

void	print_map(t_mlx *mlx_game)
{
	t_list	*current;

	current = mlx_game->headref;
	while (current)
	{
		ft_printf("Printing.....");
		ft_printf("%s\n", current->content);
		current = current->next;
	}
}
//200 width is 5 walls in size

int main(void)
{
	int fd;
	t_mlx *mlx_game;

	mlx_game = malloc(sizeof(t_mlx));
	if (!mlx_game)
		return(ft_printf("Error\nAllocation failed!\n"), 1);
	mlx_game->player = malloc(sizeof(t_player));
	mlx_game->winsize = malloc(sizeof(t_winsize));
	mlx_game->headref = (t_list *)malloc(sizeof(t_list));
	fd = open("maps/short_map.ber", O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error value is: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (!mlx_game->player || !mlx_game->winsize || !mlx_game->headref)
		ft_error(mlx_game, "Allocation failed!");
	mlx_game->img_size = 100;
	read_map(mlx_game, fd);
	close(fd);
	// print_map(mlx_game);
	if (is_map_valid(mlx_game->headref))
		ft_error(mlx_game, "Map is Invalid!");
	set_ups(mlx_game);
	mlx_key_hook(mlx_game->mlx, &my_keyhook, mlx_game);
	mlx_close_hook(mlx_game->mlx, &my_closehook, mlx_game);
	mlx_loop(mlx_game->mlx);
	mlx_close_window(mlx_game->mlx);
	mlx_terminate(mlx_game->mlx);
	return (0);
}