/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:57:53 by guillaumebe       #+#    #+#             */
/*   Updated: 2024/10/31 19:51:38 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_double_lines(t_cub *cub, char *line, char *line2, int flag)
{
	int	i;

	if (line[0] == '\n')
	{
		if (line)
			free(line);
		if (line2)
			free(line2);
		ft_error(cub, "Detected: Empty line in map\n");
	}
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\n' && line[i + 1] == '\n')
			flag = 1;
		if (line[i] != '\n' && line[i] != '\0' && flag == 1)
		{
			if (line)
				free(line);
			if (line2)
				free(line2);
			ft_error(cub, "Detected: Empty line in map\n");
		}
	}
}

char	*ft_str_join_free_both(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (free(s1), free(s2), NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}

void	ft_get_map(t_cub *cub, int fd, char *line)
{
	char	*copy_line;

	copy_line = ft_gnl_stack(fd);
	if (!copy_line)
		(close(fd), ft_error(cub, "Detected: Empty map\n"));
	while (copy_line)
	{
		line = ft_str_join_free_both(line, copy_line);
		if (!line)
			(close(fd), ft_error(cub, MALLOC_ERROR));
		copy_line = ft_gnl_stack(fd);
	}
	close(fd);
	ft_check_double_lines(cub, line, copy_line, 0);
	cub->map = ft_split(line, '\n');
	if (line)
		free(line);
	if (copy_line)
		free(copy_line);
	if (!cub->map)
		ft_error(cub, MALLOC_ERROR);
	ft_check_map_chars(cub);
	ft_fill_map_with_spaces(cub);
	ft_check_walls(cub);
}
