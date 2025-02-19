/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:52:47 by rzamolo-          #+#    #+#             */
/*   Updated: 2024/11/02 20:38:38 by rzamolo-         ###   ########.fr       */
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
"/home/rzt/Documents/42Madrid/so_long/assets/images/wall2.xpm";
	game->sprites.floor.path = \
"/home/rzt/Documents/42Madrid/so_long/assets/images/floor2.xpm";
	game->sprites.collectible.path = \
"/home/rzt/Documents/42Madrid/so_long/assets/images/collectible2.xpm";
	game->sprites.exit.path = \
"/home/rzt/Documents/42Madrid/so_long/assets/images/exit2.xpm";
	game->player.img.path = \
"/home/rzt/Documents/42Madrid/so_long/assets/images/player2.xpm";
	ft_load_game_sprites(game);
}
