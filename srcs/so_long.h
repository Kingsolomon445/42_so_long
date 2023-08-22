/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:19:13 by ofadahun          #+#    #+#             */
/*   Updated: 2023/06/30 17:02:41 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../utils/utils.h"

void	get_side_face_start(t_mlx *mlx_game);

void	set_ups(t_mlx *mlx_game);

void	player_moves(t_mlx *mlx_game, mlx_key_data_t keydata);

#endif //SO_LONG_H