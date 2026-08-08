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
                                                         \
  TILE_DIRECTION_TYPE(BLOCK_1)                           \
                                                         \
  TILE_DIRECTION_TYPE(TOP_1)                             \
  TILE_DIRECTION_TYPE(TOP_2)                             \
  TILE_DIRECTION_TYPE(TOP_3)                             \
  TILE_DIRECTION_TYPE(TOP_4)                             \
                                                         \
  TILE_DIRECTION_TYPE(BOTTOM_1)                          \
  TILE_DIRECTION_TYPE(BOTTOM_2)                          \
  TILE_DIRECTION_TYPE(BOTTOM_3)                          \
  TILE_DIRECTION_TYPE(BOTTOM_4)                          \
                                                         \
  TILE_DIRECTION_TYPE(LEFT_1)                            \
  TILE_DIRECTION_TYPE(LEFT_2)                            \
  TILE_DIRECTION_TYPE(LEFT_3)                            \
  TILE_DIRECTION_TYPE(LEFT_4)                            \
                                                         \
  TILE_DIRECTION_TYPE(RIGHT_1)                           \
  TILE_DIRECTION_TYPE(RIGHT_2)                           \
  TILE_DIRECTION_TYPE(RIGHT_3)                           \
  TILE_DIRECTION_TYPE(RIGHT_4)                           \
                                                         \
  TILE_DIRECTION_TYPE(HORIZONTAL_1)                      \
  TILE_DIRECTION_TYPE(HORIZONTAL_2)                      \
  TILE_DIRECTION_TYPE(HORIZONTAL_3)                      \
  TILE_DIRECTION_TYPE(HORIZONTAL_4)                      \
                                                         \
  TILE_DIRECTION_TYPE(VERTICAL_1)                        \
  TILE_DIRECTION_TYPE(VERTICAL_2)                        \
  TILE_DIRECTION_TYPE(VERTICAL_3)                        \
  TILE_DIRECTION_TYPE(VERTICAL_4)                        \
                                                         \
  TILE_DIRECTION_TYPE(TOP_END_1)                         \
  TILE_DIRECTION_TYPE(TOP_END_2)                         \
  TILE_DIRECTION_TYPE(TOP_END_3)                         \
  TILE_DIRECTION_TYPE(TOP_END_4)                         \
                                                         \
  TILE_DIRECTION_TYPE(BOTTOM_END_1)                      \
  TILE_DIRECTION_TYPE(BOTTOM_END_2)                      \
  TILE_DIRECTION_TYPE(BOTTOM_END_3)                      \
  TILE_DIRECTION_TYPE(BOTTOM_END_4)                      \
                                                         \
  TILE_DIRECTION_TYPE(LEFT_END_1)                        \
  TILE_DIRECTION_TYPE(LEFT_END_2)                        \
  TILE_DIRECTION_TYPE(LEFT_END_3)                        \
  TILE_DIRECTION_TYPE(LEFT_END_4)                        \
                                                         \
  TILE_DIRECTION_TYPE(RIGHT_END_1)                       \
  TILE_DIRECTION_TYPE(RIGHT_END_2)                       \
  TILE_DIRECTION_TYPE(RIGHT_END_3)                       \
  TILE_DIRECTION_TYPE(RIGHT_END_4)                       \
                                                         \
  TILE_DIRECTION_TYPE(TILE_TYPE_MAX) 

typedef enum {
    FOREACH_TILE_DIRECTION_TYPE(ENUM_GEN)
} TileDirection;

const char* tile_direction_strings[] = {
  FOREACH_TILE_DIRECTION_TYPE(STRING_GEN)
};

const int TILE_SIZE = 48;

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
  Vector2 origin = { .x = 0, .y = 0 };
  float rotation = 0;
  Color tint = { .r = 255, .g = 255, .b = 255, .a = alpha };

  DrawTexturePro(texture, source, destination, origin, rotation, tint);

}

