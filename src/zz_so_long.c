// Jogo de plataforma utilizando a MiniLibX
// Esse exemplo é simplificado e inclui apenas elementos básicos do jogo

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Definição das dimensões da janela e do jogador
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50
#define TILE_SIZE 50

// Macro para controlar a velocidade geral do jogo
// Ao alterar GAME_SPEED, é possível acelerar ou desacelerar todas as movimentações do jogo
#define GAME_SPEED 0.5

// Definição dos parâmetros de movimentação
#define GRAVITY (1 * GAME_SPEED)  // Gravidade aplicada ao jogador para simular queda
#define JUMP_STRENGTH (-15 * GAME_SPEED)  // Força do pulo do jogador
#define PLAYER_SPEED (3 * GAME_SPEED)  // Velocidade de movimentação horizontal do jogador
#define MAX_VELOCITY (5 * GAME_SPEED)  // Velocidade máxima de queda

// Mapa do jogo (1 = parede, 0 = espaço vazio, C = coletável, E = saída, P = jogador)
char *map[] = {
    "11111111111",
    "10000000001",
    "10E00000001",
    "11110001111",
    "10000000CC1",
    "1CC00111111",
    "11110000PC1",
    "11111111111"
};

char **mutable_map;

// Estrutura que armazena o estado do jogo
typedef struct s_game {
    void *mlx;
    void *window;
    void *image;
    char *image_data;
    int bpp;
    int size_line;
    int endian;
    void *player_sprite;
    void *wall_sprite;
    void *collectible_sprite;
    void *exit_sprite;
    int player_x;
    int player_y;
    int player_velocity;
    int is_jumping;
    int player_h_velocity;
    int moves;
    int collectibles;
} t_game;

// Renderiza o mapa na janela
// Essa função percorre o mapa e coloca as imagens correspondentes de acordo com o tipo de bloco
void render_map(t_game *game) {
    for (int y = 0; mutable_map[y]; y++) {
        for (int x = 0; mutable_map[y][x]; x++) {
            int screen_x = x * TILE_SIZE;
            int screen_y = y * TILE_SIZE;
            if (mutable_map[y][x] == '1') {
                // Renderiza as paredes
                mlx_put_image_to_window(game->mlx, game->window, game->wall_sprite, screen_x, screen_y);
            } else if (mutable_map[y][x] == 'C') {
                // Renderiza os coletáveis
                mlx_put_image_to_window(game->mlx, game->window, game->collectible_sprite, screen_x, screen_y);
            } else if (mutable_map[y][x] == 'E') {
                // Renderiza a saída
                mlx_put_image_to_window(game->mlx, game->window, game->exit_sprite, screen_x, screen_y);
            }
        }
    }
}

// Renderiza o jogador na janela
void render_player(t_game *game) {
    mlx_put_image_to_window(game->mlx, game->window, game->player_sprite, game->player_x, game->player_y);
}

// Renderiza a interface do usuário (UI) na tela, mostrando movimentos e coletáveis
void render_ui(t_game *game) {
    char moves_text[50];
    char collectibles_text[50];
    sprintf(moves_text, "Movimentos: %d", game->moves);
    sprintf(collectibles_text, "Coletáveis: %d", game->collectibles);
    mlx_string_put(game->mlx, game->window, 10, 10, 0xFFFFFF, moves_text);
    mlx_string_put(game->mlx, game->window, 10, 30, 0xFFFFFF, collectibles_text);
}

// Verifica se há colisão em determinada posição
// Retorna 1 se houver colisão com uma parede, caso contrário retorna 0
int check_collision(int x, int y) {
    int map_x = x / TILE_SIZE;
    int map_y = y / TILE_SIZE;
    if (map_x < 0 || map_y < 0 || map_y >= 8 || map_x >= 11 || mutable_map[map_y] == NULL || mutable_map[map_y][map_x] == '1')
        return 1;
    return 0;
}

