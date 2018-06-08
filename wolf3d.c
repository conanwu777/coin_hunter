/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 19:42:06 by cwu               #+#    #+#             */
/*   Updated: 2018/05/29 23:09:47 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	find_start_and_coins(t_vars *vp)
{
	int x;
	int y;

	vp->coins_left = 0;
	y = 0;
	while (y < vp->msz.y)
	{
		x = 0;
		while (x < vp->msz.x)
		{
			if (vp->map[y][x] == 'x')
			{
				vp->pos.fx = x + 0.45f;
				vp->pos.fy = y + 0.45f;
			}
			if (vp->map[y][x] == '*')
				vp->coins_left++;
			x++;
		}
		y++;
	}
}

void	redraw(t_vars *vp)
{
	pthread_t	id[4];
	t_input		in[4];
	int			c;

	init_3d(vp);
	map_to_2d(vp);
	c = -1;
	while (++c < 4 && (in[c].vp = vp))
		pthread_create(&(id[(in[c].mod = c)]),
			NULL, &fill_sky, (void*)(&(in[c])));
	c = -1;
	while (++c < 4)
		pthread_join(id[c], NULL);
	c = -1;
	while (++c < 4 && (in[c].vp = vp))
		pthread_create(&(id[(in[c].mod = c)]),
			NULL, &fill_floor, (void*)(&(in[c])));
	c = -1;
	while (++c < 4)
		pthread_join(id[c], NULL);
	fill_walls(vp);
	vp->cool ? put_coin(vp) : 1;
}

int		read_map(char *file, t_vars *vp)
{
	int		count;
	int		fd;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		return (0);
	}
	ft_gnl(fd, &line);
	vp->msz.x = ft_atoi(line);
	free(line);
	ft_gnl(fd, &line);
	vp->msz.y = ft_atoi(line);
	free(line);
	vp->map = (char**)malloc(sizeof(char*) * vp->msz.y);
	while (count < vp->msz.y)
	{
		ft_gnl(fd, &vp->map[vp->msz.y - 1 - count]);
		count++;
	}
	find_start_and_coins(vp);
	return (1);
}
