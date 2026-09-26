@tool
class_name Hotspot
extends Node2D
## Anklickbares Objekt im Raum.
## - Nur Beschreibung: wird angeschaut.
## - can_pick_up: landet im Inventar.
## - required_item: braucht einen Gegenstand aus dem Inventar (Rätsel).

signal interacted
signal solved

@export var display_name := "Gegenstand"
@export_multiline var description := "Nichts Besonderes."
## Größe der anklickbaren Fläche.
@export var size := Vector2(80, 80):
	set(value):
		size = value
		queue_redraw()
## Platzhalter-Farbe. Transparent machen, wenn ein Hintergrundbild das Objekt zeigt.
@export var color := Color(0.8, 0.6, 0.3):
	set(value):
		color = value
		queue_redraw()
## Wo die Figur stehen bleibt (relativ zum Objekt).
@export var walk_offset := Vector2(0, 60)

@export_group("Aufheben")
@export var can_pick_up := false
@export var item_id := ""

@export_group("Rätsel")
@export var required_item := ""
@export_multiline var solved_text := ""
@export_multiline var missing_text := ""
@export var consume_item := true

var is_solved := false


func _ready() -> void:
	if not Engine.is_editor_hint():
		add_to_group("hotspots")


func _draw() -> void:
	draw_rect(Rect2(-size / 2, size), color)
	if Engine.is_editor_hint():
		draw_rect(Rect2(-size / 2, size), Color.WHITE, false, 2.0)
		draw_circle(walk_offset, 6, Color.GREEN)


func contains(global_point: Vector2) -> bool:
	return Rect2(global_position - size / 2, size).has_point(global_point)


func get_walk_target() -> Vector2:
	return global_position + walk_offset


func interact() -> void:
	if required_item != "" and not is_solved:
		if Game.has_item(required_item):
			if consume_item:
				Game.remove_item(required_item)
			is_solved = true
			Game.say(solved_text)
			solved.emit()
		else:
			Game.say(missing_text if missing_text != "" else description)
		return

	if can_pick_up:
		Game.add_item(item_id if item_id != "" else String(name), display_name)
		Game.say("%s eingesteckt." % display_name)
		interacted.emit()
		queue_free()
		return

	Game.say(description)
	interacted.emit()
