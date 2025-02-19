/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:20:26 by rzamolo-          #+#    #+#             */
/*   Updated: 2024/11/02 21:11:58 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	ft_right(t_game *game)
{
	if (game->map.map[game->player.y][game->player.x + 1] != '1' &&
		game->map.map[game->player.y][game->player.x + 1] != 'E')
		game->player.x += 1;
	else if (game->map.map[game->player.y][game->player.x + 1] == 'E' &&
		game->player.collectibles == game->map.collectibles)
		game->player.x += 1;
	else
		return (0);
	return (1);
}

int	ft_down(t_game *game)
{
	if (game->map.map[game->player.y + 1][game->player.x] != '1' &&
		game->map.map[game->player.y + 1][game->player.x] != 'E')
		game->player.y += 1;
	else if (game->map.map[game->player.y + 1][game->player.x] == 'E' &&
		game->player.collectibles == game->map.collectibles)
		game->player.y += 1;
	else
		return (0);
	return (1);
}

int	ft_left(t_game *game)
{
	if (game->map.map[game->player.y][game->player.x - 1] != '1' &&
		game->map.map[game->player.y][game->player.x - 1] != 'E')
		game->player.x -= 1;
	else if (game->map.map[game->player.y][game->player.x - 1] == 'E' &&
		game->player.collectibles == game->map.collectibles)
		game->player.x -= 1;
	else
		return (0);
	return (1);
}

int	ft_up(t_game *game)
{
	if (game->map.map[game->player.y - 1][game->player.x] != '1' &&
		game->map.map[game->player.y - 1][game->player.x] != 'E')
		game->player.y -= 1;
	else if (game->map.map[game->player.y - 1][game->player.x] == 'E' &&
		game->player.collectibles == game->map.collectibles)
		game->player.y -= 1;
	else
		return (0);
	return (1);
}

void	ft_moves(t_game *game, int key)
{
	int	move;

	move = 0;
	game->player.x_old = game->player.x;
	game->player.y_old = game->player.y;
	if (key == KEY_W || key == KEY_UP_ARROW)
		move = ft_up(game);
	else if (key == KEY_A || key == KEY_LEFT_ARROW)
		move = ft_left(game);
	else if (key == KEY_S || key == KEY_DOWN_ARROW)
		move = ft_down(game);
	else if (key == KEY_D || key == KEY_RIGHT_ARROW)
		move = ft_right(game);
	if (move == 1)
	{
		ft_render_player(game);
		ft_score(game);
	}
}
