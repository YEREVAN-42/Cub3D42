/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khovakim <khovakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:23:32 by khovakim          #+#    #+#             */
/*   Updated: 2023/06/27 20:48:01 by khovakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include "./parsing.h"
# include "./get_next_line.h"

# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000

# define NONE 0xFF000000
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define MAGENTA 0x00FF00FF
# define YELLOW 0x00FFFF00
# define CYAN 0x0000FFFF
# define GRAY 0x00808080
# define DARK_GRAY 0x00404040
# define LIGHT_GRAY 0x00C0C0C0
# define ORANGE 0x00FFA500
# define BROWN 0x008B4513
# define PURPLE 0x00800080

typedef struct s_img
{
	void	*img;

	char	*addr[6];

	int		bits_per_px[6];
	int		size_len[6];
	int		endian[6];
}			t_img;

typedef struct s_ray
{
	double	xo;
	double	yo;
	double	ra;
	double	hx;
	double	hy;
	double	vx;
	double	vy;
	double	px;
	double	py;
	double	rx;
	double	ry;
	double	atan_ra;
	double	tan_ra;

	int		depth;
	int		zeros;
	int		zerosh;
}				t_ray;

typedef struct s_player
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
}			t_player;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_game
{
	t_player	*player;
	t_img		*img;
	t_map		*map;
	t_list		*mapp;

	void		*mlx;
	void		*mlx_window;
	void		*no;
	void		*so;
	void		*ea;
	void		*we;
	void		*minimap;

	double		map_height;
	double		map_width;
	double		pa;
	double		dist;
	double		stepy;
	double		angle;

	int			minimap_x;
	int			minimap_y;
	int			zeros;
	int			ray;
	int			linelen;
	int			step_num;
}				t_game;

void	game_start(t_game *game, t_map *map);
void	init_struct(t_game *game);
void	draw_player(t_game *game);
void	ft_putstr_fd(char *s, int fd);
void	getting_address(t_game *game, t_map *map);
void	ft_raycasting(t_game *game);
void	player_init_angle(t_game *game, t_map *map);
void	horizontal_lines(t_game *game, t_ray *ray);
void	draw_line(t_game *game, int i);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	put_map_sym(int mx, int my, t_game *game, char c);
void	r_key(t_game *game);
void	l_key(t_game *game);
void	list_free(t_list *map);
void	free_game_addr(char **addr);
void	my_mlx_pixel_put(t_game *game, int x, int y, int clr);
void	map_rendering(t_game *game);

int		key_hooks(int key, t_game *game);
int		key_hooks(int key, t_game *game);
int		game_end(t_game *game);
int		start_game(t_game *game);

double	degree_to_radian(double degree);
double	replace_angle_360(double degree);
double	calc_dist(t_ray *ray);

char	get_map_sym(int mx, int my, t_game *game);
char	**ft_split(char const *s, char c);

#endif