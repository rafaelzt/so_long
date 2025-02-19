/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:30:07 by rzamolo-          #+#    #+#             */
/*   Updated: 2024/10/21 12:07:52 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../mlx/mlx.h"
#include "../inc/so_long.h"

#define HEIGHT 640
#define WIDTH 480

// Keys
#define KEY_ESC 65307

#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_W 119

#define KEY_LEFT 65361
#define KEY_DOWN 65364
#define KEY_RIGHT 65363
#define KEY_UP 65362


int	key_press(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
    	mlx_destroy_window(vars->mlx, vars->win);  // Destroi a janela antes de sair
		exit(0);
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_window(t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);  // Destroi a janela antes de sair
    exit(0);  // Encerra o programa
    return (0);
}

void	draw_square(t_vars *vars, int x, int y, int size, int color)
{
	int	x_i;
	int	y_i;

	x_i = x;
	y_i = y;
	while (y_i < y + size)
	{
		while (x_i < x + size)
		{
			mlx_pixel_put(vars->mlx, vars->win, x, y, color);
			++x_i;
		}
	++y_i;
	}	
}

int	main(void)
{
	int		i;
	t_vars	vars;
	t_data	img;

	i = 5;
	// Initialize the connection between your software and the display
	vars.mlx = mlx_init();
	if (!vars.mlx)
	{
		fprintf(stderr, "Erro ao inicializar MiniLibX.\n");
		return (EXIT_FAILURE);
	}

	// Criar a janela e armazená-la na estrutura vars
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello world!");
	if (!vars.win)
	{
		fprintf(stderr, "Erro ao criar janela.\n");
		return (EXIT_FAILURE);
	}

	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	// Desenhar uma linha diagonal vermelha
	draw_square(&vars, 20, 20, 10, 0x00FF0000);

	// Colocar a imagem na janela
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

	// Hook para fechar a janela
	mlx_hook(vars.win, 17, 0, (int (*)())close_window, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_press, &vars);
	
	// Loop principal da MiniLibX
	mlx_loop(vars.mlx);

	return (0);
}

/*
int	main(void)
{
	int		i;
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	i = 5;
	mlx = mlx_init();
	if (!mlx)
	{
		printf("MiniLibX initialization error!\n");
		return (EXIT_FAILURE);
	}
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Hello world!");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	while (i < 100)
	{
		my_mlx_pixel_put(&img, i, i, 0x00FF0000);
		++i;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(mlx_win, 17, 0, &close_window, mlx);
	mlx_loop(mlx);
}
*/

/*
===============================================================================

    mlx_init: Initialises the MLX library. Must be called before using any other functions.
    mlx_new_window: Creates a new window instance.
    mlx_hook: Registers events.
    mlx_loop: Loops over the MLX pointer, triggering each hook in order of registration.
    mlx_xpm_file_to_image: Converts an XPM file to an MLX image pointer.
    mlx_put_image_to_window: Puts your image to the screen at the given coordinates.
    mlx_destroy_image: Frees the image.
    mlx_destroy_window: Frees the window instance.
    mlx_destroy_display: Frees MLX.
===============================================================================
*/


/*
===============================================================================
int	main(void)
{
	void	*mlx;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");

	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);

	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);	
	return (0);
}
===============================================================================
*/

/*
===============================================================================
int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
}
===============================================================================
*/
