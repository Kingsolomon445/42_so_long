/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:47:51 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/30 13:45:58 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	**init_map(t_list **headref, int rows)
{
	char	**map;
	t_list	*current;
	int		i;

	map = malloc(sizeof(char *) * (rows + 1));
	current = *headref;
	i = 0;
	while (current)
	{
		*(map + i) = ft_strdup(current->content);
		current = current->next;
		i++;
	}
	*(map + i) = NULL;
	return (map);
}

static void	init_vars(t_valid_path *vars, int rows, int cols, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (map[i][j] == 'P')
			{
				vars->player_row = i;
				vars->player_col = j;
			}
			else if (map[i][j] == vars->exit)
			{
				vars->exit_row = i;
				vars->exit_col = j;
			}
			j++;
		}
		i++;
	}
}

static int	is_valid_move(int row, int col, char **map, t_winsize *winsize)
{
	if (row >= 0 && row < winsize->rows && col >= 0 && col < \
	winsize->cols && map[row][col] != '1')
		return (1);
	return (0);
}

static void	flood_fill(int row, int col, t_valid_path *vars, t_winsize *winsize)
{
	if (!is_valid_move(row, col, vars->map, winsize) || vars->visited[row][col])
		return ;
	vars->visited[row][col] = 1;
	flood_fill(row - 1, col, vars, winsize);
	flood_fill(row + 1, col, vars, winsize);
	flood_fill(row, col - 1, vars, winsize);
	flood_fill(row, col + 1, vars, winsize);
}

int	has_valid_path(t_list **headref, t_winsize *winsize, char exit)
{
	t_valid_path	*vars;
	int				i;
	int				j;
	int				res;

	vars = malloc(sizeof(t_valid_path));
	vars->map = init_map(headref, winsize->rows);
	vars->exit = exit;
	init_vars(vars, winsize->rows, winsize->cols, vars->map);
	vars->visited = ft_make_int_array(winsize->rows, winsize->cols);
	flood_fill(vars->player_row, vars->player_col, vars, winsize);
	i = -1;
	while (++i < winsize->rows)
	{
		j = -1;
		while (++j < winsize->cols)
		{
			if (vars->map[i][j] == 'C' && !vars->visited[i][j])
				return (ft_free_int_array(vars->visited, winsize->rows), \
				ft_free_split(vars->map), ft_free(vars), 0);
		}
	}
	res = vars->visited[vars->exit_row][vars->exit_col];
	return (ft_free_int_array(vars->visited, winsize->rows), \
	ft_free_split(vars->map), ft_free(vars), res);
}
