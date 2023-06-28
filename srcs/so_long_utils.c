/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:12:07 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/28 19:00:41 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_wall_size(int *hor_wall, int *ver_wall, t_list *headref)
{
	t_list	*current;

	current = headref;
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
	mlx_delete_xpm42(mlx_game->exit_xpm);
	mlx_game->player->player_can_exit = 1;
}

void	end_game(t_mlx *mlx_game, const char *message)
{
	ft_printf("Total moves -------> %d\n", mlx_game->player->total_moves);
	ft_printf("%s\n", message);
	mlx_terminate(mlx_game->mlx);
	ft_free_ptr_all(mlx_game);
	system("leaks so_long");
	exit(EXIT_SUCCESS);
}
