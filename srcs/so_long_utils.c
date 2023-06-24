/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:12:07 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/23 17:00:37 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_ptr_all(t_mlx *mlx_game)
{
	ft_free(mlx_game->player);
	ft_free(mlx_game->winsize);
	ft_free_lst(&(mlx_game->headref));
	ft_free(mlx_game);
}

void	get_wall_size(int *hor_wall, int *ver_wall, t_list *headref)
{
	t_list	*current;

	current = headref;
	*hor_wall += ft_strlen(headref->content);
	while (current)
	{
		*ver_wall += 1;
		current = current->next;
	}
}

void	open_exit_door(t_mlx *mlx_game, int x, int y)
{
	mlx_delete_image(mlx_game->mlx, mlx_game->exit_img);
	mlx_game->exit_texture = mlx_load_png("../resources/exit-open.png");
	mlx_game->exit_img = mlx_texture_to_image(mlx_game->mlx, mlx_game->exit_texture);
	mlx_image_to_window(mlx_game->mlx, mlx_game->exit_img, x, y);
	mlx_delete_texture(mlx_game->exit_texture);
	mlx_game->player->player_can_exit = 1;
}

void	end_game(t_mlx *mlx_game, const char *message)
{
	ft_printf("Total moves -------> %d\n", mlx_game->player->total_moves);
	ft_printf("%s\n", message);
	print_map(mlx_game);
	// mlx_delete_image(mlx_game->mlx, mlx_game->collectible_img);
	// mlx_delete_image(mlx_game->mlx, mlx_game->exit_img);
	// mlx_delete_image(mlx_game->mlx, mlx_game->player->player_img);
	// mlx_delete_image(mlx_game->mlx, mlx_game->wall_img);
	// mlx_close_window(mlx_game->mlx);
	mlx_terminate(mlx_game->mlx);
	ft_free_ptr_all(mlx_game);
	system("leaks so_long");
	exit(EXIT_SUCCESS);
}