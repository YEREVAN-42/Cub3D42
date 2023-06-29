/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <tbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:24:33 by khovakim          #+#    #+#             */
/*   Updated: 2023/06/27 15:11:20 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_strrchr(char *str, int c)
{
	int				k;
	unsigned char	*s;

	s = (unsigned char *)str;
	k = ft_strlen(str);
	if (c == '\0')
		return ((char *)(s + k));
	while (--k >= 0)
	{
		if (s[k] == (unsigned char)c)
			return ((char *)(s + k));
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	iff;
	size_t	len;
	char	*trm;

	iff = 0;
	while (s1[iff] && ft_strchr(set, s1[iff]))
		++iff;
	len = ft_strlen(s1);
	while (len && ft_strrchr(set, s1[len]))
		--len;
	trm = ft_substr(s1, iff, len - iff + 1);
	return (trm);
}
