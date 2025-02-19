/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:45:04 by rzamolo-          #+#    #+#             */
/*   Updated: 2024/11/02 20:25:43 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	ft_put_map(t_game *game, int i, int j)
{
	if (game->map.map[i][j] == '1')
		mlx_put_image_to_window(game->win.addr, game->win.win,
			game->sprites.wall.spr, (j * TILE_SIZE), (i * TILE_SIZE));
	else
	{
		mlx_put_image_to_window(game->win.addr, game->win.win,
			game->sprites.floor.spr, (j * TILE_SIZE), (i * TILE_SIZE));
		if (game->map.map[i][j] == 'C')
		{
			mlx_put_image_to_window(game->win.addr, game->win.win,
				game->sprites.collectible.spr, (j * TILE_SIZE),
				(i * TILE_SIZE));
		}
		else if (game->map.map[i][j] == 'P')
		{
			game->player.x = j;
			game->player.y = i;
			mlx_put_image_to_window(game->win.addr, game->win.win,
				game->player.img.spr, (j * TILE_SIZE), (i * TILE_SIZE));
		}
		else if (game->map.map[i][j] == 'E')
			mlx_put_image_to_window(game->win.addr, game->win.win,
				game->sprites.exit.spr, (j * TILE_SIZE), (i * TILE_SIZE));
	}
}

void	ft_score(t_game *game)
{
	char	*nbr;

	game->player.moves++;
	mlx_put_image_to_window(game->win.addr, game->win.win,
		game->sprites.wall.spr, 0, 0);
	mlx_put_image_to_window(game->win.addr, game->win.win,
		game->sprites.wall.spr, 1 * TILE_SIZE, 0);
	nbr = ft_itoa(game->player.moves);
	write(1, "Moves: ", 7);
	write(1, nbr, ft_strlen(nbr));
	write(1, "\n", 1);
	mlx_string_put(game->win.addr, game->win.win, 10, 15, 0x00FF0000, nbr);
	free(nbr);
}

void	ft_render_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->player.collectibles = 0;
	game->player.moves = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (j <= game->map.columns)
		{
			ft_put_map(game, i, j),
			++j;
		}
		++i;
	}
	game->player.x_old = game->player.x;
	game->player.y_old = game->player.y;
}

void	ft_render_player(t_game *game)
{
	if (game->map.map[game->player.y][game->player.x] == 'E' &&
		game->player.collectibles == game->map.collectibles)
		ft_exit_game(game);
	mlx_put_image_to_window(game->win.addr, game->win.win,
		game->sprites.floor.spr, (game->player.x_old * TILE_SIZE),
		(game->player.y_old * TILE_SIZE));
	if (game->map.map[game->player.y][game->player.x] == 'C')
	{
		game->map.map[game->player.y][game->player.x] = '0';
		game->player.collectibles++;
	}
	mlx_put_image_to_window(game->win.addr, game->win.win,
		game->player.img.spr, (game->player.x * TILE_SIZE),
		(game->player.y * TILE_SIZE));
}

void	ft_render_sprites(t_img *spr, t_game *game)
{
	spr->spr = mlx_xpm_file_to_image(game->win.addr, spr->path,
			&spr->width, &spr->height);
	if (!spr->spr)
		ft_error("Image not found!\n");
}
