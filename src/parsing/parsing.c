/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:50:01 by guillaumebe       #+#    #+#             */
/*   Updated: 2024/11/12 18:16:10 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_check_colors(t_cub *cub, char *str, char type, int i)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb)
		return (0);
	if (ft_find_tab_size(rgb) != 3)
		return (ft_free_tab(rgb), 0);
	while (rgb[++i])
	{
		rgb[i] = ft_strtrim_free(rgb[i], " ");
		if (!rgb[i])
			return (ft_free_tab(rgb), 0);
		if (ft_atoi(rgb[i]) != 0)
		{
			rgb[i] = ft_strtrim_free(rgb[i], "0");
			if (!rgb[i])
				return (ft_free_tab(rgb), 0);
		}
		if (!ft_check_color_helper(rgb, i, cub, type))
			return (0);
	}
	return (ft_free_tab(rgb), 1);
}

void	ft_trim_info(t_cub *cub, char *line)
{
	if (!cub->no || !cub->so || !cub->we || !cub->ea || !cub->floor
		|| !cub->ceiling)
		(free(line), ft_error(cub,
				"Detected: Malloc error or not all info given in map"));
	cub->no = ft_strtrim_free(cub->no, "\n");
	cub->so = ft_strtrim_free(cub->so, "\n");
	cub->ea = ft_strtrim_free(cub->ea, "\n");
	cub->we = ft_strtrim_free(cub->we, "\n");
	cub->ceiling = ft_strtrim_free(cub->ceiling, "\n");
	cub->floor = ft_strtrim_free(cub->floor, "\n");
	cub->no = ft_strtrim_free(cub->no, " ");
	cub->so = ft_strtrim_free(cub->so, " ");
	cub->ea = ft_strtrim_free(cub->ea, " ");
	cub->we = ft_strtrim_free(cub->we, " ");
	if (!cub->no || !cub->so || !cub->we || !cub->ea || !cub->floor
		|| !cub->ceiling)
		(free(line), ft_error(cub,
				"Detected: Malloc error or not all info given in map"));
}

void	ft_get_info(t_cub *cub, char *line)
{
	while (*line == 32)
		line++;
	if (!ft_strncmp(line, "NO ", 3))
		cub->no = ft_strdup_free(line + 3, cub->no);
	if (!ft_strncmp(line, "SO ", 3))
		cub->so = ft_strdup_free(line + 3, cub->so);
	if (!ft_strncmp(line, "WE ", 3))
		cub->we = ft_strdup_free(line + 3, cub->we);
	if (!ft_strncmp(line, "EA ", 3))
		cub->ea = ft_strdup_free(line + 3, cub->ea);
	if (!ft_strncmp(line, "F ", 2))
	{
		cub->floor = ft_strdup_free(line + 2, cub->floor);
		cub->floor = ft_strtrim_free(cub->floor, "\n");
	}
	if (!ft_strncmp(line, "C ", 2))
	{
		cub->ceiling = ft_strdup_free(line + 2, cub->ceiling);
		cub->ceiling = ft_strtrim_free(cub->ceiling, "\n");
	}
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		cub->info++;
}

int	ft_info_line(char *line)
{
	while (*line == 32)
		line++;
	if (!ft_strncmp(line, "NO ", 3) || (!ft_strncmp(line, "SO ", 3))
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2)
		|| line[0] == '\n')
		return (1);
	else
		return (0);
}

void	ft_parse_file(t_cub *cub, int fd)
{
	char	*line;

	line = ft_gnl_stack(fd);
	while (line && ft_info_line(line))
	{
		ft_get_info(cub, line);
		free(line);
		line = NULL;
		line = ft_gnl_stack(fd);
	}
	ft_trim_info(cub, line);
	if (!ft_check_colors(cub, cub->floor, 'F', -1) || !ft_check_colors(cub,
			cub->ceiling, 'C', -1))
	{
		if (line)
			free(line);
		(close(fd), ft_error(cub, COLOR_ERROR));
	}
	ft_get_map(cub, fd, line);
	if (cub->info != 6)
		(ft_error(cub, "Detected: Duplicate or missing map info/texture\n"));
	cub->f_color = ft_translate_color(cub->tabf);
	cub->c_color = ft_translate_color(cub->tabc);
}
