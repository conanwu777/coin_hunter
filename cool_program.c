/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cool_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 16:06:48 by cwu               #+#    #+#             */
/*   Updated: 2018/05/31 16:06:49 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	check_wall(t_vars *vp, t_pt p, char c, int num)
{
	t_pt np;
	t_pt proj1;
	t_pt proj2;

	np.fx = (c == 'v' ? p.fx : p.fx + 1);
	np.fy = (c == 'v' ? p.fy + 1 : p.fy);
	proj1 = projection(p, 0, vp);
	proj2 = projection(np, 0, vp);
	if ((proj1.x < 0 && proj2.x < 0) || (proj1.x > W && proj2.x > W) ||
		((0 <= proj1.x && proj1.x <= W && 0 <= proj1.y && proj1.y <= H &&
		0 <= proj2.x && proj2.x <= W && 0 <= proj2.y && proj2.y <= H &&
			vp->p3d[proj1.y][proj1.x].d < vp->fp[p.y][p.x].fy - 1
		&& vp->p3d[proj2.y][proj2.x].d <
		(c == 'v' ? vp->fp[p.y + 1][p.x].fy : vp->fp[p.y][p.x + 1].fy) - 1
		&& fabsf(vp->p3d[proj1.y][proj1.x].d
		- vp->p3d[proj2.y][proj2.x].d) < 2)))
		return ;
	if (c == 'v' && p.fx < vp->pos.fx)
		start_thread_wall(vp, p, num <= 3 ? (num - 1) * 3 + 2 : num + 6, 1);
	else if (c == 'v')
		start_thread_wall(vp, p, num <= 3 ? (num - 1) * 3 + 2 : num + 6, 1);
	else if (p.fy < vp->pos.fy)
		start_thread_wall(vp, p, num <= 3 ? (num - 1) * 3 + 1 : num + 6, 0);
	else
		start_thread_wall(vp, p, num <= 3 ? (num - 1) * 3 + 3 : num + 6, 0);
}

void	textures_2(t_vars *vp, int db)
{
	void	*img;

	img = mlx_xpm_file_to_image(vp->mlx, "textures/wall_3b.xpm", &db, &db);
	vp->tex[7] = mlx_get_data_addr(img, &db, &db, &db);
	img = mlx_xpm_file_to_image(vp->mlx, "textures/wall_3n.xpm", &db, &db);
	vp->tex[8] = mlx_get_data_addr(img, &db, &db, &db);
	img = mlx_xpm_file_to_image(vp->mlx, "textures/wall_3d.xpm", &db, &db);
	vp->tex[9] = mlx_get_data_addr(img, &db, &db, &db);
	img = mlx_xpm_file_to_image(vp->mlx, "textures/window.xpm", &db, &db);
	vp->tex[10] = mlx_get_data_addr(img, &db, &db, &db);
	img = mlx_xpm_file_to_image(vp->mlx, "textures/sky.xpm", &db, &db);
	vp->tex[11] = mlx_get_data_addr(img, &db, &db, &db);
	img = mlx_xpm_file_to_image(vp->mlx, "textures/coin.xpm", &db, &db);
	vp->tex[12] = mlx_get_data_addr(img, &db, &db, &db);
	img = mlx_xpm_file_to_image(vp->mlx, "textures/start_new.xpm", &db, &db);
	vp->tex[13] = mlx_get_data_addr(img, &db, &db, &db);
	img = mlx_xpm_file_to_image(vp->mlx, "textures/lvl_up.xpm", &db, &db);
	vp->tex[14] = mlx_get_data_addr(img, &db, &db, &db);
	img = mlx_xpm_file_to_image(vp->mlx, "textures/finish.xpm", &db, &db);
	vp->tex[15] = mlx_get_data_addr(img, &db, &db, &db);
}

void	textures(t_vars *vp)
{
	void	*img;
	int		db;

	vp->tex = (char**)malloc(sizeof(char*) * TEX_NUM);
	img = mlx_xpm_file_to_image(vp->mlx, "textures/floor.xpm", &db, &db);
	vp->tex[0] = mlx_get_data_addr(img, &db, &db, &db);
	img = mlx_xpm_file_to_image(vp->mlx, "textures/wall_1b.xpm", &db, &db);
	vp->tex[1] = mlx_get_data_addr(img, &db, &db, &db);
	img = mlx_xpm_file_to_image(vp->mlx, "textures/wall_1n.xpm", &db, &db);
	vp->tex[2] = mlx_get_data_addr(img, &db, &db, &db);
	img = mlx_xpm_file_to_image(vp->mlx, "textures/wall_1d.xpm", &db, &db);
	vp->tex[3] = mlx_get_data_addr(img, &db, &db, &db);
	img = mlx_xpm_file_to_image(vp->mlx, "textures/wall_2b.xpm", &db, &db);
	vp->tex[4] = mlx_get_data_addr(img, &db, &db, &db);
	img = mlx_xpm_file_to_image(vp->mlx, "textures/wall_2n.xpm", &db, &db);
	vp->tex[5] = mlx_get_data_addr(img, &db, &db, &db);
	img = mlx_xpm_file_to_image(vp->mlx, "textures/wall_2d.xpm", &db, &db);
	vp->tex[6] = mlx_get_data_addr(img, &db, &db, &db);
	textures_2(vp, db);
}

int		main(void)
{
	t_vars	vars;
	char	buf[16];
	int		db;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, W, H, "Wolf3D");
	vars.img = mlx_new_image(vars.mlx, W, H);
	vars.str = mlx_get_data_addr(vars.img, &db, &db, &db);
	textures(&vars);
	vars.lvl_left = 3;
	sprintf(buf, "maps/cool_map%d", vars.lvl_left - 1);
	read_map(buf, &vars);
	vars.tmp.x = 500;
	vars.tmp.y = 250;
	vars.theta = 0;
	vars.sc = 1;
	vars.cool = 1;
	malloc_fp(&vars);
	malloc_3d(&vars);
	thread_3d(&vars);
	mlx_hook(vars.win, 2, 0, &k_manager, (void*)(&vars));
	mlx_hook(vars.win, 17, 1L << 17, quit, (void*)(&vars));
	draw_image(&vars, 13);
	mlx_loop(vars.mlx);
	return (0);
}
