/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 19:44:27 by cwu               #+#    #+#             */
/*   Updated: 2018/05/27 19:44:28 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_pt	check_for_wall(t_vars *vp, float angle)
{
	t_pt goal;

	goal.fx = vp->pos.fx + sin(angle) * 0.1f;
	goal.fy = vp->pos.fy + cos(angle) * 0.1f;
	goal.x = floor(goal.fx);
	goal.y = floor(goal.fy);
	if (0 <= goal.y && goal.y < vp->msz.y &&
	0 <= (int)(vp->pos.fx - 0.01) && (int)(vp->pos.fx + 0.01) < vp->msz.x
	&& is_wall(vp->map[goal.y][(int)(vp->pos.fx - 0.01)])
	&& is_wall(vp->map[goal.y][(int)(vp->pos.fx + 0.01)]))
		goal.fy = round(vp->pos.fy);
	if (0 <= goal.x && goal.x < vp->msz.x &&
	0 <= (int)(vp->pos.fy - 0.01) && (int)(vp->pos.fy + 0.01) < vp->msz.y
	&& is_wall(vp->map[(int)(vp->pos.fy - 0.01)][goal.x])
	&& is_wall(vp->map[(int)(vp->pos.fy + 0.01)][goal.x]))
		goal.fx = round(vp->pos.fx);
	return (goal);
}

int		k_manager(int key, void *ptr)
{
	t_vars *vp;

	vp = (t_vars*)ptr;
	if (vp->sc == 0)
	{
		k_control(key, vp);
	}
	else
	{
		if (key == 53)
			quit(vp);
		if (key == 36 || key == 49)
		{
			if (vp->lvl_left == 0)
			{
				mlx_destroy_image(vp->mlx, vp->img);
				exit(1);
			}
			redraw(vp);
			thread_3d(vp);
			vp->sc = 0;
		}
	}
	return (0);
}

int		k_control(int key, t_vars *vp)
{
	if (key == 53)
		quit(vp);
	if (key == 27)
		vp->tmp.x -= (vp->tmp.x >= 5 ? 5 : 0);
	if (key == 24)
		vp->tmp.x += 5;
	if (key == 33)
		vp->tmp.y -= (vp->tmp.y >= 5 ? 5 : 0);
	if (key == 30)
		vp->tmp.y += 5;
	if (key == 126 || key == 125)
	{
		vp->pos = check_for_wall(vp, vp->theta + (key == 126 ? 0 : PI));
		check_for_coin(vp);
	}
	if (key == 124 || key == 123)
		vp->theta += (key == 124 ? PI / 100.0f : -PI / 100.0f);
	if (vp->sc == 0)
	{
		redraw(vp);
		thread_3d(vp);
	}
	return (1);
}

int		quit(t_vars *vp)
{
	t_pt point;

	point.y = -1;
	while (++point.y < H)
		free(vp->p3d[point.y]);
	free(vp->p3d);
	mlx_destroy_image(vp->mlx, vp->img);
	exit(1);
}
