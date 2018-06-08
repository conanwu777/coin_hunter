/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 02:17:11 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/05/30 02:17:12 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <pthread.h>
# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include "libft/ft_printf.h"

# define PIX mlx_pixel_put
# define STR mlx_string_put
# define W 900
# define H 900
# define TEX_NUM 20
# define IMG 400
# define PI 3.1415926
# define MAX_DEPTH 100000

typedef struct		s_pt
{
	int				x;
	int				y;
	float			fx;
	float			fy;
	float			fz;
	char			c;
}					t_pt;

typedef struct		s_3dp
{
	unsigned int	color;
	float			d;
}					t_3dp;

typedef struct		s_vars
{
	char			**tex;
	void			*mlx;
	void			*win;
	void			*img;
	char			*str;
	float			mv;
	char			**map;
	t_pt			**fp;
	t_pt			msz;
	t_pt			tmp;
	t_pt			pos;
	t_3dp			**p3d;
	float			theta;
	int				coins_left;
	unsigned char	cool;
	unsigned char	sc;
	unsigned char	lvl_left;
}					t_vars;

typedef	struct		s_input
{
	t_vars			*vp;
	int				mod;
}					t_input;

typedef	struct		s_wall_in
{
	t_vars			*vp;
	int				mod;
	t_pt			pt;
	int				tex;
	int				orientation;
}					t_wall_in;

t_pt				rotate(t_pt p, float theta);
t_pt				move(t_pt p, t_pt move);
void				check_for_coin(t_vars *vp);
void				put_coin(t_vars *vp);
void				malloc_3d(t_vars *vp);
void				init_3d(t_vars *vp);
t_pt				projection(t_pt pt, float h, t_vars *vp);
void				thread_3d(t_vars *vp);
void				*project_3d(void *ptr);
void				map_to_2d(t_vars *vp);
void				*fill_sky(void *ptr);
void				*fill_floor(void *ptr);
void				fill_walls(t_vars *vp);
int					k_control(int key, t_vars *vp);
int					k_manager(int key, void *addr);
int					quit(t_vars *vp);
void				redraw(t_vars *vp);
void				malloc_fp(t_vars *vp);
void				start_thread_wall(t_vars *vp, t_pt pt, int tex,
					int orienation);
void				wall_loop_inner(t_pt *point, int *c, float t,
					t_wall_in *w);
void				check_wall(t_vars *vp, t_pt p, char c, int num);
void				*fill_wall(void *ptr);
int					read_map(char *file, t_vars *vp);
void				redraw(t_vars *vp);
void				find_start_and_coins(t_vars *vp);
void				load_level(t_vars *vp);
void				draw_image(t_vars *vp, int img);
int					is_wall(char c);
void				free_arrs(t_vars *vp);

#endif
