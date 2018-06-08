/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 02:32:16 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/05/30 02:32:23 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		is_wall(char c)
{
	if (c != '0' && c != '*' && c != 'x')
		return (c - '0');
	return (0);
}

void	*fill_wall(void *ptr)
{
	t_wall_in	*w;
	float		t;
	t_pt		p;
	int			c;
	int			n;

	w = (t_wall_in*)ptr;
	t = 0;
	n = 0;
	while (t < 1)
	{
		p.fx = (!w->orientation ?
			w->pt.fx + t - w->vp->pos.fx : w->pt.fx - w->vp->pos.fx);
		p.fy = (!w->orientation ?
			w->pt.fy - w->vp->pos.fy : w->pt.fy + t - w->vp->pos.fy);
		p = rotate(p, w->vp->theta);
		p.fz = -1;
		while (n % 4 == w->mod && p.fz < 1 && p.fy > 0.3f)
			wall_loop_inner(&p, &c, t, w);
		n++;
		t += (p.fy / W > 0.0005 ? p.fy / W : 0.0005);
	}
	return (NULL);
}

void	start_thread_wall(t_vars *vp, t_pt pt, int tex, int orienation)
{
	int			c;
	t_wall_in	in[4];
	pthread_t	id[4];

	c = -1;
	while (++c < 4)
	{
		in[c].tex = tex;
		in[c].pt = pt;
		in[c].vp = vp;
		in[c].mod = c;
		in[c].orientation = orienation;
		pthread_create(&(id[c]), NULL, fill_wall, (void*)(&(in[c])));
	}
	c = -1;
	while (++c < 4)
		pthread_join(id[c], NULL);
}

void	square_check(t_vars *vp, t_pt p, int size, t_pt c)
{
	t_pt a;

	a.y = p.y + c.y;
	a.x = p.x + c.x;
	a.fx = a.x + 0.5;
	a.fy = a.y + 0.5;
	if ((abs(c.x) == size || abs(c.y) == size) &&
		0 <= a.y && a.y < vp->msz.y && 0 <= a.x && a.x < vp->msz.x)
	{
		if (a.x < vp->msz.x - 1 && is_wall(vp->fp[a.y][a.x].c) &&
		is_wall(vp->fp[a.y][a.x + 1].c) &&
		(vp->fp[a.y][a.x].fy > -1 || vp->fp[a.y][a.x + 1].fy > -1))
			check_wall(vp, a, 'h', is_wall(vp->fp[a.y][a.x].c) ==
			is_wall(vp->fp[a.y][a.x + 1].c) ?
			is_wall(vp->fp[a.y][a.x].c) : 4 - vp->lvl_left);
		if (a.y < vp->msz.y - 1 && is_wall(vp->fp[a.y][a.x].c)
		&& is_wall(vp->fp[a.y + 1][a.x].c) &&
		(vp->fp[a.y][a.x].fy > -1 || vp->fp[a.y + 1][a.x].fy > -1))
			check_wall(vp, a, 'v', is_wall(vp->fp[a.y][a.x].c) ==
			is_wall(vp->fp[a.y + 1][a.x].c) ?
			is_wall(vp->fp[a.y][a.x].c) : 4 - vp->lvl_left);
	}
}

void	fill_walls(t_vars *vp)
{
	t_pt	c;
	t_pt	p;
	int		size;

	size = 0;
	p.x = floor(vp->pos.fx);
	p.y = floor(vp->pos.fy);
	while (p.x - size >= 0 || p.x + size < vp->msz.x
		|| p.y - size >= 0 || p.y + size < vp->msz.y)
	{
		c.y = -size - 1;
		while (++c.y <= size)
		{
			c.x = -size - 1;
			while (++c.x <= size)
				square_check(vp, p, size, c);
		}
		size++;
	}
}
