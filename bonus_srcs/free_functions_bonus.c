/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 19:00:13 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/28 19:12:14 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_free_double_int_ptr(int	**ptr, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		ft_free(*(ptr + i));
		i++;
	}
	ft_free(ptr);
}

void	ft_free_double_str_ptr(char	**ptr)
{
	int	i;

	i = 0;
	while (*(ptr + i))
	{
		ft_free(*(ptr + i));
		i++;
	}
	ft_free(ptr);
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
