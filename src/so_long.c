/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:50:19 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/02/19 22:30:35 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/**
 * Exits the game and cleans up resources.
 *
 * This function is called when the user requests to exit the game, such as by
 * pressing the Escape or Q key. It destroys the game window, frees the memory
 * used by the game map, and then exits the program.
 *
 * @param param A pointer to the main game struct.
 * @return 0 to indicate that the game has been successfully exited.
 */
int	ft_exit_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_destroy_window(game->win.addr, game->win.win);
	ft_free_map(game->map.map);
	exit(0);
}

/**
 * Handles keyboard input events for the game.
 *
 * This function is called whenever a key is pressed during the game. It
 * checks the key code and performs the corresponding action, such as
 * exiting the game or moving the player character.
 *
 * @param key The key code of the pressed key.
 * @param param A pointer to the main game struct.
 * @return 0 to indicate that the event has been handled.
 *//**
  * Handles keyboard input events for the game.
  *
  * This function is called whenever a key is pressed during the game. It
  * checks the key code and performs the corresponding action, such as
  * exiting the game or moving the player character.
  *
  * @param key The key code of the pressed key.
  * @param param A pointer to the main game struct.
  * @return 0 to indicate that the event has been handled.
 
/**
 * Handles keyboard input events for the game.
 *
 * This function is called whenever a key is pressed during the game. It
 * checks the key code and performs the corresponding action, such as
 * exiting the game or moving the player character.
 *
 * @param key The key code of the pressed key.
 * @param param A pointer to the main game struct.
 * @return 0 to indicate that the event has been handled.
 */
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

/**
 * Copies the game state from the main game struct to an auxiliary struct.
 * This allows the game state to be preserved and used for pathfinding and
 * other operations without modifying the main game state.
/**
  *
 * @param game The main game struct containing the current game state.
 * @param aux The auxiliary struct to copy the game state to.
 */
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

/**
 * Initializes the game state and sets up the game window.
 *
 * This function performs the following tasks:
 * - Validates the map file provided as an argument
 * - Copies the game state from the main game struct to an auxiliary struct
 * - Checks if there is a valid path from the player's starting position to the exit
 * - Initializes the MLX library and creates a new window for the game
 * - Sets the size of the game window based on the map dimensions
 * - Sets the window title
 * - Loads the game sprites and renders the initial map
 *
 * @param game The main game struct to be initialized.
 * @param aux The auxiliary game struct to be initialized.
 * @param av The path to the map file.
 */
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

/**
 * The main entry point of the So_Long game.
 *
 * This function performs the following tasks:
 * - Validates the number of command-line arguments
 * - Initializes the game state and sets up the game window
 * - Registers the key hook and exit hook functions
 * - Enters the main event loop to handle user input and game updates
 * - Frees the memory allocated for the game map
 *
 * @param ac The number of command-line arguments.
 * @param av The command-line arguments, including the path to the map file.
 * @return 0 on successful execution, -1 on error.
 */
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
