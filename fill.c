/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 19:45:46 by cwu               #+#    #+#             */
/*   Updated: 2018/05/27 19:45:48 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	*fill_sky(void *ptr)
{
	t_pt	point;
	int		c;
	double	db;
	t_vars	*vp;
	int		mod;

	vp = ((t_input*)ptr)->vp;
	mod = ((t_input*)ptr)->mod;
	point.y = mod - 4;
	while ((point.y += 4) < H && (point.x = -1) == -1)
	{
		while (++point.x < W)
			if (vp->p3d[point.y][point.x].d == MAX_DEPTH)
			{
				c = ((int)((float)point.y / H * IMG * 3 + 1) * IMG * 3 +
(int)((modf((float)point.x / W + vp->theta * 2 / PI, &db)) * IMG * 3));
				if (vp->p3d[point.y][point.x].d == MAX_DEPTH)
				{
					vp->p3d[point.y][point.x].color =
					((unsigned int*)(vp->tex[vp->cool ? 11 : 5]))[c];
					vp->p3d[point.y][point.x].d = MAX_DEPTH - 1;
				}
			}
	}
	return (NULL);
}

void	finish_floor(int *c, t_pt grid, t_pt point, t_vars *vp)
{
	*c = ((int)((grid.fy - floor(grid.fy)) * IMG) * IMG
	+ (grid.fx - floor(grid.fx)) * IMG);
	vp->p3d[point.y][point.x].color = ((unsigned int*)
	(vp->tex[0]))[*c];
	vp->p3d[point.y][point.x].d = point.fy;
}

void	*fill_floor(void *ptr)
{
	t_pt	point;
	t_pt	grid;
	int		c;
	t_vars	*vp;
	int		mod;

	vp = ((t_input*)ptr)->vp;
	mod = ((t_input*)ptr)->mod;
	point.y = mod - 4;
	while ((point.y += 4) < H && (point.x = -1) == -1)
		while (++point.x < W)
		{
			point.fx = (float)(point.x - W / 2) / (point.y - H / 2 ?
			(float)point.y - H / 2 : 1) * vp->tmp.y / vp->tmp.x;
			point.fy = (float)vp->tmp.y / (point.y - H / 2 ?
			point.y - H / 2 : 1);
			grid = move(rotate(point, -vp->theta), vp->pos);
			if (grid.fx > 0 && grid.fx < vp->msz.x
				&& grid.fy > 0 && grid.fy < vp->msz.x && point.fy > 0)
				finish_floor(&c, grid, point, vp);
		}
	return (NULL);
}

void	wall_loop_inner(t_pt *point, int *c, float t, t_wall_in *w)
{
	point->x = (int)(W / 2 + w->vp->tmp.x * point->fx /
	(point->fy ? point->fy : 0.1));
	point->y = (int)(H / 2 + w->vp->tmp.y * point->fz /
	(point->fy ? point->fy : 0.1));
	if (0 < point->x && point->x < W && 0 < point->y && point->y < H
	&& w->vp->p3d[point->y][point->x].d > point->fy)
	{
		*c = ((int)((point->fz + 1) / 2 * IMG) * IMG + t * IMG);
		if (((unsigned char*)(w->vp->tex[w->tex]))[4 * (*c) + 3] != 255)
		{
			w->vp->p3d[point->y][point->x].color =
			((unsigned int*)(w->vp->tex[w->tex]))[*c];
			w->vp->p3d[point->y][point->x].d = point->fy;
		}
	}
	point->fz += (point->fy / H > 0.0015 ? point->fy / H : 0.0015);
}
