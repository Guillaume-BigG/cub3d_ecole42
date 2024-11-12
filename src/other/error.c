/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:39:09 by guillaumebe       #+#    #+#             */
/*   Updated: 2024/10/31 18:14:24 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_texture(t_cub *cub)
{
	if (cub->texture)
	{
		if (cub->texture[NO])
			free(cub->texture[NO]);
		if (cub->texture[SO])
			free(cub->texture[SO]);
		if (cub->texture[EA])
			free(cub->texture[EA]);
		if (cub->texture[WE])
			free(cub->texture[WE]);
	}
	if (cub->texture)
		free(cub->texture);
	if (cub->vec)
		free(cub->vec);
}

void	ft_free_infos(t_cub *cub)
{
	if (cub->no)
		free(cub->no);
	if (cub->so)
		free(cub->so);
	if (cub->we)
		free(cub->we);
	if (cub->ea)
		free(cub->ea);
	if (cub->floor)
		free(cub->floor);
	if (cub->ceiling)
		free(cub->ceiling);
}

void	ft_free_all(t_cub *cub)
{
	if (cub->map)
		ft_free_tab(cub->map);
	ft_free_infos(cub);
	ft_free_texture(cub);
	ft_destroy_mlx(cub);
}

int	ft_destroy(t_cub *cub)
{
	ft_free_all(cub);
	printf("Exit\n");
	exit(0);
	return (0);
}

void	ft_error(t_cub *cub, char *err_msg)
{
	ft_printf_err_err("Error\n");
	if (err_msg)
		ft_printf_err_err("%s", err_msg);
	ft_free_all(cub);
	exit(1);
}
