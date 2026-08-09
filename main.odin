package main

import "core:fmt"
import rl "vendor:raylib"

import "engine"

player := engine.Player {
	x = 150,
	y = 150,
}

main :: proc() {
	fmt.println("Hellope!")

	screenWidth: i32 = 800
	screenHeight: i32 = 450

	rl.InitWindow(screenWidth, screenHeight, "Platformet")

	rl.SetTargetFPS(500)

	for (!rl.WindowShouldClose()) {
		rl.BeginDrawing()
		engine.update(rl.GetFrameTime(), &player)

		engine.draw(&player)

		rl.ClearBackground(rl.RAYWHITE)

		rl.EndDrawing()
	}

	rl.CloseWindow()
}
