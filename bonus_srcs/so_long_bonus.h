/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:19:13 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/30 17:05:02 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../utils/utils.h"

int		is_move_valid(t_mlx *mlx_game, int x, int y);
void	check_if_collide_with_enemy(t_mlx *mlx_game);
int		check_if_fire_hit_exit(t_mlx *mlx_game, int x, int y);
int		check_if_fire_hit_wall(t_mlx *mlx_game, int x, int y);
void	check_if_enemy_hit(t_mlx *mlx_game);
int		check_for_side_to_face(t_mlx *mlx_game, char *line, char *prev_line);
void	shoot_fire(t_mlx *mlx_game);
void	update_fire(t_mlx *mlx_game);

void	update_str_img(t_mlx *mlx_game);
void	set_ups(t_mlx *mlx_game);

void	player_moves(t_mlx *mlx_game, mlx_key_data_t keydata);
#endif //SO_LONG_BONUS_H