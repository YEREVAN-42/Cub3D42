/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <tbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:26:08 by khovakim          #+#    #+#             */
/*   Updated: 2023/06/27 15:11:20 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**ft_read_map(char *text)
{
	char	**line;
	char	*str;
	int		i;
	int		fd;

	i = 0;
	fd = open(text, O_RDONLY);
	line = malloc(sizeof(char *) * (ft_map_len(fd) + 1));
	close(fd);
	fd = open(text, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		if (ft_only_whitespaces(str) == 0 || i > 6)
		{
			line[i] = ft_strtrim(str, "\n");
			++i;
		}
		ft_free_str(str);
	}
	line[i] = NULL;
	close(fd);
	return (line);
}
