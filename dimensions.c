/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimensions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 19:46:59 by cwu               #+#    #+#             */
/*   Updated: 2018/05/27 19:47:01 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	malloc_3d(t_vars *vp)
{
	t_pt point;

	vp->p3d = (t_3dp**)malloc(sizeof(t_3dp*) * H);
	point.y = -1;
	while (++point.y < H)
		vp->p3d[point.y] = (t_3dp*)malloc(sizeof(t_3dp) * W);
}

void	init_3d(t_vars *vp)
{
	t_pt point;

	point.y = -1;
	while (++point.y < H)
	{
		point.x = -1;
		while (++point.x < W)
			(vp->p3d[point.y][point.x]).d = MAX_DEPTH;
	}
}

t_pt	projection(t_pt pt, float h, t_vars *vp)
{
	t_pt	res;

	res.fx = (pt.fx - vp->pos.fx) * cos(vp->theta) -
	(pt.fy - vp->pos.fy) * sin(vp->theta);
	res.fy = (pt.fx - vp->pos.fx) * sin(vp->theta) +
	(pt.fy - vp->pos.fy) * cos(vp->theta);
	res.fz = h;
	res.x = (int)(W / 2 + vp->tmp.x * res.fx / (res.fy ? res.fy : 0.01));
	res.y = (int)(H / 2 + vp->tmp.y * res.fz / (res.fy ? res.fy : 0.01));
	return (res);
}

void	malloc_fp(t_vars *vp)
{
	t_pt c;

	c.y = -1;
	vp->fp = (t_pt**)malloc(sizeof(t_pt*) * vp->msz.y);
	while (++c.y < vp->msz.y)
		vp->fp[c.y] = (t_pt*)malloc(sizeof(t_pt) * vp->msz.x);
}

void	map_to_2d(t_vars *vp)
{
	t_pt c;

	c.y = -1;
	while (++c.y < vp->msz.y)
	{
		c.x = -1;
		while (++c.x < vp->msz.x)
		{
			vp->fp[c.y][c.x].fx = (c.x - vp->pos.fx) * cos(vp->theta)
			- (c.y - vp->pos.fy) * sin(vp->theta);
			vp->fp[c.y][c.x].fy = (c.y - vp->pos.fy) * cos(vp->theta)
			+ (c.x - vp->pos.fx) * sin(vp->theta);
			vp->fp[c.y][c.x].c = vp->map[c.y][c.x];
		}
	}
}
