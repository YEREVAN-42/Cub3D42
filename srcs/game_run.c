/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <tbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:24:45 by khovakim          #+#    #+#             */
/*   Updated: 2023/06/27 15:11:20 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	pixel_put(t_game *win, int x, int y, int color)
{
	char	*pixel;

	pixel = win->img->addr[1] + (y * win->img->size_len[0]
			+ x * (win->img->bits_per_px[0] / 8));
		*(unsigned int *)pixel = color;
}

void	draw_rect(t_game *game, int width, int color)
{
	int	end_x;
	int	end_y;

	end_x = game->minimap_x + width;
	end_y = game->minimap_y + width;
	while (game->minimap_y < end_y)
	{
		game->minimap_x = end_x - width;
		while (game->minimap_x < end_x)
		{
			pixel_put(game, game->minimap_x, game->minimap_y, color);
			game->minimap_x++;
		}
		game->minimap_y++;
	}
}

void	draw_player(t_game *game)
{
	game->minimap_x = game->player->posx * 10;
	game->minimap_y = game->player->posy * 10;
	draw_rect(game, 10, RED);
	mlx_put_image_to_window(game->mlx, game->mlx_window, game->minimap, 0, 0);
}

void	draw_minimap(t_game *game)
{
	int	j;
	int	i;

	i = -1;
	if (game->minimap)
		mlx_destroy_image(game->mlx, game->minimap);
	game->minimap = mlx_new_image(game->mlx,
			game->map_width * 10, game->map_height * 10);
	game->img->addr[1] = mlx_get_data_addr(game->minimap,
			&game->img->bits_per_px[0],
			&game->img->size_len[0], &game->img->endian[0]);
	while (++i < game->map_height)
	{
	j = -1;
		while (game->map->map[i][++j])
		{
			game->minimap_x = j * 10;
			game->minimap_y = i * 10;
			if (game->map->map[i][j] == '1')
				draw_rect(game, 10, BROWN);
			else if (game->map->map[i][j] == '0')
				draw_rect(game, 10, WHITE);
		}
	}
	draw_player(game);
}

int	start_game(t_game *game)
{
	map_rendering(game);
	draw_minimap(game);
	return (0);
}
