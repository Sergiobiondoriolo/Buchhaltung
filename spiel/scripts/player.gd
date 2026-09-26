class_name Player
extends Node2D
## Spielfigur: läuft zu dem Punkt, auf den geklickt wurde.
## Der Ursprung (0,0) ist zwischen den Füßen.

signal arrived

@export var speed := 260.0

var _target := Vector2.ZERO
var _moving := false


func _ready() -> void:
	_target = position


func walk_to(point: Vector2) -> void:
	_target = point
	_moving = true


func _process(delta: float) -> void:
	if not _moving:
		return
	if _target.x != position.x:
		scale.x = 1.0 if _target.x > position.x else -1.0
	position = position.move_toward(_target, speed * delta)
	if position.distance_to(_target) < 1.0:
		_moving = false
		arrived.emit()


func _draw() -> void:
	# Platzhalter-Figur – später durch ein Sprite2D/AnimatedSprite2D ersetzen.
	draw_rect(Rect2(-14, -40, 10, 40), Color(0.2, 0.2, 0.35))  # Bein
	draw_rect(Rect2(4, -40, 10, 40), Color(0.2, 0.2, 0.35))    # Bein
	draw_rect(Rect2(-18, -95, 36, 58), Color(0.75, 0.2, 0.2))  # Oberkörper
	draw_circle(Vector2(0, -112), 17, Color(0.95, 0.8, 0.65))  # Kopf
	draw_circle(Vector2(7, -115), 3, Color.BLACK)              # Auge (Blickrichtung)
