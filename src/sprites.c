/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:52:47 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/02/19 22:15:13 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	ft_load_game_sprites(t_game *game)
{
	ft_render_sprites(&game->sprites.wall, game);
	ft_render_sprites(&game->sprites.floor, game);
	ft_render_sprites(&game->sprites.collectible, game);
	ft_render_sprites(&game->sprites.exit, game);
	ft_render_sprites(&game->player.img, game);
}

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
