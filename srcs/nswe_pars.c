/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nswe_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <tbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:25:48 by khovakim          #+#    #+#             */
/*   Updated: 2023/06/27 15:11:20 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t	ft_matrix_size(char **matrix)
{
	size_t	size;

	size = 0;
	while (matrix && matrix[size])
		++size;
	return (size);
}

int	ft_pars_n(t_texture *texture, char **line, int l, char flag)
{
	char	**matrix;

	matrix = NULL;
	matrix = ft_split_space(line[l]);
	if (ft_matrix_size(matrix) != 2)
	{
		free_arr(matrix);
		matrix = NULL;
		write(2, "Incorrect path\n", 15);
		return (1);
	}
	else
	{
		if (flag == 'n')
			texture->no = ft_strdup(matrix[1]);
		else if (flag == 's')
			texture->so = ft_strdup(matrix[1]);
		else if (flag == 'w')
			texture->we = ft_strdup(matrix[1]);
		else if (flag == 'e')
			texture->ea = ft_strdup(matrix[1]);
	}
	free_arr(matrix);
	matrix = NULL;
	return (0);
}

void	initialize_nswe(t_texture *texture)
{	
	texture->no = NULL;
	texture->so = NULL;
	texture->we = NULL;
	texture->ea = NULL;
}

int	pars_nswe(t_texture *texture, char **line)
{
	int		i;
	int		l;
	char	flag;

	l = -1;
	initialize_nswe(texture);
	while (line[++l] && l < 6)
	{
		i = 0;
		flag = '!';
		while (ft_is_whitespace(line[l][i]))
			++i;
		if (!ft_strncmp(line[l] + i, "NO", 2))
			flag = 'n';
		else if (!ft_strncmp(line[l] + i, "SO", 2))
			flag = 's';
		else if (!ft_strncmp(line[l] + i, "WE", 2))
			flag = 'w';
		else if (!ft_strncmp(line[l] + i, "EA", 2))
			flag = 'e';
		if (flag != '!')
			if (ft_pars_n(texture, line, l, flag))
				return (1);
	}
	return (0);
}

int	check_patf_format(t_texture *texture)
{
	int	i;

	i = 0;
	if (ft_strcmp(texture->no + (ft_strlen(texture->no) - 4), ".xpm")
		|| ft_strcmp(texture->so + (ft_strlen(texture->so) - 4), ".xpm")
		|| ft_strcmp(texture->we + (ft_strlen(texture->we) - 4), ".xpm")
		|| ft_strcmp(texture->ea + (ft_strlen(texture->ea) - 4), ".xpm"))
	{
		write(2, "Incorrect path format\n", 22);
		return (1);
	}
	return (0);
}
