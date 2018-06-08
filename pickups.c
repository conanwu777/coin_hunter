/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 03:25:07 by cwu               #+#    #+#             */
/*   Updated: 2018/06/01 03:25:10 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	check_for_coin(t_vars *vp)
{
	t_pt goal;

	goal.fx = vp->pos.fx;
	goal.fy = vp->pos.fy;
	goal.x = floor(goal.fx);
	goal.y = floor(goal.fy);
	if (0 <= goal.y && goal.y < vp->msz.y &&
	0 <= goal.x && goal.x < vp->msz.x &&
	vp->map[goal.y][goal.x] == '*')
	{
		vp->map[goal.y][goal.x] = '0';
		vp->fp[goal.y][goal.x].c = '0';
		vp->coins_left--;
		if (vp->cool == 1 && vp->coins_left == 0)
		{
			load_level(vp);
		}
	}
}

void	draw_coin(t_vars *vp, t_pt p)
{
	t_pt	count;
	t_pt	scp;
	t_pt	t;
	int		c;
	float	d;

	count.y = -1;
	scp = projection(p, 0, vp);
	d = (vp->fp[p.y][p.x].fy + vp->fp[p.y + 1][p.x + 1].fy) / 2;
	while (++count.y < (int)(vp->tmp.y / d) && (count.x = -1) == -1)
		while (++count.x < (int)(vp->tmp.y / d))
		{
			t.x = scp.x + count.x - (int)(vp->tmp.y / d / 2);
			t.y = scp.y + count.y - (int)(vp->tmp.y / d / 2);
			if (0 <= t.y && t.y < H && 0 <= t.x && t.x < W
				&& vp->p3d[t.y][t.x].d > d)
			{
				c = (int)((float)count.y / (int)(vp->tmp.y / d) * IMG) * IMG
				+ (int)((float)count.x / (int)(vp->tmp.y / d) * IMG);
				if (((unsigned char*)(vp->tex[12]))[4 * c + 3] != 255 &&
				(vp->p3d[t.y][t.x].d = vp->fp[p.y][p.x].fy) != -1)
					vp->p3d[t.y][t.x].color = ((unsigned int*)(vp->tex[12]))[c];
			}
		}
}

void	put_coin(t_vars *vp)
{
	t_pt p;

	p.y = -1;
	while (++p.y < vp->msz.y)
	{
		p.x = -1;
		while (++p.x < vp->msz.x)
			if (vp->fp[p.y][p.x].c == '*')
			{
				p.fx = (float)p.x + 0.5;
				p.fy = (float)p.y + 0.5;
				draw_coin(vp, p);
			}
	}
}

void	draw_image(t_vars *vp, int img)
{
	t_pt	c;
	int		c2;

	c.y = -1;
	while (++c.y < H)
	{
		c.x = -1;
		while (++c.x < W)
		{
			c2 = ((int)((float)c.y / H * IMG * 3) * IMG * 3 +
			(int)((float)c.x / W * IMG * 3));
			((unsigned int*)vp->str)[c.y * W + c.x] =
			((unsigned int*)vp->tex[img])[c2];
		}
	}
	mlx_put_image_to_window(vp->mlx, vp->win, vp->img, 0, 0);
}

void	load_level(t_vars *vp)
{
	char	buf[16];

	vp->sc = 1;
	vp->lvl_left--;
	if (vp->lvl_left == 0)
		draw_image(vp, 15);
	else
		draw_image(vp, 14);
	vp->theta = 0;
	sprintf(buf, "maps/cool_map%d", vp->lvl_left - 1);
	free_arrs(vp);
	read_map(buf, vp);
	malloc_fp(vp);
}
