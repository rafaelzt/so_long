/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:20:14 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/02/19 22:33:15 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/**
 * Recursively checks if a valid path exists from the current position to the 
 * exit and collects all collectibles.
 *
 * @param aux Pointer to the auxiliary data structure containing the game map 
 * and other state information.
 * @param col The current x-coordinate of the position being checked.
 * @param row The current y-coordinate of the position being checked.
 * @return 1 if a valid path exists, 0 otherwise.
 */
int	ft_valid_path(t_aux *aux, int col, int row)
{
	if (aux->map[row][col] == '1')
		return (0);
	if (aux->map[row][col] == 'E')
	{
		aux->reacheable_e++;
		if (aux->collectibles == aux->reachable_c)
			return (1);
	}
	if (aux->map[row][col] == 'C')
	{
		aux->reachable_c++;
		aux->map[row][col] = '0';
		if (aux->collectibles == aux->reachable_c && aux->reacheable_e == 1)
			return (1);
	}
	aux->map[row][col] = '1';
	if ((col + 1 < aux->columns && ft_valid_path(aux, col + 1, row))
		|| (col - 1 >= 0 && ft_valid_path(aux, col - 1, row))
		|| (row + 1 < aux->rows && ft_valid_path(aux, col, row + 1))
		|| (row - 1 >= 0 && ft_valid_path(aux, col, row - 1)))
		return (1);
	return (0);
}
