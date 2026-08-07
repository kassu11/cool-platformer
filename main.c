#include "raylib.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// I have honestly no idea how this magic works: https://www.reddit.com/r/C_Programming/comments/1f2rkvt/convert_c_enum_to_its_string_representation/
// But it makes enums as string, and this is used when printing values in editor
#define ENUM_GEN(ENUM) ENUM,
#define STRING_GEN(STRING) #STRING,

#define FOREACH_TILE_DIRECTION_TYPE(TILE_DIRECTION_TYPE) \
  TILE_DIRECTION_TYPE(VOID)                              \
  TILE_DIRECTION_TYPE(TOP_1)                             \
  TILE_DIRECTION_TYPE(TOP_2)                             \
  TILE_DIRECTION_TYPE(TOP_3)                             \
  TILE_DIRECTION_TYPE(TOP_4)                             \
  TILE_DIRECTION_TYPE(BOTTOM_1)                          \
  TILE_DIRECTION_TYPE(BOTTOM_2)                          \
  TILE_DIRECTION_TYPE(BOTTOM_3)                          \
  TILE_DIRECTION_TYPE(BOTTOM_4)                          \
  TILE_DIRECTION_TYPE(LEFT_1)                            \
  TILE_DIRECTION_TYPE(LEFT_2)                            \
  TILE_DIRECTION_TYPE(LEFT_3)                            \
  TILE_DIRECTION_TYPE(LEFT_4)                            \
  TILE_DIRECTION_TYPE(RIGHT_1)                           \
  TILE_DIRECTION_TYPE(RIGHT_2)                           \
  TILE_DIRECTION_TYPE(RIGHT_3)                           \
  TILE_DIRECTION_TYPE(RIGHT_4)                           \
  TILE_DIRECTION_TYPE(CORNER_1)                          \
  TILE_DIRECTION_TYPE(CORNER_2)                          \
  TILE_DIRECTION_TYPE(CORNER_3)                          \
  TILE_DIRECTION_TYPE(CORNER_4)                          \
  TILE_DIRECTION_TYPE(TILE_TYPE_MAX) 

typedef enum {
    FOREACH_TILE_DIRECTION_TYPE(ENUM_GEN)
} TileDirection;

const char* tile_direction_strings[] = {
  FOREACH_TILE_DIRECTION_TYPE(STRING_GEN)
};

const int TILE_SIZE = 48;

Texture2D tile_atlas;
typedef struct {
  int x;
  int y;
  Texture2D texture;
} Tile;

typedef struct {
  TileDirection dir;
  int x;
  int y;
} TileInfo;



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

  Rectangle source = { .height = texture.height, .width = texture.width, .x = 0, .y = 0 };
  Rectangle destination = { .height = height, .width = width, .x = x, .y = y };
  Vector2 origin = { .x = 0, .y = 0 };
  float rotation = 0;
  Color tint = WHITE;

  DrawTexturePro(texture, source, destination, origin, rotation, tint);

}

void drawFromTileAtlas(Tile tile, int alpha, int x, int y, int dx, int dy) {

  Texture2D texture = tile.texture;
  Rectangle source = { .height = 8, .width = 8, .x = tile.x + dx * 8, .y = tile.y + dy * 8 };
  Rectangle destination = { .height = TILE_SIZE, .width = TILE_SIZE, .x = x, .y = y };
  Vector2 origin = {.x = 0, .y = 0};
  float rotation = 0;
  Color tint = { .r = 255, .g = 255, .b = 255, .a = alpha };

  DrawTexturePro(texture, source, destination, origin, rotation, tint);

}

