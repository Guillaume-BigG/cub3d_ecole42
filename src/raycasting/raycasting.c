/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:22:27 by guillaumebe       #+#    #+#             */
/*   Updated: 2024/10/31 19:52:09 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_img_addr(t_cub *cub, int **buffer, int i)
{
	int		j;
	int		index;
	t_img	img;

	ft_init_img(&img);
	img.mlx_img = mlx_new_image(cub->mlx, SCREEN_W, SCREEN_H);
	img.addr = (int *)mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len,
			&img.endian);
	while (++i < SCREEN_H)
	{
		j = -1;
		while (++j < SCREEN_W)
		{
			index = i * (img.line_len / 4) + j;
			if (buffer[i][j] > 0)
				img.addr[index] = buffer[i][j];
			else if (i < SCREEN_H / 2)
				img.addr[index] = cub->c_color;
			else
				img.addr[index] = cub->f_color;
		}
	}
	mlx_put_image_to_window(cub->mlx, cub->win, img.mlx_img, 0, 0);
	mlx_destroy_image(cub->mlx, img.mlx_img);
}

static void	ft_loop_reset(int **buffer)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (i < SCREEN_H)
		i++;
	while (++j <= i)
		free(buffer[j]);
	free(buffer);
}

static void	ft_loop_info(t_cub *cub, t_vec *vec, int x, int **buffer)
{
	while (++x < SCREEN_W)
	{
		ft_ray_pos(vec, x);
		ft_side_dist(vec);
		ft_dda(cub, vec);
		ft_start_draw(vec);
		ft_draw(cub, vec, x, buffer);
	}
	ft_img_addr(cub, buffer, -1);
	ft_loop_reset(buffer);
}

void	ft_raycasting(t_cub *cub, int i)
{
	t_vec	*vec;
	int		buff_index;
	int		**buffer;

	buff_index = -1;
	buffer = ft_calloc(SCREEN_H + 1, sizeof(int *));
	if (!buffer)
		ft_error(cub, MALLOC_ERROR);
	while (++buff_index < SCREEN_H)
	{
		buffer[buff_index] = ft_calloc(SCREEN_W + 1, sizeof(int));
		if (!buffer[buff_index])
		{
			while (++i < buff_index)
				free(buffer[buff_index]);
			free(buffer);
			ft_error(cub, MALLOC_ERROR);
		}
	}
	vec = cub->vec;
	vec->hit = 0;
	ft_loop_info(cub, vec, -1, buffer);
}
