/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:29:06 by gbeaudoi          #+#    #+#             */
/*   Updated: 2024/10/31 16:13:44 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_r_rotate(t_vec *vec)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = vec->dir[X];
	old_planex = vec->plane[X];
	vec->dir[X] = vec->dir[X] * cos(R_SPEED) - vec->dir[Y] * sin(R_SPEED);
	vec->dir[Y] = old_dirx * sin(R_SPEED) + vec->dir[Y] * cos(R_SPEED);
	vec->plane[X] = vec->plane[X] * cos(R_SPEED) - vec->plane[Y] * sin(R_SPEED);
	vec->plane[Y] = old_planex * sin(R_SPEED) + vec->plane[Y] * cos(R_SPEED);
	return (1);
}

int	ft_l_rotate(t_vec *vec)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = vec->dir[X];
	old_planex = vec->plane[X];
	vec->dir[X] = vec->dir[X] * cos(-R_SPEED) - vec->dir[Y] * sin(-R_SPEED);
	vec->dir[Y] = old_dirx * sin(-R_SPEED) + vec->dir[Y] * cos(-R_SPEED);
	vec->plane[X] = vec->plane[X] * cos(-R_SPEED) - vec->plane[Y]
		* sin(-R_SPEED);
	vec->plane[Y] = old_planex * sin(-R_SPEED) + vec->plane[Y] * cos(-R_SPEED);
	return (1);
}

int	ft_display_moves(t_cub *cub)
{
	cub->vec->moved += ft_moving(cub, cub->vec);
	if (cub->vec->moved == 0)
		return (1);
	ft_raycasting(cub, -1);
	return (0);
}
