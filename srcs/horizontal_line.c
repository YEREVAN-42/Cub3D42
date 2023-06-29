/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <tbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:25:16 by khovakim          #+#    #+#             */
/*   Updated: 2023/06/27 15:11:20 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	get_map_sym(int mx, int my, t_game *game)
{
	t_list	*map;
	char	*s;

	if (mx < 0 || my < 0 || mx >= game->map_width || my >= game->map_height)
		return (' ');
	map = game->mapp;
	while (my > 0)
	{
		my--;
		map = map->next;
	}
	s = map->content;
	return (s[mx]);
}

void	horizontal_dist_check(t_game *game, t_ray *ray, char c)
{
	double	disth;

	disth = calc_dist(ray);
	if (disth < game->dist)
	{
		game->zeros = ray->zerosh;
		if (c == 'D')
			game->zeros = 6;
		game->dist = disth;
	}
	else
	{
		ray->rx = ray->vx;
		ray->ry = ray->vy;
	}
	ray->depth = game->map_height;
}

void	horizontal_lines_2(t_game *game, t_ray *ray)
{
	int		mx;
	int		my;
	char	c;

	while (ray->depth < game->map_height)
	{	
		mx = (int)ray->rx >> 6;
		my = (int)ray->ry >> 6;
		c = get_map_sym(mx, my, game);
		if (c == '1' || c == 'D')
		{
			horizontal_dist_check(game, ray, c);
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->depth += 1;
		}
	}
}

void	horizontal_lines(t_game *game, t_ray *ray)
{
	ray->atan_ra = 1.0 / tan(degree_to_radian(ray->ra));
	if (sin(degree_to_radian(ray->ra)) > 0.0001)
	{
		ray->zerosh = 2;
		ray->ry = (((int)ray->py >> 6) << 6) - 0.0001;
		ray->rx = (ray->py - ray->ry) * ray->atan_ra + ray->px;
		ray->yo = -64;
		ray->xo = 64 * ray->atan_ra;
	}
	else if (sin(degree_to_radian(ray->ra)) < -0.0001)
	{
		ray->zerosh = 3;
		ray->ry = (((int)ray->py >> 6) << 6) + 64;
		ray->rx = (ray->py - ray->ry) * ray->atan_ra + ray->px;
		ray->yo = 64;
		ray->xo = -64 * ray->atan_ra;
	}
	else if (sin(degree_to_radian(ray->ra)) < 0.0001
		&& sin(degree_to_radian(ray->ra)) > -0.0001)
	{
		ray->depth = game->map_height;
		ray->rx = ray->px;
		ray->ry = ray->py;
	}
	horizontal_lines_2(game, ray);
}
