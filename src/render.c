/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:45:04 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/02/19 22:26:38 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/**
 * Renders a single tile of the game map.
 *
 * This function is responsible for rendering a single tile of the game map based on the
 * contents of the map array. It will render a wall, floor, collectible, player, or exit
 * sprite at the appropriate position on the game window.
 *
 * @param game Pointer to the game struct containing the game state and resources.
 * @param i The row index of the tile to be rendered.
 * @param j The column index of the tile to be rendered.
 */
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

/**
 * Renders the player's score and moves on the game window.
 *
 * This function is responsible for updating the player's move count and displaying it on the game window.
 * It will render a wall sprite to clear the previous score, then write the new move count to the console and
 * display it on the game window using the mlx_string_put function.
 *
 * @param game Pointer to the game struct containing the game state and resources.
 */
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
	mlx_string_put(game->win.addr, game->win.win, 10, 15, 0x000000FF, nbr);
	free(nbr);
}

/**
 * Renders the game map on the window.
 *
 * This function is responsible for rendering the game map on the window. It iterates through the map
 * and calls the `ft_put_map` function to render each tile. It also initializes the player's collectibles
 * and move count to 0, and stores the player's old position.
 *
 * @param game Pointer to the game struct containing the game state and resources.
 */
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

/**
 * Renders the player character on the game window.
 *
 * This function is responsible for rendering the player character on the game window. It first checks if the player has reached the exit and collected all the collectibles, in which case it calls the `ft_exit_game` function. It then clears the player's old position by rendering the floor sprite, and updates the player's collectibles count if the player is standing on a collectible. Finally, it renders the player's sprite at the current position.
 *
 * @param game Pointer to the game struct containing the game state and resources.
 */
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

/**
 * Loads an image from an XPM file and stores it in the provided t_img struct.
 *
 * This function is responsible for loading an image from an XPM file specified by the `path` member of the `t_img` struct. It uses the `mlx_xpm_file_to_image` function from the MLX library to load the image and store its width and height in the corresponding members of the `t_img` struct. If the image fails to load, the function calls the `ft_error` function to handle the error.
 *
 * @param spr Pointer to the t_img struct where the loaded image will be stored.
 * @param game Pointer to the t_game struct containing the game state and resources.
 */
void	ft_render_sprites(t_img *spr, t_game *game)
{
	spr->spr = mlx_xpm_file_to_image(game->win.addr, spr->path,
			&spr->width, &spr->height);
	if (!spr->spr)
		ft_error("Image not found!\n");
}
