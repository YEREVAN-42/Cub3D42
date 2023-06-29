/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <tbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:26:32 by khovakim          #+#    #+#             */
/*   Updated: 2023/06/27 15:11:20 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		++len;
	return (len);
}

double	degree_to_radian(double degree)
{
	return (degree * 3.14159 / 180.0);
}

double	replace_angle_360(double degree)
{
	if (degree >= 360)
		degree = degree - 360;
	else if (degree <= -1)
		degree = degree + 360;
	return (degree);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}
