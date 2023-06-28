/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_path_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:47:51 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/28 19:10:46 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	is_valid_move(int row, int col, char **map, int rows, int cols)
{
	if (row >= 0 && row < rows && col >= 0 && col < \
	cols && map[row][col] != '1')
		return (1);
	return (0);
}

void	flood_fill(int row, int col, char **map, \
int **visited, int rows, int cols)
{
	if (!is_valid_move(row, col, map, rows, cols) || visited[row][col])
		return ;
	visited[row][col] = 1;
	flood_fill(row - 1, col, map, visited, rows, cols);
	flood_fill(row + 1, col, map, visited, rows, cols);
	flood_fill(row, col - 1, map, visited, rows, cols);
	flood_fill(row, col + 1, map, visited, rows, cols);
}

char	**init_map(t_list **headref, int rows)
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

int	**init_visited(int rows, int cols)
{
	int	**visited;
	int	*tab;
	int	i;
	int	j;

	visited = malloc(sizeof(int *) * rows);
	i = 0;
	while (i < rows)
	{
		tab = malloc(sizeof(int) * cols);
		j = 0;
		while (j < cols)
		{
			*(tab + j) = 0;
			j++;
		}
		*(visited + i) = tab;
		i++;
	}
	return (visited);
}

void	init_vars(t_valid_path *vars, int rows, int cols, char **map)
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
			else if (map[i][j] == 'X')
			{
				vars->exit_row = i;
				vars->exit_col = j;
			}
			j++;
		}
		i++;
	}
}

int	has_valid_path(t_list **headref, int rows, int cols)
{
	t_valid_path	*vars;
	int				i;
	int				j;
	int				res;

	vars = malloc(sizeof(t_valid_path));
	vars->map = init_map(headref, rows);
	init_vars(vars, rows, cols, vars->map);
	vars->visited = init_visited(rows, cols);
	flood_fill(vars->player_row, vars->player_col, \
	vars->map, vars->visited, rows, cols);
	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (++j < cols)
		{
			if (vars->map[i][j] == 'C' && !vars->visited[i][j])
				return (ft_free_double_int_ptr(vars->visited, rows), \
				ft_free_double_str_ptr(vars->map), ft_free(vars), 0);
		}
	}
	res = vars->visited[vars->exit_row][vars->exit_col];
	return (ft_free_double_int_ptr(vars->visited, rows), \
	ft_free_double_str_ptr(vars->map), ft_free(vars), res);
}
