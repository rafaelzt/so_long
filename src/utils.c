/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:20:46 by rzamolo-          #+#    #+#             */
/*   Updated: 2024/11/02 20:27:40 by rzamolo-         ###   ########.fr       */
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

void	ft_error(char *str)
{
	perror(str);
	exit (1);
}
