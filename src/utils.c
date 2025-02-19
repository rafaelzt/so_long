/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:20:46 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/02/19 22:25:41 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

// t_img	ft_new_image(t_win win, int width, int height)
// {
// 	t_img	img;

// 	img.win = win;
// 	img.spr = mlx_new_image(win.addr, width, height);
// 	img.addr = mlx_get_data_addr(img.spr, &img.bpp, &img.line_len, &img.endian);
// 	img.width = width;
// 	img.height = height;
// 	return (img);
// }

/**
 * Frees the memory allocated for a 2D map array.
 *
 * This function takes a 2D array of strings (char **) representing a map, and
 * frees the memory allocated for each row of the map, as well as the memory
 * allocated for the map array itself.
 *
 * @param map The 2D array of strings representing the map to be freed.
 */
void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

/**
 * Counts the number of lines in a given string.
 *
 * This function takes a string `map` and counts the number of newline characters
 * ('\n') in the string, which corresponds to the number of lines in the map.
 *
 * @param map The string to count the number of lines in.
 * @return The number of lines in the given string.
 */
size_t	ft_count_line(char *map)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (map[i] != '\0')
	{
		if (map[i] == '\n')
			++count;
		++i;
	}
	return (count);
}

size_t	ft_lenarr(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
		++i;
	return (i);
}

/**
 * Prints an error message and exits the program.
 *
 * This function takes a string `str` and prints it to stderr using the `perror`
 * function. It then exits the program with a status of 1.
 *
 * @param str The error message to be printed.
 */
void	ft_error(char *str)
{
	perror(str);
	exit (1);
}
