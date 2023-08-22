#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct t_winsize
{
	int	width;
	int	height;
	int	rows;
	int	cols;
}	t_winsize;

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
	int				side_face_start;
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
	char			*valid_chars;
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
	char	exit;
}	t_valid_path;

void	ft_free_ptr_all(t_mlx *mlx_game);
void	ft_free_lst(t_list **headref);
void	ft_error(t_mlx *mlx_game, const char *message);

void	is_map_valid(t_mlx *mlx_game, char exit);
void	is_map_ext_ber(t_mlx *mlx_game, char *path);

int		check_key(mlx_key_data_t keydata);

void	check_if_collectible_taken(t_mlx *mlx_game);

void	my_closehook(void *param);

void	open_exit_door(t_mlx *mlx_game, int x, int y);
void	end_game(t_mlx *mlx_game, const char *message);

void	set_window_size(t_mlx *mlx_game);
int		get_img_size(t_mlx *mlx_game);

void	read_map(t_mlx *mlx_game, int fd);
void	print_map(t_mlx *mlx_game);

int		has_valid_path(t_list **headref, t_winsize *winsize, char exit);
#endif //UTILS_H