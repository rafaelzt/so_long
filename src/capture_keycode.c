/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capture_keycode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:07:16 by rzamolo-          #+#    #+#             */
/*   Updated: 2024/11/02 20:29:26 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../inc/so_long.h"

int	key_press(int keycode, void *param)
{
	(void)param;
	printf("Key pressed: %d\n", keycode);
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 640, 480, "Key Press Test");
	mlx_hook(mlx_win, 2, 1L << 0, key_press, NULL);
	mlx_loop(mlx);
	return (0);
}
