/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:02:08 by gbeaudoi          #+#    #+#             */
/*   Updated: 2024/11/12 18:16:19 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/ft_printf.h"
# include "../libft/include/ft_printferr.h"
# include "../libft/include/get_next_line_bonus.h"
# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MALLOC_ERROR "Detected: Malloc error\n"
# define COLOR_ERROR "Detected: Color format issue"
# define SCREEN_W 1280
# define SCREEN_H 720
# define X 0
# define Y 1
# define IMG_SIZE 64
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define P_SPEED 0.03
# define R_SPEED 0.04

typedef struct s_img
{
	void	*mlx_img;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		img_width;
	int		img_height;
}			t_img;

typedef struct s_vec
{
	double	pos[2];
	double	dir[2];
	double	plane[2];
	double	camera[2];
	double	ray_dir[2];
	double	side_dist[2];
	double	dd[2];
	int		coordinate[2];
	int		step[2];
	int		tex[2];
	int		move[2];
	int		rotate;
	int		moved;
	int		hori_line;
	int		draw_start;
	int		draw_end;
	int		hit;
	int		side;
	double	dist_to_wall;
	int		texture_value;
	double	wallx;
	double	texture_mov;
	double	texture_pos;
	int		color;
	int		y;
}			t_vec;

typedef struct s_cub
{
	char	**map;
	size_t	height;
	size_t	width;
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*ceiling;
	char	*floor;
	int		info;
	int		f_color;
	int		c_color;
	int		tabf[3];
	int		tabc[3];
	t_vec	*vec;
	void	*mlx;
	void	*win;
	t_img	*img;
	int		**texture;
}			t_cub;

// PARSING
char		*ft_str_join_free_both(char *s1, char *s2);
void		ft_parse_file(t_cub *cub, int fd);
void		ft_check_map_chars(t_cub *cub);
void		ft_check_walls(t_cub *cub);
void		ft_get_map(t_cub *cub, int fd, char *line);
void		ft_fill_map_with_spaces(t_cub *cub);
int			ft_check_color_helper(char **rgb, int i, t_cub *cub, char type);

// UTILS
char		*ft_strdup_free(char *s, char *info);
int			ft_rgb(char *str);
int			ft_translate_color(int *rgb);
int			ft_find_tab_size(char **tab_str);

// INIT
void		ft_init_mlx_and_vec(t_cub *cub);
void		ft_init_texture(t_cub *cub);
void		ft_raycasting(t_cub *cub, int i);
void		ft_init_img(t_img *img);

int			ft_display_moves(t_cub *cub);

// MLX
int			ft_handle_keypress(int keysym, t_cub *cub);
int			ft_handle_keyrelease(int key, t_cub *cub);
void		ft_load_xpm(t_cub *cub, t_img *img, char *tex);

// ERROR
void		ft_error(t_cub *cub, char *err_msg);
void		ft_destroy_mlx(t_cub *cub);
int			ft_destroy(t_cub *cub);

// MOVE
int			ft_x_move(t_cub *cub, t_vec *vec, int leftorright);
int			ft_y_move(t_cub *cub, t_vec *vec, int upordown);
int			ft_l_rotate(t_vec *vec);
int			ft_r_rotate(t_vec *vec);
int			ft_moving(t_cub *cub, t_vec *vec);

// RAYCASTING
void		ft_ray_pos(t_vec *vec, int x);
void		ft_side_dist(t_vec *vec);
void		ft_dda(t_cub *cub, t_vec *vec);
void		ft_start_draw(t_vec *vec);
void		ft_draw(t_cub *cub, t_vec *vec, int x, int **buffer);

#endif