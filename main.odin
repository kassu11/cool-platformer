package main

import "core:fmt"
import rl "vendor:raylib"

main :: proc() {
	fmt.println("Hellope!")

	screenWidth: i32 = 800
	screenHeight: i32 = 450

	rl.InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window")

	rl.SetTargetFPS(60)

	for !rl.WindowShouldClose() {
		rl.BeginDrawing()

		rl.ClearBackground(rl.RAYWHITE)

		rl.EndDrawing()
	}

	rl.CloseWindow()
}
