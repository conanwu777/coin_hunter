/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 02:32:33 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/05/30 02:32:35 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	free_arrs(t_vars *vp)
{
	int count;

	count = 0;
	while (count < vp->msz.y)
	{
		free(vp->map[count]);
		free(vp->fp[count]);
		count++;
	}
	free(vp->fp);
	free(vp->map);
}

t_pt	rotate(t_pt p, float theta)
{
	t_pt res;

	res.fx = p.fx * cos(theta) - p.fy * sin(theta);
	res.fy = p.fx * sin(theta) + p.fy * cos(theta);
	return (res);
}

t_pt	move(t_pt p, t_pt move)
{
	p.fx += move.fx;
	p.fy += move.fy;
	return (p);
}

void	thread_3d(t_vars *vp)
{
	pthread_t	id[4];
	t_input		in[4];
	int			c;
	char		buf[17];

	c = -1;
	while (++c < 4 && (in[c].vp = vp))
	{
		in[c].mod = c;
		pthread_create(&(id[c]), NULL, &project_3d, (void*)(&(in[c])));
	}
	c = -1;
	while (++c < 4)
		pthread_join(id[c], NULL);
	mlx_put_image_to_window(vp->mlx, vp->win, vp->img, 0, 0);
	if (vp->cool)
	{
		sprintf(buf, "Coins Left : %2d", vp->coins_left);
		mlx_string_put(vp->mlx, vp->win, 20, 20, 200000, buf);
	}
}

void	*project_3d(void *ptr)
{
	t_pt	sc;
	int		pix;
	t_vars	*vp;
	int		mod;

	vp = ((t_input*)ptr)->vp;
	mod = ((t_input*)ptr)->mod;
	sc.y = mod;
	while (sc.y < H)
	{
		sc.x = -1;
		while (++sc.x < W)
			if (vp->p3d[sc.y][sc.x].d != MAX_DEPTH)
			{
				pix = sc.x + sc.y * W;
				((unsigned int*)vp->str)[pix] = vp->p3d[sc.y][sc.x].color;
			}
		sc.y += 4;
	}
	return (NULL);
}
