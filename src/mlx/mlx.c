/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:02:01 by guillaumebe       #+#    #+#             */
/*   Updated: 2024/10/31 19:51:23 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_img(t_img *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->img_width = 0;
	img->img_height = 0;
}

void	ft_load_xpm(t_cub *cub, t_img *img, char *tex)
{
	ft_init_img(img);
	img->mlx_img = mlx_xpm_file_to_image(cub->mlx, tex, &img->img_width,
			&img->img_height);
	if (!img->mlx_img)
		ft_error(cub, MALLOC_ERROR);
	img->addr = (int *)mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
}

void	ft_destroy_mlx(t_cub *cub)
{
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
}

int	ft_handle_keypress(int keysym, t_cub *cub)
{
	if (keysym == XK_Escape)
		ft_destroy(cub);
	if (keysym == XK_w)
		cub->vec->move[Y] = 1;
	if (keysym == XK_s)
		cub->vec->move[Y] = -1;
	if (keysym == XK_a)
		cub->vec->move[X] = -1;
	if (keysym == XK_d)
		cub->vec->move[X] = 1;
	if (keysym == XK_Left)
		cub->vec->rotate -= 1;
	if (keysym == XK_Right)
		cub->vec->rotate += 1;
	return (0);
}

int	ft_handle_keyrelease(int key, t_cub *cub)
{
	if (key == XK_w && cub->vec->move[Y] == 1)
		cub->vec->move[Y] = 0;
	if (key == XK_s && cub->vec->move[Y] == -1)
		cub->vec->move[Y] = 0;
	if (key == XK_a && cub->vec->move[X] == -1)
		cub->vec->move[X] = 0;
	if (key == XK_d && cub->vec->move[X] == 1)
		cub->vec->move[X] = 0;
	if (key == XK_Left && cub->vec->rotate <= 1)
		cub->vec->rotate = 0;
	if (key == XK_Right && cub->vec->rotate >= 1)
		cub->vec->rotate = 0;
	return (0);
}
