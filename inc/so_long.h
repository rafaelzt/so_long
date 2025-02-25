/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:27:51 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/02/20 22:41:56 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <mlx.h>	// MiniLibX
// # include "../mlx/mlx.h"
# include <stddef.h>
# include <unistd.h>
# include <sys/stat.h>
# include "libft.h"

// Definição de constantes
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define TILE_SIZE 50
// Definição de teclas
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113
// Definição de teclas
# define KEY_UP_ARROW 65362
# define KEY_LEFT_ARROW 65361
# define KEY_DOWN_ARROW 65364
# define KEY_RIGHT_ARROW 65363
# define KEY_ESC 65307

/**
 * @brief Auxiliary structure used for various purposes in the so_long project.
 *
 * This structure contains various fields that are used to store information
 * about the game map, such as the starting and ending coordinates, the number
 * of collectibles, the number of reachable collectibles, the number of rows and
 * columns in the map, and the number of reachable exits.
 */
typedef struct s_aux
{
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	char	**map;
	int		collectibles;
	int		reachable_c;
	int		rows;
	int		columns;
	int		reacheable_e;
}			t_aux;

typedef struct s_win
{
	void	*addr;
	void	*win;
	int		width;
	int		height;
}			t_win;

/**
 * @brief Auxiliary structure used to store information about an image.
 *
 * This structure contains various fields that are used to store information
 * about an image, such as the window it is associated with, the sprite data,
 * the image path, the image dimensions, and other metadata.
 */
typedef struct s_img
{
	t_win	win;
	void	*spr;
	char	*addr;
	char	*path;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_exit
{
	int	x;
	int	y;
}		t_exit;

typedef struct s_player
{
	t_img	img;
	int		x;
	int		y;
	int		x_old;
	int		y_old;
	int		moves;
	int		collectibles;
}			t_player;

typedef struct s_sprites
{
	t_img	wall;
	t_img	floor;
	t_img	collectible;
	t_img	exit;
}			t_sprites;

typedef struct s_map
{
	char	**map;
	int		rows;
	int		columns;
	int		collectibles;
}			t_map;

typedef struct s_game
{
	t_win		win;
	t_map		map;
	t_sprites	sprites;
	t_player	player;
	t_exit		exit;
}				t_game;

void	ft_init_game(t_game *game, t_aux *aux, char *av);
void	ft_game_cpy(t_game *game, t_aux *aux);
int		ft_get_key(int key, void *param);
int		ft_exit_game(void *param);

void	ft_valid_map(t_game *game, const char *file);
void	ft_check_ext(const char *file);
char	*ft_create_map(int fd);
void	ft_is_rectangle(char **lines, size_t len);
void	ft_scan_map(t_game *game, size_t len, size_t start, size_t end);

int		ft_start_player_position(t_game *game, int x, int y);
int		ft_exit_position(t_game *game, int x, int y);

void	ft_render_sprites(t_img *spr, t_game *game);
void	ft_render_player(t_game *game);
void	ft_render_map(t_game *game);
void	ft_score(t_game *game);
void	ft_put_map(t_game *game, int row, int col);

void	ft_set_sprites_path(t_game *game);
void	ft_load_game_sprites(t_game *game);

void	ft_free_map(char **map);
size_t	ft_lenarr(char **map);
size_t	ft_count_line(char *map);

int		ft_valid_path(t_aux *aux, int x, int y);
void	ft_error(char *str);

void	ft_moves(t_game *game, int key);
int		ft_up(t_game *game);
int		ft_left(t_game *game);
int		ft_down(t_game *game);
int		ft_right(t_game *game);

#endif
