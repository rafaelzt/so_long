#include "../inc/so_long.h"

void draw_game(t_game *game)
{
    int x;
    int y;
    char tile;

    mlx_clear_window(game->mlx, game->win);
    for (y = 0; y < game->map.height; y++)
    {
        for (x = 0; x < game->map.width; x++)
        {
            tile = game->map.data[y][x];
            if (tile == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->sprites.wall, x * TILE_SIZE, y * TILE_SIZE);
            else if (tile == '0')
                mlx_put_image_to_window(game->mlx, game->win, game->sprites.floor, x * TILE_SIZE, y * TILE_SIZE);
            else if (tile == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->sprites.collectible, x * TILE_SIZE, y * TILE_SIZE);
            else if (tile == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->sprites.exit, x * TILE_SIZE, y * TILE_SIZE);
        }
    }
    // Desenhar o jogador na posição atual
    mlx_put_image_to_window(game->mlx, game->win, game->sprites.player,
                            game->player.x, game->player.y);
}

