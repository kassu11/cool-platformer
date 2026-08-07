#include "raylib.h"
#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum {
  TOP_1,
  TOP_2,
  TOP_3,
  TOP_4,
  TOP_5,
  BOTTOM_1,
  BOTTOM_2,
  BOTTOM_3,
  BOTTOM_4,
  BOTTOM_5,
  LEFT_1,
  LEFT_2,
  LEFT_3,
  LEFT_4,
  LEFT_5,
  RIGHT_1,
  RIGHT_2,
  RIGHT_3,
  RIGHT_4,
  RIGHT_5,
  CORNER_1,
  CORNER_2,
  CORNER_3,
  CORNER_4,
  CORNER_5,
} TileDirection;

Texture2D tile_atlas;
typedef struct {
  int x;
  int y;
} Tile;



Texture2D loadTexture(const char *fileName) {
  Image image = LoadImage(fileName);                // Loaded in CPU memory (RAM)
  Texture2D texture = LoadTextureFromImage(image);  // Image converted to texture, GPU memory (VRAM)
  UnloadImage(image);                               // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

  if (!IsTextureValid(texture)) {
    printf("Error loading texture \"%s\"", fileName);
    exit(EXIT_FAILURE);
  }

  return texture;
}

void drawTexture(Texture texture, int x, int y, int width, int height) {
  DrawTexturePro(
    texture, 
    (Rectangle){.height = texture.height, .width = texture.width, .x = 0, .y = 0},
    (Rectangle){.height = height, .width = width, .x = x, .y = y},
    (Vector2){.x = 0, .y = 0},
    0,
    WHITE
  );
}

void drawFromTileAtlas(Texture texture, int x, int y, int x2, int y2) {
  DrawTexturePro(
    texture, 
    (Rectangle){.height = 8, .width = 8, .x = x2, .y = y2},
    (Rectangle){.height = 64, .width = 64, .x = x, .y = y},
    (Vector2){.x = 0, .y = 0},
    0,
    WHITE
  );
}

void drawTile(Tile tile, int x, int y, TileDirection dir) {
  if (dir == TOP_1) drawFromTileAtlas(tile_atlas, x, y, tile.x + 0, tile.y + 0);
  if (dir == TOP_2) drawFromTileAtlas(tile_atlas, x, y, tile.x + 8, tile.y + 0);
  if (dir == TOP_3) drawFromTileAtlas(tile_atlas, x, y, tile.x + 16, tile.y + 0);
  if (dir == TOP_4) drawFromTileAtlas(tile_atlas, x, y, tile.x + 24, tile.y + 0);
}

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60);

  tile_atlas = loadTexture("textures/tile-atlas.png");
  Tile cement = ((Tile){.x = 16, .y = 16});

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);


    drawTile(cement, 0, 0, TOP_1);
    drawTile(cement, 100, 0, TOP_2);
    drawTile(cement, 0, 100, TOP_3);
    drawTile(cement, 100, 100, TOP_4);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