void drawTile(Tile tile, int alpha, int x, int y, TileDirection dir) {

  if (dir == BLOCK_1)       drawFromTileAtlas(tile, alpha, x, y, 0, 0);

  if (dir == TOP_1)         drawFromTileAtlas(tile, alpha, x, y, 0, 0);
  if (dir == TOP_2)         drawFromTileAtlas(tile, alpha, x, y, 1, 0);
  if (dir == TOP_3)         drawFromTileAtlas(tile, alpha, x, y, 2, 0);
  if (dir == TOP_4)         drawFromTileAtlas(tile, alpha, x, y, 3, 0);

  if (dir == BOTTOM_1)      drawFromTileAtlas(tile, alpha, x, y, 0, 1);
  if (dir == BOTTOM_2)      drawFromTileAtlas(tile, alpha, x, y, 1, 1);
  if (dir == BOTTOM_3)      drawFromTileAtlas(tile, alpha, x, y, 2, 1);
  if (dir == BOTTOM_4)      drawFromTileAtlas(tile, alpha, x, y, 3, 1);

  if (dir == LEFT_1)        drawFromTileAtlas(tile, alpha, x, y, 0, 2);
  if (dir == LEFT_2)        drawFromTileAtlas(tile, alpha, x, y, 1, 2);
  if (dir == LEFT_3)        drawFromTileAtlas(tile, alpha, x, y, 2, 2);
  if (dir == LEFT_4)        drawFromTileAtlas(tile, alpha, x, y, 3, 2);

  if (dir == RIGHT_1)       drawFromTileAtlas(tile, alpha, x, y, 0, 3);
  if (dir == RIGHT_2)       drawFromTileAtlas(tile, alpha, x, y, 1, 3);
  if (dir == RIGHT_3)       drawFromTileAtlas(tile, alpha, x, y, 2, 3);
  if (dir == RIGHT_4)       drawFromTileAtlas(tile, alpha, x, y, 3, 3);

  if (dir == HORIZONTAL_1)  drawFromTileAtlas(tile, alpha, x, y, 0, 4);
  if (dir == HORIZONTAL_2)  drawFromTileAtlas(tile, alpha, x, y, 1, 4);
  if (dir == HORIZONTAL_3)  drawFromTileAtlas(tile, alpha, x, y, 2, 4);
  if (dir == HORIZONTAL_4)  drawFromTileAtlas(tile, alpha, x, y, 3, 4);

  if (dir == VERTICAL_1)    drawFromTileAtlas(tile, alpha, x, y, 0, 5);
  if (dir == VERTICAL_2)    drawFromTileAtlas(tile, alpha, x, y, 1, 5);
  if (dir == VERTICAL_3)    drawFromTileAtlas(tile, alpha, x, y, 2, 5);
  if (dir == VERTICAL_4)    drawFromTileAtlas(tile, alpha, x, y, 3, 5);

  if (dir == TOP_END_1)     drawFromTileAtlas(tile, alpha, x, y, 0, 6);
  if (dir == TOP_END_2)     drawFromTileAtlas(tile, alpha, x, y, 1, 6);
  if (dir == TOP_END_3)     drawFromTileAtlas(tile, alpha, x, y, 2, 6);
  if (dir == TOP_END_4)     drawFromTileAtlas(tile, alpha, x, y, 3, 6);

  if (dir == BOTTOM_END_1)  drawFromTileAtlas(tile, alpha, x, y, 0, 7);
  if (dir == BOTTOM_END_2)  drawFromTileAtlas(tile, alpha, x, y, 1, 7);
  if (dir == BOTTOM_END_3)  drawFromTileAtlas(tile, alpha, x, y, 2, 7);
  if (dir == BOTTOM_END_4)  drawFromTileAtlas(tile, alpha, x, y, 3, 7);

  if (dir == LEFT_END_1)    drawFromTileAtlas(tile, alpha, x, y, 0, 8);
  if (dir == LEFT_END_2)    drawFromTileAtlas(tile, alpha, x, y, 1, 8);
  if (dir == LEFT_END_3)    drawFromTileAtlas(tile, alpha, x, y, 2, 8);
  if (dir == LEFT_END_4)    drawFromTileAtlas(tile, alpha, x, y, 3, 8);

  if (dir == RIGHT_END_1)   drawFromTileAtlas(tile, alpha, x, y, 0, 9);
  if (dir == RIGHT_END_2)   drawFromTileAtlas(tile, alpha, x, y, 1, 9);
  if (dir == RIGHT_END_3)   drawFromTileAtlas(tile, alpha, x, y, 2, 9);
  if (dir == RIGHT_END_4)   drawFromTileAtlas(tile, alpha, x, y, 3, 9);

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

TileDirection rotateTile(TileDirection dir, bool reverseRotation) {
  switch(dir) {
    case TOP_1:
    case TOP_2:
    case TOP_3:
    case TOP_4: 
      return reverseRotation ? LEFT_1 : RIGHT_1;
    case RIGHT_1:
    case RIGHT_2:
    case RIGHT_3:
    case RIGHT_4: 
      return reverseRotation ? TOP_1 : BOTTOM_1;
    case BOTTOM_1:
    case BOTTOM_2:
    case BOTTOM_3:
    case BOTTOM_4: 
      return reverseRotation ? RIGHT_1 : LEFT_1;
    case LEFT_1:
    case LEFT_2:
    case LEFT_3:
    case LEFT_4: 
      return reverseRotation ? BOTTOM_1 : TOP_1;
    case HORIZONTAL_1:
    case HORIZONTAL_2:
    case HORIZONTAL_3:
    case HORIZONTAL_4: 
      return VERTICAL_1;
    case VERTICAL_1:
    case VERTICAL_2:
    case VERTICAL_3:
    case VERTICAL_4: 
      return HORIZONTAL_1;
    case TOP_END_1:
    case TOP_END_2:
    case TOP_END_3:
    case TOP_END_4: 
      return reverseRotation ? LEFT_END_1 : RIGHT_END_1;
    case RIGHT_END_1:
    case RIGHT_END_2:
    case RIGHT_END_3:
    case RIGHT_END_4: 
      return reverseRotation ? TOP_END_1 : BOTTOM_END_1;
    case BOTTOM_END_1:
    case BOTTOM_END_2:
    case BOTTOM_END_3:
    case BOTTOM_END_4: 
      return reverseRotation ? RIGHT_END_1 : LEFT_END_1;
    case LEFT_END_1:
    case LEFT_END_2:
    case LEFT_END_3:
    case LEFT_END_4: 
      return reverseRotation ? BOTTOM_END_1 : TOP_END_1;
    case VOID:
    case TILE_TYPE_MAX:
    case BLOCK_1: 
      return dir;
  }

  return dir;
}

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(500);

  Texture2D tile_atlas = loadTexture("textures/tile-atlas.png");
  Tile cement = ((Tile){.x = 16, .y = 16, .texture = tile_atlas });

  Texture2D block_1 = loadTexture("textures/block-1.png");
  Tile customTiles = ((Tile){.x = 0, .y = 0, .texture = block_1 });

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
        drawTile(customTiles, 255, info.x, info.y, info.dir);
      }
    }

    drawTile(customTiles, 100, item.x, item.y, item.dir);

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      // Append tile
      if (foundIndex == -1) {
        append(editorTiles, item);
      }
      // Replace old tile
      else {
        editorTiles.items[foundIndex] = item;
      }

      // Randomize next tile variation
      editorDir = changeTextureVariation(editorDir);
    }
    else if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
      if (foundIndex != -1) {
        editorDir = editorTiles.items[foundIndex].dir;
      } else {
        editorDir = VOID;
      }
    }

    if (IsKeyPressed(KEY_P)) {
      for (int i = 0; i < editorTiles.count; i++) {
        TileInfo info = editorTiles.items[i];
        if (info.dir != VOID) {
          printf("drawTile(customTiles, 255, %d, %d, %s);\n", info.x, info.y, tile_direction_strings[info.dir]);
        }
      }
    }

    else if (IsKeyPressed(KEY_R)) {
      editorDir = rotateTile(editorDir, IsKeyDown(KEY_LEFT_SHIFT));
    }

    else if (IsKeyPressed(KEY_ZERO))  editorDir = VOID;
    else if (IsKeyPressed(KEY_ONE))   editorDir = TOP_1;
    else if (IsKeyPressed(KEY_TWO))  editorDir = HORIZONTAL_1;
    else if (IsKeyPressed(KEY_THREE)) editorDir = TOP_END_1;

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
