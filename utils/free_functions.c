/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 19:00:13 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/30 17:01:00 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_error(t_mlx *mlx_game, const char *message)
{
	ft_free_lst(&(mlx_game->headref));
	ft_free(mlx_game->winsize);
	ft_free(mlx_game);
	write(1, "Error\n", 7);
	ft_printf("%s\n", message);
	exit(EXIT_FAILURE);
}

void	ft_free_lst(t_list **headref)
{
	t_list	*current;

	if (!(*headref))
		return ;
	while ((*headref)->next)
	{
		current = *headref;
		*headref = (*headref)->next;
		ft_free(current->content);
		ft_free(current);
	}
	ft_free((*headref)->content);
	ft_free(*headref);
}

void	ft_free_ptr_all(t_mlx *mlx_game)
{
	ft_free(mlx_game->player);
	ft_free(mlx_game->winsize);
	ft_free_lst(&(mlx_game->headref));
	ft_free(mlx_game);
}
