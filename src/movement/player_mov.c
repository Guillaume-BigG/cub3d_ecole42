/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:30:45 by guillaumebe       #+#    #+#             */
/*   Updated: 2024/10/31 16:13:36 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_moving(t_cub *cub, t_vec *vec)
{
	int	move;

	move = 0;
	if (vec->move[Y] == 1)
		move += ft_y_move(cub, vec, 0);
	if (vec->move[Y] == -1)
		move += ft_y_move(cub, vec, 1);
	if (vec->move[X] == -1)
		move += ft_x_move(cub, vec, 0);
	if (vec->move[X] == 1)
		move += ft_x_move(cub, vec, 1);
	if (vec->rotate < 0)
		move += ft_l_rotate(vec);
	if (vec->rotate > 0)
		move += ft_r_rotate(vec);
	return (move);
}

int	ft_check_if_move(t_cub *cub, t_vec *vec, double x, double y)
{
	if (x < 0.25 || x >= cub->width - 1.25)
		return (0);
	if (vec->pos[Y] < 0.25 || vec->pos[Y] >= cub->height - 0.25)
		return (0);
	if (vec->pos[X] < 0.25 || vec->pos[X] >= cub->width - 1.25)
		return (0);
	if (y < 0.25 || y >= cub->height - 0.25)
		return (0);
	if (cub->map[(int)(y)][(int)(x)] == '1')
		return (0);
	return (1);
}

int	ft_y_move(t_cub *cub, t_vec *vec, int upordown)
{
	double	x_tmp;
	double	y_tmp;

	x_tmp = 0;
	y_tmp = 0;
	if (upordown == 0)
	{
		x_tmp = vec->pos[X] + vec->dir[X] * (P_SPEED * 1.7);
		y_tmp = vec->pos[Y] + vec->dir[Y] * (P_SPEED * 1.7);
	}
	else if (upordown == 1)
	{
		x_tmp = vec->pos[X] - vec->dir[X] * (P_SPEED * 1.7);
		y_tmp = vec->pos[Y] - vec->dir[Y] * (P_SPEED * 1.7);
	}
	if (!ft_check_if_move(cub, vec, x_tmp, y_tmp))
		return (0);
	else
	{
		vec->pos[X] = x_tmp;
		vec->pos[Y] = y_tmp;
	}
	return (1);
}

int	ft_x_move(t_cub *cub, t_vec *vec, int leftorright)
{
	double	x_tmp;
	double	y_tmp;

	x_tmp = 0;
	y_tmp = 0;
	if (leftorright == 0)
	{
		x_tmp = vec->pos[X] + vec->dir[Y] * P_SPEED;
		y_tmp = vec->pos[Y] - vec->dir[X] * P_SPEED;
	}
	else if (leftorright == 1)
	{
		x_tmp = vec->pos[X] - vec->dir[Y] * P_SPEED;
		y_tmp = vec->pos[Y] + vec->dir[X] * P_SPEED;
	}
	if (!ft_check_if_move(cub, vec, x_tmp, y_tmp))
		return (0);
	else
	{
		vec->pos[X] = x_tmp;
		vec->pos[Y] = y_tmp;
	}
	return (1);
}
