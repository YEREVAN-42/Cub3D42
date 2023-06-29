/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <tbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:24:18 by khovakim          #+#    #+#             */
/*   Updated: 2023/06/27 15:11:20 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_free_str(char *cmd)
{	
	if (cmd != NULL)
	{
		free(cmd);
		cmd = 0;
	}
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = 0;
		}
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_all(t_map *map)
{
	if (map->texture->no)
		free(map->texture->no);
	if (map->texture->so)
		free(map->texture->so);
	if (map->texture->we)
		free(map->texture->we);
	if (map->texture->ea)
		free(map->texture->ea);
	free(map->texture->ceiling);
	free(map->texture->floor);
	free(map->texture);
	map->texture = NULL;
	free(map);
	map = NULL;
}

void	free_game_addr(char **addr)
{
	int	i;

	if (addr == NULL)
		return ;
	i = 0;
	while (i < 9)
	{
		free(addr[i]);
		addr[i] = NULL;
		i++;
	}
}

void	list_free(t_list *map)
{
	t_list	*tmp;

	if (!map)
		return ;
	tmp = map;
	while (map)
	{
		if (tmp->content)
			free(tmp->content);
		tmp->content = NULL;
		tmp = tmp->next;
		free(map);
		map = tmp;
	}
}
