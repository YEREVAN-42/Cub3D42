/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <tbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:26:14 by khovakim          #+#    #+#             */
/*   Updated: 2023/06/27 15:11:20 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_is_byte_range(char **line)
{
	unsigned long long	r;
	unsigned long long	g;
	unsigned long long	b;

	if (line[0] && line[1] && line[2])
	{
		r = ft_atoi(line[0]);
		g = ft_atoi(line[1]);
		b = ft_atoi(line[2]);
	}
	else
		return (2);
	if (!(r >= 0 && r <= 255) || !(g >= 0 && g <= 255) || !(b >= 0 && b <= 255))
		return (2);
	return (0);
}

int	ft_is_only_digits(char **s)
{
	int		i;
	int		index;
	int		count;
	char	**line;

	index = 0;
	while (s && s[index])
	{
		count = 0;
		i = -1;
		line = ft_split_space(s[index]);
		while (line[++i])
			++count;
		if (count != 1)
		{
			free_arr(line);
			return (2);
		}
		free_arr(line);
		++index;
	}
	return (0);
}

int	check_rgb(char **f, char **c)
{
	if (!f || !c)
	{
		write(2, "RGB is not correct\n", 19);
		return (1);
	}
	if (ft_isdigit(f) || ft_isdigit(c))
	{
		free_arr(f);
		free_arr(c);
		write(2, "RGB is not numeric\n", 19);
		return (1);
	}
	if (ft_is_byte_range(f) || ft_is_byte_range(c) || ft_is_only_digits(f)
		|| ft_is_only_digits(c))
	{
		free_arr(f);
		free_arr(c);
		write(2, "RGB is not corresponding\n", 25);
		return (2);
	}
	return (0);
}

void	fill_rgb(t_texture *texture, char **f, char **c)
{
	texture->ceiling = (t_colors *)malloc(sizeof(t_colors));
	texture->floor = (t_colors *)malloc(sizeof(t_colors));
	texture->ceiling->r = ft_atoi(c[0]);
	texture->ceiling->g = ft_atoi(c[1]);
	texture->ceiling->b = ft_atoi(c[2]);
	texture->floor->r = ft_atoi(f[0]);
	texture->floor->g = ft_atoi(f[1]);
	texture->floor->b = ft_atoi(f[2]);
	free_arr(f);
	free_arr(c);
}

void	pars_rgb(t_texture *texture, char **line)
{
	char	**f;
	char	**c;
	int		i;
	int		j;

	j = -1;
	f = NULL;
	c = NULL;
	while (line[++j])
	{
		i = 0;
		while (line[j][i] && (line[j][i] == '\t' || line[j][i] == 32))
			++i;
		if (ft_strncmp(line[j] + i, "F", 1) == 0)
			f = ft_split(line[j] + i + 1, ',');
		else if (ft_strncmp(line[j] + i, "C", 1) == 0)
			c = ft_split(line[j] + i + 1, ',');
	}
	if (check_rgb(f, c))
	{
		free_arr(line);
		exit(1);
	}
	else
		fill_rgb(texture, f, c);
}