// Verifica se o jogador está em um coletável e o coleta
void collect_item(t_game *game) {
    int map_x = (game->player_x + PLAYER_WIDTH / 2) / TILE_SIZE;
    int map_y = (game->player_y + PLAYER_HEIGHT / 2) / TILE_SIZE;

    // Garantir que as coordenadas estão dentro dos limites do mapa
    if (map_y >= 0 && map_y < 8 && map_x >= 0 && map_x < 11) {
        char cell = mutable_map[map_y][map_x];
        if (cell == 'C') {
            mutable_map[map_y][map_x] = '0'; // Remove o coletável do mapa
            game->collectibles++;
        }
    }
}

// Atualiza a lógica do jogo, incluindo movimentação do jogador e coleta de itens
int update(t_game *game) {
    // Atualizar a posição vertical do jogador (queda ou pulo)
    if (game->player_y + PLAYER_HEIGHT < WINDOW_HEIGHT) {
        game->player_velocity += GRAVITY;
        if (game->player_velocity > MAX_VELOCITY)
            game->player_velocity = MAX_VELOCITY;
    } else {
        game->player_velocity = 0;
        game->player_y = WINDOW_HEIGHT - PLAYER_HEIGHT;
        game->is_jumping = 0;
    }

    int new_player_y = game->player_y + game->player_velocity;
    if (new_player_y >= 0 && new_player_y + PLAYER_HEIGHT <= WINDOW_HEIGHT &&
        !check_collision(game->player_x, new_player_y + PLAYER_HEIGHT - 1) &&
        !check_collision(game->player_x + PLAYER_WIDTH - 1, new_player_y + PLAYER_HEIGHT - 1)) {
        game->player_y = new_player_y;
    } else {
        game->player_velocity = 0;
        game->is_jumping = 0;
    }

    // Atualizar a posição horizontal do jogador
    int new_player_x = game->player_x + game->player_h_velocity;
    if (new_player_x >= 0 && new_player_x + PLAYER_WIDTH <= WINDOW_WIDTH &&
        !check_collision(new_player_x, game->player_y) &&
        !check_collision(new_player_x + PLAYER_WIDTH - 1, game->player_y) &&
        !check_collision(new_player_x, game->player_y + PLAYER_HEIGHT - 1) &&
        !check_collision(new_player_x + PLAYER_WIDTH - 1, game->player_y + PLAYER_HEIGHT - 1)) {
        game->player_x = new_player_x;
    }

    // Coletar itens se o jogador estiver em um coletável
    collect_item(game);

    // Verificar se o jogador atingiu a saída e se todos os coletáveis foram coletados
    int map_x = (game->player_x + PLAYER_WIDTH / 2) / TILE_SIZE;
    int map_y = (game->player_y + PLAYER_HEIGHT / 2) / TILE_SIZE;
    if (map_y >= 0 && map_y < 8 && map_x >= 0 && map_x < 11 && mutable_map[map_y][map_x] == 'E') {
        int remaining_collectibles = 0;
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 11; x++) {
                if (mutable_map[y][x] == 'C') {
                    remaining_collectibles++;
                }
            }
        }
        if (remaining_collectibles == 0) {
            // Finaliza o jogo se todos os coletáveis foram coletados
            printf("Jogo encerrado!\n");
            printf("Total de movimentos: %d\n", game->moves);
            printf("Total de coletáveis: %d\n", game->collectibles);
            exit(0);
        }
    }

    // Renderizar mapa, jogador e UI na janela
    mlx_clear_window(game->mlx, game->window);
    render_map(game);
    render_player(game);
    render_ui(game);
    return 0;
}

