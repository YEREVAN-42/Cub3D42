/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <tbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:24:02 by khovakim          #+#    #+#             */
/*   Updated: 2023/06/27 15:11:20 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_player(char **line)
{
	int		i;
	int		l;
	int		count;

	l = 5;
	count = 0;
	while (line[++l])
	{
		i = -1;
		while (line[l][++i])
		{
			if (line[l][i] == 'N' || line[l][i] == 'S'
				|| line[l][i] == 'W' || line[l][i] == 'E')
				++count;
		}
	}
	if (count != 1)
	{
		if (count == 0)
			write(2, "No player in map\n", 17);
		else
			write(2, "More than 1 player\n", 20);
		return (1);
	}
	return (0);
}

void	check_nswe(char **line)
{
	int	i;
	int	j;

	j = 0;
	if (check_player(line))
		exit(1);
	while (line[j] && j < 6)
	{
		i = 0;
		while (line[j][i] && (line[j][i] == '\t' || line[j][i] == 32))
			++i;
		if (ft_strncmp(line[j] + i, "NO", 2) && ft_strncmp(line[j] + i, "SO", 2)
			&& ft_strncmp(line[j] + i, "WE", 2)
			&& ft_strncmp(line[j] + i, "EA", 2)
			&& ft_strncmp(line[j] + i, "F", 1)
			&& ft_strncmp(line[j] + i, "C", 1))
		{
			write(2, "Incomplete map\n", 15);
			exit(1);
		}
		++j;
	}
}

void	check_commas(char **line)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	j = -1;
	while (line[++j] && j < 6)
	{
		i = 0;
		while (line[j][i] && (line[j][i] == '\t' || line[j][i] == 32))
			++i;
		if (!ft_strncmp(line[j] + i, "F", 1)
			|| !ft_strncmp(line[j] + i, "C", 1))
		{
			while (line[j][i])
				if (line[j][i++] == ',')
					++count;
		}
	}
	if (count != 4)
	{
		write(2, "Incorrect count of commas\n", 26);
		exit(1);
	}
}
