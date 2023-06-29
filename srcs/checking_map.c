/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <tbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:24:07 by khovakim          #+#    #+#             */
/*   Updated: 2023/06/27 15:11:20 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_change_position(t_map *map, int i, int j)
{
	map->px = i + 0.5;
	map->py = j + 0.5;
	map->player = map->map[j][i];
	map->map[j][i] = '0';
}

int	check_map(char **map)
{
	int		i;
	int		j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				if ((!map[i - 1][j] || !ft_strchr(EXCHARS, map[i - 1][j]))
					|| (!map[i][j - 1] || !ft_strchr(EXCHARS, map[i][j - 1]))
					|| (!map[i][j + 1] || !ft_strchr(EXCHARS, map[i][j + 1]))
					|| (!map[i + 1] || !map[i + 1][j]
					|| !ft_strchr(EXCHARS, map[i + 1][j])))
				{
					write(2, "Wrong map\n", 10);
					return (1);
				}
			}
		}
	}
	return (0);
}

int	check_map2(t_map *map)
{
	int		i;
	int		j;

	j = -1;
	while (map->map[++j])
	{
		i = -1;
		while (map->map[j][++i])
		{
			if (!ft_strchr(ALLCHARS, map->map[j][i]))
			{
				write(2, "Wrong symbols in map\n", 21);
				return (1);
			}
			else if (ft_strchr("NSWE", map->map[j][i]))
				ft_change_position(map, i, j);
			if (map->map_width <= i)
				map->map_width = i + 1;
		}
		map->map_height = j + 1;
	}
	return (0);
}
