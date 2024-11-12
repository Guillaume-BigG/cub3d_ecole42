/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:30:00 by guillaumebe       #+#    #+#             */
/*   Updated: 2024/10/31 19:51:16 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_plane(t_vec *vec, char c)
{
	if (c == 'N')
	{
		vec->plane[X] = 0.66;
		vec->plane[Y] = 0;
	}
	if (c == 'S')
	{
		vec->plane[X] = -0.66;
		vec->plane[Y] = 0;
	}
	if (c == 'E')
	{
		vec->plane[X] = 0;
		vec->plane[Y] = 0.66;
	}
	if (c == 'W')
	{
		vec->plane[X] = 0;
		vec->plane[Y] = -0.66;
	}
}

int	*ft_fill_texture(t_cub *cub, char *texture)
{
	t_img	tmp;
	int		*array;
	int		x;
	int		y;

	ft_load_xpm(cub, &tmp, texture);
	array = ft_calloc(1, sizeof(int) * (IMG_SIZE * IMG_SIZE));
	if (!array)
		ft_error(cub, MALLOC_ERROR);
	y = -1;
	while (++y < IMG_SIZE)
	{
		x = -1;
		while (++x < IMG_SIZE)
			array[y * IMG_SIZE + x] = tmp.addr[y * IMG_SIZE + x];
	}
	mlx_destroy_image(cub->mlx, tmp.mlx_img);
	return (array);
}

void	ft_init_texture(t_cub *cub)
{
	cub->texture = ft_calloc(5, sizeof(int *));
	if (!cub->texture)
		ft_error(cub, MALLOC_ERROR);
	cub->texture[NO] = ft_fill_texture(cub, cub->no);
	cub->texture[SO] = ft_fill_texture(cub, cub->so);
	cub->texture[EA] = ft_fill_texture(cub, cub->ea);
	cub->texture[WE] = ft_fill_texture(cub, cub->we);
}

void	ft_init_pos(int y, int x, char c, t_vec *vec)
{
	vec->pos[X] = (double)x + 0.5;
	vec->pos[Y] = (double)y + 0.5;
	if (c == 'N')
	{
		vec->dir[X] = 0;
		vec->dir[Y] = -1;
	}
	else if (c == 'S')
	{
		vec->dir[X] = 0;
		vec->dir[Y] = 1;
	}
	else if (c == 'E')
	{
		vec->dir[X] = 1;
		vec->dir[Y] = 0;
	}
	else if (c == 'W')
	{
		vec->dir[X] = -1;
		vec->dir[Y] = 0;
	}
	ft_init_plane(vec, c);
}

void	ft_init_mlx_and_vec(t_cub *cub)
{
	int	y;
	int	x;

	cub->mlx = mlx_init();
	if (!cub->mlx)
		ft_error(cub, MALLOC_ERROR);
	cub->win = mlx_new_window(cub->mlx, SCREEN_W, SCREEN_H,
			"We're done with C (hopefully)");
	if (!cub->win)
		ft_error(cub, MALLOC_ERROR);
	y = -1;
	cub->vec = ft_calloc(1, sizeof(t_vec));
	if (!cub->vec)
		ft_error(cub, MALLOC_ERROR);
	while (cub->map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S'
				|| cub->map[y][x] == 'E' || cub->map[y][x] == 'W')
				ft_init_pos(y, x, cub->map[y][x], cub->vec);
		}
	}
}
