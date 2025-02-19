/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:34:20 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/02/19 22:26:50 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/**
 * Sets the initial position of the player in the game.
 *
 * @param game The game struct containing the player's position.
 * @param x The x-coordinate of the player's starting position.
 * @param y The y-coordinate of the player's starting position.
 * @return 1 to indicate success.
 */
int	ft_start_player_position(t_game *game, int x, int y)
{
	game->player.x = x;
	game->player.y = y;
	return (1);
}

/**
 * Sets the position of the game exit.
 *
 * @param game The game struct containing the exit position.
 * @param x The x-coordinate of the exit position.
 * @param y The y-coordinate of the exit position.
 * @return 1 to indicate success.
 */
int	ft_exit_position(t_game *game, int x, int y)
{
	game->exit.x = x;
	game->exit.y = y;
	return (1);
}