// Função chamada quando uma tecla é pressionada
int key_press(int keycode, t_game *game) {
    if (keycode == 65307) { // ESC para sair
        printf("Jogo encerrado!\n");
        printf("Total de movimentos: %d\n", game->moves);
        printf("Total de coletáveis: %d\n", game->collectibles);
        mlx_string_put(game->mlx, game->window, 10, 50, 0xFF0000, "Jogo encerrado!");
        char end_moves_text[50];
        char end_collectibles_text[50];
        sprintf(end_moves_text, "Total de movimentos: %d", game->moves);
        sprintf(end_collectibles_text, "Total de coletáveis: %d", game->collectibles);
        mlx_string_put(game->mlx, game->window, 10, 70, 0xFF0000, end_moves_text);
        mlx_string_put(game->mlx, game->window, 10, 90, 0xFF0000, end_collectibles_text);
        exit(0);
    }
    else if (keycode == 119) { // W para pular
        if (!game->is_jumping) {
            game->is_jumping = 1;
            game->player_velocity = JUMP_STRENGTH;
            game->moves++;
        }
    } else if (keycode == 97) { // A para mover para a esquerda
        game->player_h_velocity = -PLAYER_SPEED;
        game->moves++;
    } else if (keycode == 100) { // D para mover para a direita
        game->player_h_velocity = PLAYER_SPEED;
        game->moves++;
    }
    return 0;
}

// Função chamada quando uma tecla é solta
int key_release(int keycode, t_game *game) {
    if (keycode == 97 || keycode == 100) { // A ou D para parar de mover horizontalmente
        game->player_h_velocity = 0;
    }
    return 0;
}

// Função principal que inicializa o jogo e configura a janela
int main() {
    t_game game;

    // Criar uma cópia mutável do mapa
    mutable_map = malloc(8 * sizeof(char *));
    for (int i = 0; i < 8; i++) {
        mutable_map[i] = strdup(map[i]);
    }

    int player_width, player_height;
    int tile_width, tile_height;

    // Inicializar a MiniLibX
    game.mlx = mlx_init();
    if (game.mlx == NULL) {
        printf("Erro: Não foi possível inicializar a MiniLibX.\n");
        return 1;
    }

    // Criar uma janela para o jogo
    game.window = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Jogo de Plataforma");
    if (game.window == NULL) {
        printf("Erro: Não foi possível criar a janela.\n");
        return 1;
    }

    // Carregar sprites do jogador, parede, coletável e saída
    game.player_sprite = mlx_xpm_file_to_image(game.mlx, "/home/rzt/Documents/42Madrid/so_long/assets/images/player2.xpm", &player_width, &player_height);
    if (game.player_sprite == NULL) {
        printf("Erro: Não foi possível carregar o sprite do jogador.\n");
        return 1;
    }

    game.wall_sprite = mlx_xpm_file_to_image(game.mlx, "/home/rzt/Documents/42Madrid/so_long/assets/images/wall2.xpm", &tile_width, &tile_height);
    if (game.wall_sprite == NULL) {
        printf("Erro: Não foi possível carregar o sprite da parede.\n");
        return 1;
    }

    game.collectible_sprite = mlx_xpm_file_to_image(game.mlx, "/home/rzt/Documents/42Madrid/so_long/assets/images/collectible2.xpm", &tile_width, &tile_height);
    if (game.collectible_sprite == NULL) {
        printf("Erro: Não foi possível carregar o sprite do coletável.\n");
        return 1;
    }

    game.exit_sprite = mlx_xpm_file_to_image(game.mlx, "/home/rzt/Documents/42Madrid/so_long/assets/images/exit2.xpm", &tile_width, &tile_height);
    if (game.exit_sprite == NULL) {
        printf("Erro: Não foi possível carregar o sprite da saída.\n");
        return 1;
    }

    // Localizar a posição inicial do jogador no mapa
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 11; x++) {
            if (mutable_map[y][x] == 'P') {
                game.player_x = x * TILE_SIZE;
                game.player_y = y * TILE_SIZE;
                mutable_map[y][x] = '0';  // Remove o marcador 'P' do mapa
            }
        }
    }

    // Configurações iniciais do jogador
    game.player_velocity = 0;
    game.is_jumping = 0;
    game.player_h_velocity = 0;
    game.moves = 0;
    game.collectibles = 0;

    // Configuração dos eventos de atualização e teclas
    mlx_loop_hook(game.mlx, update, &game);
    mlx_hook(game.window, 2, 1L << 0, key_press, &game);
    mlx_hook(game.window, 3, 1L << 1, key_release, &game);
    mlx_loop(game.mlx);

    // Liberar a memória do mapa
    for (int i = 0; i < 8; i++) {
        free(mutable_map[i]);
    }
    free(mutable_map);

    return 0;
}


