/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_follow.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:27:18 by guillaumebe       #+#    #+#             */
/*   Updated: 2024/11/01 15:41:28 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_ray_pos(t_vec *vec, int x)
{
	vec->camera[X] = 2 * x / (double)SCREEN_W - 1;
	vec->ray_dir[X] = vec->dir[X] + vec->plane[X] * vec->camera[X];
	vec->ray_dir[Y] = vec->dir[Y] + vec->plane[Y] * vec->camera[X];
	vec->coordinate[X] = (int)vec->pos[X];
	vec->coordinate[Y] = (int)vec->pos[Y];
	vec->dd[X] = fabs(1 / vec->ray_dir[X]);
	vec->dd[Y] = fabs(1 / vec->ray_dir[Y]);
}

void	ft_side_dist(t_vec *vec)
{
	if (vec->ray_dir[X] < 0)
	{
		vec->step[X] = -1;
		vec->side_dist[X] = ((vec->pos[X] - vec->coordinate[X]) * vec->dd[X]);
	}
	else
	{
		vec->step[X] = 1;
		vec->side_dist[X] = ((vec->coordinate[X] + 1.0 - vec->pos[X])
				* vec->dd[X]);
	}
	if (vec->ray_dir[Y] < 0)
	{
		vec->step[Y] = -1;
		vec->side_dist[Y] = ((vec->pos[Y] - vec->coordinate[Y]) * vec->dd[Y]);
	}
	else
	{
		vec->step[Y] = 1;
		vec->side_dist[Y] = ((vec->coordinate[Y] + 1.0 - vec->pos[Y])
				* vec->dd[Y]);
	}
}

void	ft_dda(t_cub *cub, t_vec *vec)
{
	vec->hit = 0;
	while (vec->hit == 0)
	{
		if (vec->side_dist[X] < vec->side_dist[Y])
		{
			vec->side_dist[X] += vec->dd[X];
			vec->coordinate[X] += vec->step[X];
			vec->side = 0;
		}
		else
		{
			vec->side_dist[Y] += vec->dd[Y];
			vec->coordinate[Y] += vec->step[Y];
			vec->side = 1;
		}
		if (vec->coordinate[Y] < 0.25 || vec->coordinate[X] < 0.25
			|| vec->coordinate[Y] > cub->height - 0.25
			|| vec->coordinate[X] > cub->width - 1.25)
			break ;
		if (cub->map[vec->coordinate[Y]][vec->coordinate[X]] == '1')
			vec->hit = 1;
	}
}

void	ft_start_draw(t_vec *vec)
{
	if (vec->side == 0)
		vec->dist_to_wall = vec->side_dist[X] - vec->dd[X];
	else
		vec->dist_to_wall = vec->side_dist[Y] - vec->dd[Y];
	vec->hori_line = (int)(SCREEN_H / vec->dist_to_wall);
	vec->draw_start = -(vec->hori_line) / 2 + SCREEN_H / 2;
	if (vec->draw_start < 0)
		vec->draw_start = 0;
	vec->draw_end = vec->hori_line / 2 + SCREEN_H / 2;
	if (vec->draw_end >= SCREEN_H)
		vec->draw_end = SCREEN_H - 1;
	if (vec->side == 0)
	{
		if (vec->ray_dir[X] < 0)
			vec->texture_value = WE;
		else
			vec->texture_value = EA;
	}
	else
	{
		if (vec->ray_dir[Y] > 0)
			vec->texture_value = SO;
		else
			vec->texture_value = NO;
	}
}

void	ft_draw(t_cub *cub, t_vec *vec, int x, int **buffer)
{
	if (vec->side == 0)
		vec->wallx = vec->pos[Y] + vec->dist_to_wall * vec->ray_dir[Y];
	else
		vec->wallx = vec->pos[X] + vec->dist_to_wall * vec->ray_dir[X];
	vec->wallx -= floor(vec->wallx);
	vec->tex[X] = (int)(vec->wallx * (double)IMG_SIZE);
	if (vec->side == 0 && vec->ray_dir[X] > 0)
		vec->tex[X] = IMG_SIZE - vec->tex[X] - 1;
	if (vec->side == 1 && vec->ray_dir[Y] < 0)
		vec->tex[X] = IMG_SIZE - vec->tex[X] - 1;
	vec->texture_mov = 1.0 * IMG_SIZE / vec->hori_line;
	vec->texture_pos = (vec->draw_start - SCREEN_H / 2 + vec->hori_line / 2)
		* vec->texture_mov;
	vec->y = vec->draw_start - 1;
	while (++vec->y < vec->draw_end)
	{
		vec->tex[Y] = (int)vec->texture_pos & (IMG_SIZE - 1);
		vec->texture_pos += vec->texture_mov;
		vec->color = cub->texture[vec->texture_value][IMG_SIZE * vec->tex[Y]
			+ vec->tex[X]];
		buffer[vec->y][x] = vec->color;
	}
}
