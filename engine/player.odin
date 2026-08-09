package engine

import "core:c"
import rl "vendor:raylib"

Player :: struct {
	x, y:         c.int,
	prevX, prevY: c.int,
}

test :: proc(a: int) -> int {
	return a + 5
}

draw :: proc(player: ^Player) {
	dx := cast(f32)(player.x - player.prevX)
	dy := cast(f32)(player.y - player.prevY)

	rl.DrawRectangle(
		player.prevX + cast(i32)(dx * (current / interval)),
		player.prevY + cast(i32)(dy * (current / interval)),
		64,
		64,
		rl.RED,
	)
}