// Jogo de plataforma utilizando a MiniLibX
// Esse exemplo é simplificado e inclui apenas elementos básicos do jogo

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Definição das dimensões da janela e do jogador
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50
#define TILE_SIZE 50

// Macro para controlar a velocidade geral do jogo
// Ao alterar GAME_SPEED, é possível acelerar ou desacelerar todas as movimentações do jogo
#define GAME_SPEED 0.5

// Definição dos parâmetros de movimentação
#define GRAVITY (1 * GAME_SPEED)  // Gravidade aplicada ao jogador para simular queda
#define JUMP_STRENGTH (-15 * GAME_SPEED)  // Força do pulo do jogador
#define PLAYER_SPEED (3 * GAME_SPEED)  // Velocidade de movimentação horizontal do jogador
#define MAX_VELOCITY (5 * GAME_SPEED)  // Velocidade máxima de queda

// Mapa do jogo (1 = parede, 0 = espaço vazio, C = coletável, E = saída, P = jogador)
char *map[] = {
    "11111111111",
    "10000000001",
    "10E00000001",
    "11110001111",
    "10000000CC1",
    "1CC00111111",
    "11110000PC1",
    "11111111111"
};

char **mutable_map;

// Estrutura que armazena o estado do jogo
typedef struct s_game {
    void *mlx;
    void *window;
    void *image;
    char *image_data;
    int bpp;
    int size_line;
    int endian;
    void *player_sprite;
    void *wall_sprite;
    void *collectible_sprite;
    void *exit_sprite;
    int player_x;
    int player_y;
    int player_velocity;
    int is_jumping;
    int player_h_velocity;
    int moves;
    int collectibles;
} t_game;

// Renderiza o mapa na janela
// Essa função percorre o mapa e coloca as imagens correspondentes de acordo com o tipo de bloco
void render_map(t_game *game) {
    for (int y = 0; mutable_map[y]; y++) {
        for (int x = 0; mutable_map[y][x]; x++) {
            int screen_x = x * TILE_SIZE;
            int screen_y = y * TILE_SIZE;
            if (mutable_map[y][x] == '1') {
                // Renderiza as paredes
                mlx_put_image_to_window(game->mlx, game->window, game->wall_sprite, screen_x, screen_y);
            } else if (mutable_map[y][x] == 'C') {
                // Renderiza os coletáveis
                mlx_put_image_to_window(game->mlx, game->window, game->collectible_sprite, screen_x, screen_y);
            } else if (mutable_map[y][x] == 'E') {
                // Renderiza a saída
                mlx_put_image_to_window(game->mlx, game->window, game->exit_sprite, screen_x, screen_y);
            }
        }
    }
}

// Renderiza o jogador na janela
void render_player(t_game *game) {
    mlx_put_image_to_window(game->mlx, game->window, game->player_sprite, game->player_x, game->player_y);
}

// Renderiza a interface do usuário (UI) na tela, mostrando movimentos e coletáveis
void render_ui(t_game *game) {
    char moves_text[50];
    char collectibles_text[50];
    sprintf(moves_text, "Movimentos: %d", game->moves);
    sprintf(collectibles_text, "Coletáveis: %d", game->collectibles);
    mlx_string_put(game->mlx, game->window, 10, 10, 0xFFFFFF, moves_text);
    mlx_string_put(game->mlx, game->window, 10, 30, 0xFFFFFF, collectibles_text);
}

// Verifica se há colisão em determinada posição
// Retorna 1 se houver colisão com uma parede, caso contrário retorna 0
int check_collision(int x, int y) {
    int map_x = x / TILE_SIZE;
    int map_y = y / TILE_SIZE;
    if (map_x < 0 || map_y < 0 || map_y >= 8 || map_x >= 11 || mutable_map[map_y] == NULL || mutable_map[map_y][map_x] == '1')
        return 1;
    return 0;
}

