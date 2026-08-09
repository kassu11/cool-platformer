package engine
import "core:c"
import rl "vendor:raylib"

interval: f32 = 1 / 20.0
current: f32 = 0.0

lastMovement := 0
sprintTime: f32 = 0.0

running_speed: f32 = 500
walking_speed: f32 = 100

update :: proc(deltaTime: f32, player: ^Player) {
	current += deltaTime
	if current < interval {
		return
	}

	player.prevX = player.x
	player.prevY = player.y

	for ; current >= interval; current -= interval {
		// Execute physics
		if lastMovement == 0 {
			sprintTime = 0
		}

		if rl.IsKeyDown(rl.KeyboardKey.A) {
			if lastMovement == 1 || lastMovement == 0 {
				sprintTime += interval
			} else {
				sprintTime = 0
			}
			if sprintTime > 0.1 {
				player.x -= cast(c.int)(running_speed * interval)
			}
			player.x -= cast(c.int)(walking_speed * interval)
			lastMovement = 1
		}

		if rl.IsKeyDown(rl.KeyboardKey.D) {
			if lastMovement == 2 || lastMovement == 0 {
				sprintTime += interval
			} else {
				sprintTime = 0
			}
			if sprintTime > 0.1 {
				player.x += cast(c.int)(running_speed * interval)
			}
			player.x += cast(c.int)(walking_speed * interval)
			lastMovement = 2
		}

		if rl.IsKeyUp(rl.KeyboardKey.D) && rl.IsKeyUp(rl.KeyboardKey.A) {
			lastMovement = 0
		}
	}
}
