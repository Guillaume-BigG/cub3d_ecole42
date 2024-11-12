/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:21:12 by guillaumebe       #+#    #+#             */
/*   Updated: 2024/11/12 18:25:50 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_color_helper(char **rgb, int i, t_cub *cub, char type)
{
	if (!ft_rgb(rgb[i]) || ((ft_strlen(rgb[i]) > 3 && (ft_atoi(rgb[i]) != 0))
			|| ft_strlen(rgb[i]) < 1))
		return (ft_free_tab(rgb), 0);
	if (ft_atoi(rgb[i]) > 255)
		return (ft_free_tab(rgb), 0);
	if (type == 'F')
		cub->tabf[i] = ft_atoi(rgb[i]);
	else if (type == 'C')
		cub->tabc[i] = ft_atoi(rgb[i]);
	return (1);
}

void	ft_get_dims(t_cub *cub)
{
	int	i;

	i = -1;
	while (cub->map[++i])
	{
		if (ft_strlen(cub->map[i]) > cub->width)
			cub->width = ft_strlen(cub->map[i]);
	}
	cub->height = i - 1;
}

void	ft_fill_map_with_spaces(t_cub *cub)
{
	char	*spaces;
	int		i;
	int		j;
	size_t	diff;

	ft_get_dims(cub);
	i = -1;
	while (cub->map[++i])
	{
		diff = cub->width - ft_strlen(cub->map[i]);
		j = -1;
		spaces = ft_calloc((diff) + 1, sizeof(char));
		if (!spaces)
			ft_error(cub, MALLOC_ERROR);
		while (diff > 0)
		{
			spaces[++j] = 32;
			diff--;
		}
		if (cub->width - ft_strlen(cub->map[i]) > 0)
			cub->map[i] = ft_strjoin_gnl(cub->map[i], spaces);
		if (!cub->map[i])
			(free(spaces), ft_error(cub, MALLOC_ERROR));
		free(spaces);
	}
}

void	ft_check_walls(t_cub *cub)
{
	size_t	x;
	size_t	y;
	char	c;

	y = -1;
	while (cub->map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			c = cub->map[y][x];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (y == 0 || x == 0 || y == cub->height || x + 1 == cub->width)
					ft_error(cub, "Detected: Lack of Wall\n");
				else if (cub->map[y + 1][x] == 32 || cub->map[y - 1][x] == 32
					|| cub->map[y][x + 1] == 32 || cub->map[y][x - 1] == 32)
					ft_error(cub, "Detected: Lack of Wall\n");
			}
		}
	}
}

void	ft_check_map_chars(t_cub *cub)
{
	int	i;
	int	j;
	int	info_player;

	i = -1;
	info_player = 0;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] != 'N' && cub->map[i][j] != 'S'
				&& cub->map[i][j] != 'E' && cub->map[i][j] != 'W'
				&& cub->map[i][j] != '1' && cub->map[i][j] != '0'
				&& cub->map[i][j] != ' ')
				ft_error(cub, "Detected: Unrecognized character in map\n");
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S'
				|| cub->map[i][j] == 'E' || cub->map[i][j] == 'W')
				info_player++;
		}
	}
	if (info_player != 1)
		ft_error(cub, "Detected: Too many starting position");
}
