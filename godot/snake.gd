extends Node2D

var x = 0
var y = 0
var direction = 0
var move_timer = 0
var time_to_move = 5
var speed = 20

func _ready():
	set_fixed_process(true)

func _fixed_process(delta):
	# Move
	if direction != 0:
		move_timer = move_timer + 1
		move()
	# Player input
	if Input.is_action_pressed("ui_right"):
		direction = 6
	elif Input.is_action_pressed("ui_left"):
		direction = 4
	elif Input.is_action_pressed("ui_down"):
		direction = 2
	elif Input.is_action_pressed("ui_up"):
		direction = 8
		
func move():
	if move_timer >= time_to_move:
		if direction == 2:
			y = y + 1
		elif direction == 4:
			x = x - 1
		elif direction == 6:
			x = x + 1
		elif direction == 8:
			y = y -1
		set_pos(Vector2(x * speed, y * speed))
		move_timer = 0
