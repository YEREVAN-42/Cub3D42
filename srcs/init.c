/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <tbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:25:21 by khovakim          #+#    #+#             */
/*   Updated: 2023/06/27 15:11:20 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	map_to_list(t_game *game)
{
	t_list	*node;
	int		i;

	i = 0;
	game->mapp = NULL;
	while (game->map->map[i])
	{
		node = malloc(sizeof(t_list));
		node->content = game->map->map[i];
		node->next = NULL;
		ft_lstadd_back(&game->mapp, node);
		i++;
	}
}

void	init_struct_2(t_game *game)
{
	game->player->posx = game->map->px;
	game->player->posy = game->map->py;
	game->map_width = game->map->map_width;
	game->map_height = game->map->map_height;
	game->minimap = NULL;
	game->angle = 60.0 / WIN_WIDTH;
	game->minimap_x = 0;
	game->minimap_y = 0;
	map_to_list(game);
}

void	init_struct(t_game *game)
{
	int	arr_cnt;

	game->img = malloc(sizeof(t_img));
	game->player = malloc(sizeof(t_player));
	if (!(game->img) || !(game->player))
		exit(1);
	game->mlx = NULL;
	game->mlx_window = NULL;
	game->pa = 0;
	game->player->diry = 0;
	game->player->dirx = 0;
	arr_cnt = -1;
	game->img->img = NULL;
	while (++arr_cnt < 6)
		game->img->addr[arr_cnt] = NULL;
	init_struct_2(game);
}
