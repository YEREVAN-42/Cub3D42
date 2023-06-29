/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <tbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:25:54 by khovakim          #+#    #+#             */
/*   Updated: 2023/06/27 15:11:20 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_map_format(char *text)
{
	if (ft_strncmp(text + (ft_strlen(text) - 4), ".cub", 4))
	{
		write(2, "Wrong format for map\n", 21);
		exit(1);
	}
}

void	check_map_size(char **line)
{
	int	i;
	int	j;

	if (ft_matrix_size(line) < 9)
	{
		write(2, "Incomplete map\n", 15);
		free_arr(line);
		exit(1);
	}
	i = 5;
	while (line[++i])
	{
		j = -1;
		while (line[i][++j])
		{
			if (line[i][j] != 'N' && line[i][j] != 'S' && line[i][j] != 'W'
			&& line[i][j] != 'E' && line[i][j] != '0' && line[i][j] != '1'
			&& line[i][j] != ' ' && line[i][j] != '\t')
			{
				write(2, "Wrong map\n", 13);
				free_arr(line);
				exit(1);
			}
		}
	}
}

void	parsing(t_map *map, char *text)
{
	char	**line;

	check_map_format(text);
	line = ft_read_map(text);
	check_map_size(line);
	check_nswe(line);
	check_commas(line);
	map->texture = malloc(sizeof(t_texture));
	pars_rgb(map->texture, line);
	if (pars_nswe(map->texture, line) || check_patf_format(map->texture))
	{
		free_all(map);
		free_arr(line);
		exit (1);
	}
	pars_map(map, line);
	if (check_map(map->map) || check_map2(map))
	{
		free_all(map);
		free_arr(line);
		exit (1);
	}
	free_arr(line);
	line = NULL;
}
