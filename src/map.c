/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:44:22 by rzamolo-          #+#    #+#             */
/*   Updated: 2024/11/01 15:41:16 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

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
