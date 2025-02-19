/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:44:22 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/02/19 22:28:47 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/**
 * Scans the game map and processes the map elements.
 *
 * This function iterates through the game map, processing the different
 * elements it encounters. It checks for valid characters ('0', '1', 'P', 'E',
 * 'C'), updates the player and exit positions, and increments the collectibles
 * count. If it encounters an invalid character, it calls the `ft_error()`
 * function to report an error.
 *
 * After processing the map, it checks if the number of player start positions
 * and exits is valid (either 1 of each, or 0 of each).
 *
 * @param game The game struct containing the map information.
 * @param len The length of each row in the map.
 * @param start The number of player start positions found.
 * @param end The number of exits found.
 */
void	ft_scan_map(t_game *game, size_t len, size_t start, size_t end)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < ft_lenarr(game->map.map))
	{
		j = -1;
		while (++j < len)
		{
			if (game->map.map[i][j] == '0' || game->map.map[i][j] == '1')
				continue ;
			else if (game->map.map[i][j] == 'P')
				start += ft_start_player_position(game, i, j);
			else if (game->map.map[i][j] == 'E')
				end += ft_exit_position(game, i, j);
			else if (game->map.map[i][j] == 'C')
				game->map.collectibles++;
			else
				ft_error("Invalid characters!\n");
		}
	}
	if ((end > 1 || start > 1) || (end == 0 && start == 0))
		ft_error("Invalid number of Start or End!\n");
}

/**
 * Checks if the map represented by the provided lines is a valid rectangle.
 *
 * This function iterates through the lines of the map, ensuring that each line
 * has the same length as the provided length parameter. It also checks that
 * the outer edges of the map are made up of '1' characters, indicating that
 * the map is properly enclosed.
 *
 * If any of these conditions are not met, the function calls the `ft_error()`
 * function to report an error.
 *
 * @param lines The 2D array of characters representing the map.
 * @param len The expected length of each line in the map.
 */
void	ft_is_rectangle(char **lines, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < ft_lenarr(lines) - 1)
	{
		j = 0;
		if (ft_strlen(lines[i]) != len)
			ft_error("Map format is invalid!\n");
		while (lines[i][j] != '\0')
		{
			if (lines[i][j] != '1' && (j == '0' || j == len - 1 || i == 0
				|| i == ft_lenarr(lines) - 1))
				ft_error("Map isn't close!\n");
			++j;
		}
		++i;
	}
}

/**
 * Reads the contents of a file descriptor and returns a string representing the map.
 *
 * This function reads the contents of the file descriptor `fd` and concatenates
 * the read bytes into a single string, which is then returned. The function
 * assumes that the file descriptor contains a map representation, and it does
 * not perform any validation on the contents of the file.
 *
 * @param fd The file descriptor to read the map from.
 * @return A string representing the map, or NULL if an error occurs.
 */
char	*ft_create_map(int fd)
{
	char	*line;
	char	*temp;
	char	buffer[2];

	line = malloc(sizeof(char) * 1);
	if (!line)
		ft_error("Error allocating map!\n");
	line[0] = '\0';
	while (read(fd, buffer, 1) > 0)
	{
		buffer[1] = '\0';
		temp = ft_strjoin(line, buffer);
		free(line);
		line = temp;
	}
	close(fd);
	return (line);
}

/**
 * Checks the file extension of the given file.
 *
 * This function checks if the file extension of the given file is ".ber". If the
 * extension is not ".ber", it calls the `ft_error` function with the error
 * message "Invalid file extension!".
 *
 * @param file The file path to check the extension of.
 */
void	ft_check_ext(const char *file)
{
	const char	*ext;
	int			len;
	int			len_ext;

	ext = ".ber";
	len = ft_strlen(file);
	len_ext = ft_strlen(ext);
	if (ft_strncmp(file + len - len_ext, ext, len_ext) != 0)
		ft_error("Invalid file extension!\n");
}

/**
 * Validates the map file and initializes the game's map.
 *
 * This function performs the following tasks:
 * 1. Checks the file extension of the given file to ensure it is a ".ber" file.
 * 2. Opens the file and reads its contents into a single string using the `ft_create_map` function.
 * 3. Splits the string into an array of lines using the `ft_split` function.
 * 4. Checks if the number of lines in the array matches the number of lines in the file.
 * 5. Frees the memory used by the line string.
 * 6. Checks if the map is a rectangle using the `ft_is_rectangle` function.
 * 7. Initializes the `rows`, `columns`, and `collectibles` fields of the game's map.
 * 8. Calls the `ft_scan_map` function to scan the map for valid elements.
 *
 * @param game The game structure containing the map information.
 * @param file The path to the map file to be validated.
 */
void	ft_valid_map(t_game *game, const char *file)
{
	int		fd;
	int		len;
	int		start;
	int		end;
	char	*line;

	start = 0;
	end = 0;
	ft_check_ext(file);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("Error opening file!\n");
	line = ft_create_map(fd);
	game->map.map = ft_split(line, '\n');
	if (ft_lenarr(game->map.map) != ft_count_line(line) + 1)
		ft_error("Invalid map!\n");
	free(line);
	len = ft_strlen(game->map.map[ft_lenarr(game->map.map) - 1]);
	ft_is_rectangle(game->map.map, len);
	game->map.rows = ft_lenarr(game->map.map);
	game->map.columns = ft_strlen(game->map.map[0]) - 1;
	game->map.collectibles = 0;
	ft_scan_map(game, len, start, end);
}
