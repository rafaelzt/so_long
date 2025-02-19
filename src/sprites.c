/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:52:47 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/02/19 22:25:20 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/**
 * Loads and renders the game sprites.
 * This function is responsible for loading and rendering the various sprites used in the game, such as the wall, floor, collectibles, exit, and player.
 * It calls the `ft_render_sprites` function for each sprite to load and display it on the game screen.
 *
 * @param game The game state structure containing the sprite information.
 */
void	ft_load_game_sprites(t_game *game)
{
	ft_render_sprites(&game->sprites.wall, game);
	ft_render_sprites(&game->sprites.floor, game);
	ft_render_sprites(&game->sprites.collectible, game);
	ft_render_sprites(&game->sprites.exit, game);
	ft_render_sprites(&game->player.img, game);
}

/**
 * Sets the file paths for the game sprites.
 * This function initializes the file paths for the various sprites used in the game, such as the wall, floor, collectibles, exit, and player. It then calls the `ft_load_game_sprites` function to load and render these sprites.
 *
 * @param game The game state structure containing the sprite information.
 */
void	ft_set_sprites_path(t_game *game)
{
	game->sprites.wall.path = \
"/home/rzt/Documents/42/so_long/assets/images/wall.xpm";
	game->sprites.floor.path = \
"/home/rzt/Documents/42/so_long/assets/images/floor.xpm";
	game->sprites.collectible.path = \
"/home/rzt/Documents/42/so_long/assets/images/collectible.xpm";
	game->sprites.exit.path = \
"/home/rzt/Documents/42/so_long/assets/images/exit.xpm";
	game->player.img.path = \
"/home/rzt/Documents/42/so_long/assets/images/player.xpm";
	ft_load_game_sprites(game);
}
