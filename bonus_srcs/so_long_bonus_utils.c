/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:12:07 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/30 15:07:07 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	is_valid_move(int row, int col, char **map, t_winsize *winsize)
{
	if (row >= 0 && row < winsize->rows && col >= 0 && col < \
	winsize->cols && map[row][col] != '1')
		return (1);
	return (0);
}

void	flood_fill(int row, int col, t_valid_path *vars, t_winsize *winsize)
{
	if (!is_valid_move(row, col, vars->map, winsize) || vars->visited[row][col])
		return ;
	vars->visited[row][col] = 1;
	flood_fill(row - 1, col, vars, winsize);
	flood_fill(row + 1, col, vars, winsize);
	flood_fill(row, col - 1, vars, winsize);
	flood_fill(row, col + 1, vars, winsize);
}

void	get_wall_size(int *hor_wall, int *ver_wall, t_list *headref)
{
	*hor_wall += ft_strlen(headref->content);
	*ver_wall += ft_lstsize(headref);
}

void	open_exit_door(t_mlx *mlx_game, int x, int y)
{
	mlx_delete_image(mlx_game->mlx, mlx_game->exit_img);
	mlx_game->exit_xpm = mlx_load_xpm42("resources/door_open.xpm42");
	mlx_game->exit_img = mlx_texture_to_image(\
	mlx_game->mlx, &(mlx_game->exit_xpm->texture));
	mlx_resize_image(\
	mlx_game->exit_img, mlx_game->img_size, mlx_game->img_size);
	mlx_image_to_window(mlx_game->mlx, mlx_game->exit_img, x, y);
	mlx_set_instance_depth(&(mlx_game->exit_img->instances[0]), \
	(int)mlx_game->exit_img->instances[0].z - 10);
	mlx_delete_xpm42(mlx_game->exit_xpm);
	mlx_game->player->player_can_exit = 1;
}

void	end_game(t_mlx *mlx_game, const char *message)
{
	ft_printf("%s\n", message);
	mlx_terminate(mlx_game->mlx);
	ft_free_ptr_all(mlx_game);
	exit(EXIT_SUCCESS);
}
