/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:19:13 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/28 19:21:57 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct t_winsize
{
	int	width;
	int	height;
}	t_winsize;

typedef struct t_pos
{
	int	x;
	int	y;
	int	y_up;
	int	y_down;
	int	x_left;
	int	x_right;
}	t_pos;

typedef struct t_player
{
	mlx_texture_t	*player_texture;
	mlx_image_t		*player_img;
	int				total_moves;
	int				score;
	int				move_size;
	int				player_can_exit;
	int				have_enemy;
	char			fire_side_facing;
	char			side_facing;
	char			fire_axis;
	int				fire_stopped;
	int				fire_move_size;
}	t_player;

typedef struct t_mlx
{
	xpm_t			*collectible_xpm;
	xpm_t			*fire_xpm;
	xpm_t			*exit_xpm;
	mlx_texture_t	*wall_texture;
	mlx_texture_t	*enemy_texture;
	mlx_texture_t	*background_texture;
	mlx_image_t		*wall_img;
	mlx_image_t		*collectible_img;
	mlx_image_t		*fire_img;
	mlx_image_t		*exit_img;
	mlx_image_t		*enemy_img;
	mlx_image_t		*background_img;
	mlx_image_t		*str_img;
	mlx_t			*mlx;
	t_player		*player;
	t_winsize		*winsize;
	t_list			*headref;
	int				img_size;
	int				collectible_cnt;
}	t_mlx;

typedef struct t_valid_path
{
	int		player_row;
	int		player_col;
	int		exit_row;
	int		exit_col;
	int		**visited;
	char	**map;
}	t_valid_path;

void	is_map_valid(t_mlx *mlx_game);
void	is_map_ext_ber(t_mlx *mlx_game, char *path);
int		is_move_valid(t_mlx *mlx_game, int x, int y);
int		has_valid_path(t_list **headref, int rows, int cols);
int		check_key(mlx_key_data_t keydata);
void	check_if_collectible_taken(t_mlx *mlx_game);
void	check_if_collide_with_enemy(t_mlx *mlx_game);
int		check_if_fire_hit_exit(t_mlx *mlx_game, int x, int y);
int		check_if_fire_hit_wall(t_mlx *mlx_game, int x, int y);
void	check_if_enemy_hit(t_mlx *mlx_game);
void	shoot_fire(t_mlx *mlx_game);
void	update_fire(t_mlx *mlx_game);

void	my_keyhook(mlx_key_data_t keydata, void *param);
void	my_closehook(void *param);
void	my_loophook(void *param);
void	player_moves(t_mlx *mlx_game, mlx_key_data_t keydata);

void	read_map(t_mlx *mlx_game, int fd);
void	print_map(t_mlx *mlx_game);
void	ft_free_ptr_all(t_mlx *mlx_game);
void	ft_free_lst(t_list **headref);
void	ft_free_double_int_ptr(int	**ptr, int rows);
void	ft_free_double_str_ptr(char	**ptr);
void	ft_error(t_mlx *mlx_game, const char *message);
void	open_exit_door(t_mlx *mlx_game, int x, int y);
void	end_game(t_mlx *mlx_game, const char *message);
void	get_wall_size(int *hor_wall, int *ver_wall, t_list *headref);

void	update_player_img(t_mlx *mlx_game, int x, int y);
void	update_str_img(t_mlx *mlx_game);
void	set_window_size(t_mlx *mlx_game);
void	set_up_img_pos(t_mlx *mlx_game);
void	set_up_images(t_mlx *mlx_game);
#endif //SO_LONG_BONUS_H