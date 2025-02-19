/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:34:20 by rzamolo-          #+#    #+#             */
/*   Updated: 2024/11/01 15:37:23 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	ft_start_player_position(t_game *game, int x, int y)
{
	game->player.x = x;
	game->player.y = y;
	return (1);
}

int	ft_exit_position(t_game *game, int x, int y)
{
	game->exit.x = x;
	game->exit.y = y;
	return (1);
}
