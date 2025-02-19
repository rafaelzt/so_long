/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:20:14 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/02/19 22:27:47 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/**
 * Recursively checks if a valid path exists from the current position to the exit and collects all collectibles.
 *
 * @param aux Pointer to the auxiliary data structure containing the game map and other state information.
 * @param x The current x-coordinate of the position being checked.
 * @param y The current y-coordinate of the position being checked.
 * @return 1 if a valid path exists, 0 otherwise.
 */
int	ft_valid_path(t_aux *aux, int x, int y)
{
	if (aux->map[y][x] == '1')
		return (0);
	if (aux->map[y][x] == 'E')
	{
		aux->reacheable_e++;
		if (aux->collectibles == aux->reachable_c)
			return (1);
	}
	if (aux->map[y][x] == 'C')
	{
		aux->reachable_c++;
		aux->map[y][x] = '0';
		if (aux->collectibles == aux->reachable_c && aux->reacheable_e == 1)
			return (1);
	}
	aux->map[y][x] = '1';
	if ((x + 1 < aux->columns && ft_valid_path(aux, x + 1, y))
		|| (x - 1 >= 0 && ft_valid_path(aux, x - 1, y))
		|| (y + 1 < aux->rows && ft_valid_path(aux, x, y + 1))
		|| (y - 1 >= 0 && ft_valid_path(aux, x, y - 1)))
		return (1);
	return (0);
}
