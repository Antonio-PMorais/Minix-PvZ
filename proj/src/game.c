#include "game.h"
#include "v_card.h"
#include "i8042.h"
#include "proj.h"

// Dimensões para o VIDEO_MODE 0x115 (800x600 no VBE padrão)
#define SCREEN_W 800
#define SCREEN_H 600

// Cores (Formato RGB 24/32 bits)
#define COLOR_BG      0x228B22 // Verde relvado escuro
#define COLOR_UI      0x3b4d24 // Verde musgo para a barra superior
#define COLOR_CELL    0x32CD32 // Verde claro para as células (relva)
#define COLOR_PLANT   0x00FF00 // Verde néon (representa uma planta)
#define COLOR_CURSOR  0xFFFFFF // Branco

// Dimensões do Courtyard (9 colunas x 5 linhas)
#define GRID_COLS 9
#define GRID_ROWS 5
#define CELL_SIZE 80
#define GRID_START_X 40
#define GRID_START_Y 150

// Estado do rato
static int16_t mouse_x, mouse_y;
static bool prev_lb = false; // Guarda se o botão esquerdo estava premido no último frame (evita spam)
#define CURSOR_SIZE 8

// Estado da grelha (0 = vazio, 1 = ocupado por planta)
static int grid[GRID_ROWS][GRID_COLS];

// Flag de saída
static bool quit = false;
#define ESC_BREAKCODE 0x81

void game_init() {
    // Inicializar rato no centro
    mouse_x = SCREEN_W / 2;
    mouse_y = SCREEN_H / 2;
    
    // Limpar a grelha (0 plantas no início)
    for (int r = 0; r < GRID_ROWS; r++) {
        for (int c = 0; c < GRID_COLS; c++) {
            grid[r][c] = 0;
        }
    }
}

void game_update() {
    // Por enquanto vazio. 
    // No futuro: mover zombies para a esquerda, atualizar timers das plantas e sóis.
}

void game_render() {
    // 1. Limpar fundo (relvado base)
    vg_clear(COLOR_BG);

    // 2. Desenhar a barra de UI no topo (onde vão ficar os sóis e seleção de plantas)
    vg_draw_rectangle(0, 0, SCREEN_W, 100, COLOR_UI);

    // 3. Desenhar a grelha 9x5
    for (int r = 0; r < GRID_ROWS; r++) {
        for (int c = 0; c < GRID_COLS; c++) {
            int cell_x = GRID_START_X + c * CELL_SIZE;
            int cell_y = GRID_START_Y + r * CELL_SIZE;

            // Desenhar a célula (deixando uma pequena margem +2/-4 para fazer um efeito de grelha/rede)
            vg_draw_rectangle(cell_x + 2, cell_y + 2, CELL_SIZE - 4, CELL_SIZE - 4, COLOR_CELL);

            // Se houver uma planta (valor 1) nesta célula, desenha um quadrado menor no meio
            if (grid[r][c] == 1) {
                vg_draw_rectangle(cell_x + 20, cell_y + 20, 40, 40, COLOR_PLANT);
            }
        }
    }

    // 4. Desenhar o cursor do rato (uma cruz simples)
    vg_draw_rectangle(mouse_x - CURSOR_SIZE / 2, mouse_y - 1, CURSOR_SIZE, 2, COLOR_CURSOR);
    vg_draw_rectangle(mouse_x - 1, mouse_y - CURSOR_SIZE / 2, 2, CURSOR_SIZE, COLOR_CURSOR);

    // 5. Enviar back buffer para a VRAM
    vg_flip();
}

bool game_should_quit() {
    return quit;
}

void game_on_key(uint8_t scancode) {
    if (scancode == ESC_BREAKCODE) {
        quit = true;
    }
}

void game_on_mouse(struct packet *pp) {
    // Atualizar posição do rato
    mouse_x += pp->delta_x;
    mouse_y -= pp->delta_y;

    // Prender o rato aos limites do ecrã
    if (mouse_x < 0) mouse_x = 0;
    if (mouse_x >= SCREEN_W) mouse_x = SCREEN_W - 1;
    if (mouse_y < 0) mouse_y = 0;
    if (mouse_y >= SCREEN_H) mouse_y = SCREEN_H - 1;

    // Verificar se houve um "clique novo" (botão esquerdo pressionado agora, mas solto no frame anterior)
    if (pp->lb && !prev_lb) {
        
        // Verificar se o rato está dentro da zona do jardim (grelha)
        if (mouse_x >= GRID_START_X && mouse_x < GRID_START_X + GRID_COLS * CELL_SIZE &&
            mouse_y >= GRID_START_Y && mouse_y < GRID_START_Y + GRID_ROWS * CELL_SIZE) {
            
            // Calcular os índices [linha][coluna] corretos consoante a coordenada (x, y)
            int col = (mouse_x - GRID_START_X) / CELL_SIZE;
            int row = (mouse_y - GRID_START_Y) / CELL_SIZE;

            // Se a célula estiver vazia, planta lá!
            if (grid[row][col] == 0) {
                grid[row][col] = 1;
            }
        }
    }
    
    // Atualizar estado do botão para o próximo frame
    prev_lb = pp->lb;
}
