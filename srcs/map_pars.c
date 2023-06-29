/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <tbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:25:42 by khovakim          #+#    #+#             */
/*   Updated: 2023/06/27 15:11:20 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t	max_len(char **matrix)
{
	size_t	l;
	size_t	len;

	l = 0;
	len = matrix_strlen(matrix[0]);
	while (matrix[++l])
	{
		if (len < matrix_strlen(matrix[l]))
			len = matrix_strlen(matrix[l]);
	}
	return (len);
}

void	ft_tab_to_space(char **map, int i, int *k)
{
	map[i][*k] = ' ';
	map[i][++*k] = ' ';
	map[i][++*k] = ' ';
	map[i][++*k] = ' ';
}

void	pars_map(t_map *map, char **line)
{
	int		i;
	int		j;
	int		k;

	i = 5;
	map->map = malloc(sizeof(char *) * (ft_matrix_size(line) - 5));
	while (line[++i])
		map->map[i - 6] = malloc(sizeof(char) * (max_len(line + 6) + 1));
	i = 5;
	while (line[++i])
	{
		j = -1;
		k = 0;
		while (line[i][++j])
		{
			if (line[i][j] == '\t')
				ft_tab_to_space(map->map, i - 6, &k);
			else
				map->map[i - 6][k] = line[i][j];
			++k;
		}
		map->map[i - 6][k] = '\0';
	}
	map->map[i - 6] = NULL;
}
