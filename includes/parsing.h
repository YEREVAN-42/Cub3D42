/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <tbabayan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:23:49 by khovakim          #+#    #+#             */
/*   Updated: 2023/06/27 14:51:57 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "get_next_line.h"

# define ALLCHARS " 01NSWE"
# define EXCHARS "01NSWE"

typedef struct s_colors
{
	int	r;
	int	g;
	int	b;
}				t_colors;

typedef struct s_texture
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;

	t_colors	*floor;
	t_colors	*ceiling;
}				t_texture;

typedef struct s_map
{
	t_texture	*texture;
	char		**map;

	double		px;
	double		py;

	int			map_width;
	int			map_height;

	char		player;
}				t_map;

char	*ft_strdup(const char *s1);
char	*ft_strtrim(char *s1, char *set);
char	**ft_split(char const *s, char c);
char	**ft_split_space(char *str);
char	**ft_read_map(char *text);

void	parsing(t_map *map, char *text);

int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_map_len(int fd);
int		ft_only_whitespaces(char *str);
int		ft_is_whitespace(char c);
int		ft_isdigit(char **a);

long	ft_atoi(const char *str);

size_t	ft_matrix_size(char **matrix);
size_t	matrix_strlen(const char *str);

void	pars_map(t_map *map, char **line);
void	pars_rgb(t_texture *map, char **line);

int		pars_nswe(t_texture *texture, char **line);

void	check_nswe(char **line);
void	check_commas(char **line);
int		check_patf_format(t_texture *texture);
int		check_map(char **line);
int		check_map2(t_map *map);

//free
void	ft_free_str(char *cmd);
void	free_arr(char **arr);
void	free_all(t_map *map);

#endif