void drawTile(Tile tile, int alpha, int x, int y, TileDirection dir) {

  if (dir == TOP_1)    drawFromTileAtlas(tile, alpha, x, y, 0, 0);
  if (dir == TOP_2)    drawFromTileAtlas(tile, alpha, x, y, 1, 0);
  if (dir == TOP_3)    drawFromTileAtlas(tile, alpha, x, y, 2, 0);
  if (dir == TOP_4)    drawFromTileAtlas(tile, alpha, x, y, 3, 0);

  if (dir == BOTTOM_1) drawFromTileAtlas(tile, alpha, x, y, 0, 1);
  if (dir == BOTTOM_2) drawFromTileAtlas(tile, alpha, x, y, 1, 1);
  if (dir == BOTTOM_3) drawFromTileAtlas(tile, alpha, x, y, 2, 1);
  if (dir == BOTTOM_4) drawFromTileAtlas(tile, alpha, x, y, 3, 1);

  if (dir == LEFT_1)   drawFromTileAtlas(tile, alpha, x, y, 0, 2);
  if (dir == LEFT_2)   drawFromTileAtlas(tile, alpha, x, y, 1, 2);
  if (dir == LEFT_3)   drawFromTileAtlas(tile, alpha, x, y, 2, 2);
  if (dir == LEFT_4)   drawFromTileAtlas(tile, alpha, x, y, 3, 2);

  if (dir == RIGHT_1)  drawFromTileAtlas(tile, alpha, x, y, 0, 3);
  if (dir == RIGHT_2)  drawFromTileAtlas(tile, alpha, x, y, 1, 3);
  if (dir == RIGHT_3)  drawFromTileAtlas(tile, alpha, x, y, 2, 3);
  if (dir == RIGHT_4)  drawFromTileAtlas(tile, alpha, x, y, 3, 3);

}

typedef struct {
  TileInfo *items;
  size_t count;
  size_t capacity;
} Tiles;

#define append(array, value)\
  do {\
    if (array.count >= array.capacity) {\
      if (array.capacity == 0) array.capacity = 256;\
      else array.capacity *= 2;\
      array.items = realloc(array.items, array.capacity * sizeof(*array.items));\
    }\
    array.items[array.count++] = value;\
  } while(0)


int lastTextureChangeDir = 1;
TileDirection changeTextureVariation(TileDirection dir) {
  TileDirection next = dir + lastTextureChangeDir;

  if (next > -1 && tile_direction_strings[dir][0] == tile_direction_strings[next][0]) {
    return next;
  }

  lastTextureChangeDir *= -1;
  next = dir + lastTextureChangeDir;
  if (next < TILE_TYPE_MAX && tile_direction_strings[dir][0] == tile_direction_strings[next][0]) {
    return next;
  }

  return dir;
}

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60);

  tile_atlas = loadTexture("textures/tile-atlas.png");
  Tile cement = ((Tile){.x = 16, .y = 16, .texture = tile_atlas });

  TileDirection editorDir = TOP_1;
  Tiles editorTiles = {0};

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    int x = GetMouseX() / TILE_SIZE * TILE_SIZE;
    int y = GetMouseY() / TILE_SIZE * TILE_SIZE;
    TileInfo item = {.x = x, .y = y, .dir = editorDir};

    int foundIndex = -1;
    for (int i = 0; i < editorTiles.count; i++) {
      TileInfo info = editorTiles.items[i];
      if (item.x == info.x && item.y == info.y) {
        foundIndex = i;
      } else {
        drawTile(cement, 255, info.x, info.y, info.dir);
      }
    }

    drawTile(cement, 100, item.x, item.y, item.dir);

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      if (foundIndex == -1) {
        append(editorTiles, item);
      } else {
        editorTiles.items[foundIndex] = item;
      }
      editorDir = changeTextureVariation(editorDir);
    }

    if (IsKeyPressed(KEY_P)) {
      for (int i = 0; i < editorTiles.count; i++) {
        TileInfo info = editorTiles.items[i];
        if (info.dir != VOID) {
          printf("drawTile(cement, 255, %d, %d, %s);\n", info.x, info.y, tile_direction_strings[info.dir]);
        }
      }
    }

    else if (IsKeyPressed(KEY_ZERO))  editorDir = VOID;
    else if (IsKeyPressed(KEY_ONE))   editorDir = TOP_1;
    else if (IsKeyPressed(KEY_TWO))   editorDir = RIGHT_1;
    else if (IsKeyPressed(KEY_THREE)) editorDir = BOTTOM_1;
    else if (IsKeyPressed(KEY_FOUR))  editorDir = LEFT_1;

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
