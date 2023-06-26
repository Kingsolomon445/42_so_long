/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:26:44 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/26 15:25:47 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	is_map_ext_ber(t_mlx *mlx_game, char *path)
{
	int	path_len;

	path_len = ft_strlen(path);
	if (*(path + --path_len) != 'r')
		ft_error(mlx_game, "Invalid Extension\n");
	if (*(path + --path_len) != 'e')
		ft_error(mlx_game, "Invalid Extension\n");
	if (*(path + --path_len) != 'b')
		ft_error(mlx_game, "Invalid Extension\n");
	if (*(path + --path_len) != '.')
		ft_error(mlx_game, "Invalid Extension\n");
}

void	is_line_valid(char *line, t_mlx *mlx_game)
{
	int	i;

	i = 0;
	if (!line)
		ft_error(mlx_game, "Empty map!\n");
	if (*line == '\n' || *line == '\0')
		ft_error(mlx_game, "Empty line in map!\n");
	while (*(line + i))
	{
		if (!ft_strchr("01ECPX", *(line + i)) && *(line + i + 1))
		{
			ft_free(line);
			ft_error(mlx_game, "Invalid character in map\n");
		}
		i++;
	}
}

t_list	*make_new_node(char *line)
{
	char	*new_line;

	if (ft_strchr(line, '\n'))
	{
		new_line = ft_strtrim((const char *)line, "\n");
		ft_free(line);
		return (ft_lstnew(new_line));
	}
	else
		return (ft_lstnew(line));
}

void	read_map(t_mlx *mlx_game, int fd)
{
	char	*line;
	t_list	*new;

	line = get_next_line(fd);
	is_line_valid(line, mlx_game);
	mlx_game->headref = make_new_node(line);
	if (!mlx_game->headref)
		ft_error(mlx_game, "Allocation fails!\n");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return ;
		is_line_valid(line, mlx_game);
		new = make_new_node(line);
		if (!new)
			ft_error(mlx_game, "Allocation fails!\n");
		ft_lstadd_back(&(mlx_game->headref), new);
	}
}

void	print_map(t_mlx *mlx_game)
{
	t_list	*current;

	current = mlx_game->headref;
	while (current)
	{
		ft_printf("%s\n", current->content);
		current = current->next;
	}
}