// Verifica se o jogador está em um coletável e o coleta
void collect_item(t_game *game) {
    int map_x = (game->player_x + PLAYER_WIDTH / 2) / TILE_SIZE;
    int map_y = (game->player_y + PLAYER_HEIGHT / 2) / TILE_SIZE;

    // Garantir que as coordenadas estão dentro dos limites do mapa
    if (map_y >= 0 && map_y < 8 && map_x >= 0 && map_x < 11) {
        char cell = mutable_map[map_y][map_x];
        if (cell == 'C') {
            mutable_map[map_y][map_x] = '0'; // Remove o coletável do mapa
            game->collectibles++;
        }
    }
}

// Atualiza a lógica do jogo, incluindo movimentação do jogador e coleta de itens
int update(t_game *game) {
    // Atualizar a posição vertical do jogador (queda ou pulo)
    if (game->player_y + PLAYER_HEIGHT < WINDOW_HEIGHT) {
        game->player_velocity += GRAVITY;
        if (game->player_velocity > MAX_VELOCITY)
            game->player_velocity = MAX_VELOCITY;
    } else {
        game->player_velocity = 0;
        game->player_y = WINDOW_HEIGHT - PLAYER_HEIGHT;
        game->is_jumping = 0;
    }

    int new_player_y = game->player_y + game->player_velocity;
    if (new_player_y >= 0 && new_player_y + PLAYER_HEIGHT <= WINDOW_HEIGHT &&
        !check_collision(game->player_x, new_player_y + PLAYER_HEIGHT - 1) &&
        !check_collision(game->player_x + PLAYER_WIDTH - 1, new_player_y + PLAYER_HEIGHT - 1)) {
        game->player_y = new_player_y;
    } else {
        game->player_velocity = 0;
        game->is_jumping = 0;
    }

    // Atualizar a posição horizontal do jogador
    int new_player_x = game->player_x + game->player_h_velocity;
    if (new_player_x >= 0 && new_player_x + PLAYER_WIDTH <= WINDOW_WIDTH &&
        !check_collision(new_player_x, game->player_y) &&
        !check_collision(new_player_x + PLAYER_WIDTH - 1, game->player_y) &&
        !check_collision(new_player_x, game->player_y + PLAYER_HEIGHT - 1) &&
        !check_collision(new_player_x + PLAYER_WIDTH - 1, game->player_y + PLAYER_HEIGHT - 1)) {
        game->player_x = new_player_x;
    }

    // Coletar itens se o jogador estiver em um coletável
    collect_item(game);

    // Verificar se o jogador atingiu a saída e se todos os coletáveis foram coletados
    int map_x = (game->player_x + PLAYER_WIDTH / 2) / TILE_SIZE;
    int map_y = (game->player_y + PLAYER_HEIGHT / 2) / TILE_SIZE;
    if (map_y >= 0 && map_y < 8 && map_x >= 0 && map_x < 11 && mutable_map[map_y][map_x] == 'E') {
        int remaining_collectibles = 0;
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 11; x++) {
                if (mutable_map[y][x] == 'C') {
                    remaining_collectibles++;
                }
            }
        }
        if (remaining_collectibles == 0) {
            // Finaliza o jogo se todos os coletáveis foram coletados
            printf("Jogo encerrado!\n");
            printf("Total de movimentos: %d\n", game->moves);
            printf("Total de coletáveis: %d\n", game->collectibles);
            exit(0);
        }
    }

    // Renderizar mapa, jogador e UI na janela
    mlx_clear_window(game->mlx, game->window);
    render_map(game);
    render_player(game);
    render_ui(game);
    return 0;
}

