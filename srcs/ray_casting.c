/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khovakim <khovakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:26:01 by khovakim          #+#    #+#             */
/*   Updated: 2023/06/29 14:57:22 by khovakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	vertical_dist_check(t_game *game, t_ray *ray, char c)
{
	game->dist = calc_dist(ray);
	game->zeros = ray->zeros;
	if (c == 'D')
		game->zeros = 6;
	ray->depth = game->map_width;
}

void	vertical_lines_2(t_game *game, t_ray *ray)
{
	int		mx;
	int		my;
	char	val;

	while (ray->depth < game->map_width)
	{
		mx = (int)ray->rx >> 6;
		my = (int)ray->ry >> 6;
		val = get_map_sym(mx, my, game);
		if (val == '1' || val == 'D')
			vertical_dist_check(game, ray, val);
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->depth += 1;
		}
	}
	ray->vx = ray->rx;
	ray->vy = ray->ry;
}

void	vertical_lines(t_game *game, t_ray *ray)
{
	ray->tan_ra = tan(degree_to_radian(ray->ra));
	ray->depth = 0;
	if (cos(degree_to_radian(ray->ra)) > 0.0001)
	{
		ray->zeros = 5;
		ray->rx = (((int)ray->px >> 6) << 6) + 64;
		ray->ry = (ray->px - ray->rx) * ray->tan_ra + ray->py;
		ray->xo = 64;
		ray->yo = -64 * ray->tan_ra;
	}
	else if (cos(degree_to_radian(ray->ra)) < -0.0001)
	{
		ray->zeros = 4;
		ray->rx = (((int)ray->px >> 6) << 6) - 0.0001;
		ray->ry = (ray->px - ray->rx) * ray->tan_ra + ray->py;
		ray->xo = -64;
		ray->yo = 64 * ray->tan_ra;
	}
	else if (cos(degree_to_radian(ray->ra)) == 0)
	{
		ray->depth = game->map_width;
		ray->rx = ray->px;
		ray->ry = ray->py;
	}
	vertical_lines_2(game, ray);
}

void	ft_raycasting(t_game *game)
{
	t_ray	*ray;
	int		i;

	i = 0;
	ray = (t_ray *)malloc(sizeof(t_ray));
	ray->ra = replace_angle_360(game->pa + 30);
	ray->px = game->player->posx * 64;
	ray->py = game->player->posy * 64;
	while (i < WIN_WIDTH)
	{
		game->dist = 1000000;
		vertical_lines(game, ray);
		ray->depth = 0;
		horizontal_lines(game, ray);
		game->dist = game->dist * cos(degree_to_radian
				(replace_angle_360(game->pa - ray->ra)));
		if (game->zeros > 3 && game->zeros != 6)
			game->ray = (int)(ray->vy) % 64;
		else
			game->ray = (int)(ray->rx) % 64;
		draw_line(game, i);
		ray->ra = replace_angle_360(ray->ra - game->angle);
		i++;
	}
	free(ray);
}

void	map_rendering(t_game *game)
{
	if (game->img->img)
		mlx_destroy_image(game->mlx, game->img->img);
	game->img->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img->img)
	{
		write(2, "Error:\nImage couldn't be created!\n", 35);
		game_end(game);
	}
	game->img->addr[1] = mlx_get_data_addr(game->img->img,
			&game->img->bits_per_px[1],
			&game->img->size_len[1], &game->img->endian[1]);
	ft_raycasting(game);
	mlx_put_image_to_window(game->mlx, game->mlx_window, game->img->img, 0, 0);
}
