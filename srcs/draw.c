/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khovakim <khovakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:24:13 by khovakim          #+#    #+#             */
/*   Updated: 2023/06/29 14:56:27 by khovakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int clr)
{
	char	*dst;

	dst = game->img->addr[1] + ((y * game->img->size_len[1]) + x
			* (game->img->bits_per_px[1] / 8));
	*(unsigned int *)dst = clr;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	put_texture_pixel(t_game *game, int x, int y, int k)
{
	char	*dst;
	int		i;
	int		j;

	if (game->linelen == 0)
		return ;
	i = game->ray;
	k = k + game->stepy;
	j = (k << 6) / game->linelen;
	dst = game->img->addr[game->zeros] + ((j * game->img->size_len[game->zeros])
			+ i * (game->img->bits_per_px[game->zeros] / 8));
	my_mlx_pixel_put(game, x, y, *(unsigned int *)dst);
}

void	draw_line_2(t_game *game, int i, int lineh, int lineoff)
{
	int	k;
	int	y;

	k = -1;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y < lineoff)
			my_mlx_pixel_put(game, i, y,
				create_trgb(0, game->map->texture->ceiling->r,
					game->map->texture->ceiling->g,
					game->map->texture->ceiling->b));
		else if (y > lineh + lineoff)
			my_mlx_pixel_put(game, i, y,
				create_trgb(0, game->map->texture->floor->r,
					game->map->texture->floor->g,
					game->map->texture->floor->b));
		else
			put_texture_pixel(game, i, y, k++);
		y++;
	}
}

void	draw_line(t_game *game, int i)
{
	int	lineh;
	int	lineoff;

	lineh = (WIN_HEIGHT << 5) / game->dist;
	game->stepy = 0;
	game->linelen = lineh;
	if (lineh > WIN_HEIGHT)
	{
		game->stepy = ((lineh - WIN_HEIGHT) >> 1);
		lineh = WIN_HEIGHT;
	}
	lineoff = (WIN_HEIGHT - lineh) >> 1;
	draw_line_2(game, i, lineh, lineoff);
}