// Função chamada quando uma tecla é pressionada
int key_press(int keycode, t_game *game) {
    if (keycode == 65307) { // ESC para sair
        printf("Jogo encerrado!\n");
        printf("Total de movimentos: %d\n", game->moves);
        printf("Total de coletáveis: %d\n", game->collectibles);
        mlx_string_put(game->mlx, game->window, 10, 50, 0xFF0000, "Jogo encerrado!");
        char end_moves_text[50];
        char end_collectibles_text[50];
        sprintf(end_moves_text, "Total de movimentos: %d", game->moves);
        sprintf(end_collectibles_text, "Total de coletáveis: %d", game->collectibles);
        mlx_string_put(game->mlx, game->window, 10, 70, 0xFF0000, end_moves_text);
        mlx_string_put(game->mlx, game->window, 10, 90, 0xFF0000, end_collectibles_text);
        exit(0);
    }
    else if (keycode == 119) { // W para pular
        if (!game->is_jumping) {
            game->is_jumping = 1;
            game->player_velocity = JUMP_STRENGTH;
            game->moves++;
        }
    } else if (keycode == 97) { // A para mover para a esquerda
        game->player_h_velocity = -PLAYER_SPEED;
        game->moves++;
    } else if (keycode == 100) { // D para mover para a direita
        game->player_h_velocity = PLAYER_SPEED;
        game->moves++;
    }
    return 0;
}

// Função chamada quando uma tecla é solta
int key_release(int keycode, t_game *game) {
    if (keycode == 97 || keycode == 100) { // A ou D para parar de mover horizontalmente
        game->player_h_velocity = 0;
    }
    return 0;
}

// Função principal que inicializa o jogo e configura a janela
int main() {
    t_game game;

    // Criar uma cópia mutável do mapa
    mutable_map = malloc(8 * sizeof(char *));
    for (int i = 0; i < 8; i++) {
        mutable_map[i] = strdup(map[i]);
    }

    int player_width, player_height;
    int tile_width, tile_height;

    // Inicializar a MiniLibX
    game.mlx = mlx_init();
    if (game.mlx == NULL) {
        printf("Erro: Não foi possível inicializar a MiniLibX.\n");
        return 1;
    }

    // Criar uma janela para o jogo
    game.window = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Jogo de Plataforma");
    if (game.window == NULL) {
        printf("Erro: Não foi possível criar a janela.\n");
        return 1;
    }

    // Carregar sprites do jogador, parede, coletável e saída
    game.player_sprite = mlx_xpm_file_to_image(game.mlx, "/home/rzt/Documents/42Madrid/so_long/assets/images/player2.xpm", &player_width, &player_height);
    if (game.player_sprite == NULL) {
        printf("Erro: Não foi possível carregar o sprite do jogador.\n");
        return 1;
    }

    game.wall_sprite = mlx_xpm_file_to_image(game.mlx, "/home/rzt/Documents/42Madrid/so_long/assets/images/wall2.xpm", &tile_width, &tile_height);
    if (game.wall_sprite == NULL) {
        printf("Erro: Não foi possível carregar o sprite da parede.\n");
        return 1;
    }

    game.collectible_sprite = mlx_xpm_file_to_image(game.mlx, "/home/rzt/Documents/42Madrid/so_long/assets/images/collectible2.xpm", &tile_width, &tile_height);
    if (game.collectible_sprite == NULL) {
        printf("Erro: Não foi possível carregar o sprite do coletável.\n");
        return 1;
    }

    game.exit_sprite = mlx_xpm_file_to_image(game.mlx, "/home/rzt/Documents/42Madrid/so_long/assets/images/exit2.xpm", &tile_width, &tile_height);
    if (game.exit_sprite == NULL) {
        printf("Erro: Não foi possível carregar o sprite da saída.\n");
        return 1;
    }

    // Configurações iniciais do jogador
    game.player_x = 7 * TILE_SIZE;
    game.player_y = 5 * TILE_SIZE;
    game.player_velocity = 0;
    game.is_jumping = 0;
    game.player_h_velocity = 0;
    game.moves = 0;
    game.collectibles = 0;

    // Configuração dos eventos de atualização e teclas
    mlx_loop_hook(game.mlx, update, &game);
    mlx_hook(game.window, 2, 1L << 0, key_press, &game);
    mlx_hook(game.window, 3, 1L << 1, key_release, &game);
    mlx_loop(game.mlx);

    // Liberar a memória do mapa
    for (int i = 0; i < 8; i++) {
        free(mutable_map[i]);
    }
    free(mutable_map);

    return 0;
}

