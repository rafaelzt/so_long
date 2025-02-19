/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:50:19 by rzamolo-          #+#    #+#             */
/*   Updated: 2024/11/01 18:09:59 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	ft_exit_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_destroy_window(game->win.addr, game->win.win);
	ft_free_map(game->map.map);
	exit(0);
}

int	ft_get_key(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == KEY_ESC || key == KEY_Q)
		ft_exit_game(game);
	else if (key == KEY_W || key == KEY_UP_ARROW)
		ft_moves(game, key);
	else if (key == KEY_A || key == KEY_LEFT_ARROW)
		ft_moves(game, key);
	else if (key == KEY_S || key == KEY_DOWN_ARROW)
		ft_moves(game, key);
	else if (key == KEY_D || key == KEY_RIGHT_ARROW)
		ft_moves(game, key);
	return (0);
}

void	ft_game_cpy(t_game *game, t_aux *aux)
{
	int	i;

	i = 0;
	aux->map = malloc(sizeof(char *) * game->map.rows);
	if (aux->map == NULL)
		ft_error("Allocate error");
	while (i < game->map.rows)
	{
		aux->map[i] = ft_strdup(game->map.map[i]);
		if (aux->map[i] == NULL)
			ft_error("Allocate error");
		i++;
	}
	aux->start_x = game->player.x;
	aux->start_y = game->player.y;
	aux->end_x = game->exit.x;
	aux->end_y = game->exit.y;
	aux->collectibles = game->map.collectibles;
	aux->reachable_c = 0;
	aux->rows = game->map.rows;
	aux->columns = game->map.columns;
	aux->reacheable_e = 0;
}

void	ft_init_game(t_game *game, t_aux *aux, char *av)
{
	ft_valid_map(game, av);
	ft_game_cpy(game, aux);
	if (!ft_valid_path(aux, aux->start_x, aux->start_y))
	{
		ft_error("There is no route to complete the map!\n");
		ft_free_map(game->map.map);
	}
	game->win.addr = mlx_init();
	game->win.width = (ft_strlen(game->map.map[0])) * TILE_SIZE;
	game->win.height = (ft_lenarr(game->map.map)) * TILE_SIZE;
	game->win.win = mlx_new_window(game->win.addr, game->win.width,
			game->win.height, "| rzamolo- | So_Long | rzamolo- |");
	ft_set_sprites_path(game);
	ft_render_map(game);
}

int	main(int ac, char **av)
{
	t_game	game;
	t_aux	aux;

	if (ac == 2)
	{
		ft_init_game(&game, &aux, av[1]);
		mlx_key_hook(game.win.win, ft_get_key, &game);
		mlx_hook(game.win.win, 17, 0, ft_exit_game, &game);
		mlx_loop(game.win.addr);
		ft_free_map(game.map.map);
		return (0);
	}
	perror("Number invalid of arguments!\n");
	return (-1);
}
