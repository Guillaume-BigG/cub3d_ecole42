/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:54:10 by guillaumebe       #+#    #+#             */
/*   Updated: 2024/11/12 18:01:41 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_let_it_cub(t_cub *cub)
{
	ft_init_mlx_and_vec(cub);
	ft_init_texture(cub);
	ft_raycasting(cub, -1);
	mlx_hook(cub->win, KeyPress, KeyPressMask, &ft_handle_keypress, cub);
	mlx_hook(cub->win, KeyRelease, KeyReleaseMask, &ft_handle_keyrelease, cub);
	mlx_hook(cub->win, DestroyNotify, 0, &ft_destroy, cub);
	mlx_loop_hook(cub->mlx, &ft_display_moves, cub);
	mlx_loop(cub->mlx);
}

int	ft_map_extension(const char *map_file)
{
	size_t	i;

	i = ft_strlen(map_file);
	if (i < 4 || map_file[i - 1] != 'b' || map_file[i - 2] != 'u' || map_file[i
			- 3] != 'c' || map_file[i - 4] != '.')
		return (0);
	return (1);
}

void	ft_init_struct(t_cub *cub)
{
	cub->map = NULL;
	cub->no = NULL;
	cub->so = NULL;
	cub->we = NULL;
	cub->ea = NULL;
	cub->floor = NULL;
	cub->ceiling = NULL;
	cub->height = 0;
	cub->width = 0;
	cub->mlx = NULL;
	cub->win = NULL;
	cub->texture = NULL;
	cub->vec = NULL;
	cub->info = 0;
}

int	main(int argc, char *argv[])
{
	t_cub	cub;
	int		fd;

	ft_init_struct(&cub);
	if (argc != 2)
		ft_error(&cub, "Detected: Args issue\n");
	fd = open(argv[1], __O_DIRECTORY);
	if (fd > 0)
		(close(fd), ft_error(&cub, "Detected: Directory,\
				please provide a file\n"));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		(ft_error(&cub, "Detected :Error opening the file\n"));
	if (!ft_map_extension(argv[1]))
		(close(fd), ft_error(&cub, "Detected: wrong file extension!\n"));
	ft_parse_file(&cub, fd);
	ft_let_it_cub(&cub);
}
