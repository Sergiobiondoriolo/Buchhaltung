extends Node2D
## Steuert den Raum: Klicks, Maus-Hover, Meldungen und Inventar-Anzeige.

@onready var player: Player = $Player
@onready var floor_area: Polygon2D = $Floor
@onready var door: Hotspot = $Door
@onready var message_label: Label = $UI/Message
@onready var hover_label: Label = $UI/Hover
@onready var inventory_label: Label = $UI/Inventory
@onready var message_timer: Timer = $UI/MessageTimer

var _pending: Hotspot = null


func _ready() -> void:
	Game.message_shown.connect(_on_message)
	Game.inventory_changed.connect(_update_inventory)
	player.arrived.connect(_on_player_arrived)
	door.solved.connect(_on_door_solved)
	message_timer.timeout.connect(func() -> void: message_label.text = "")
	_update_inventory()
	Game.say("Wo bin ich hier? Ich sollte mich umsehen.")


func _process(_delta: float) -> void:
	var hotspot := _hotspot_at(get_global_mouse_position())
	hover_label.visible = hotspot != null
	if hotspot:
		hover_label.text = hotspot.display_name
		hover_label.position = get_viewport().get_mouse_position() + Vector2(18, 18)
	Input.set_default_cursor_shape(Input.CURSOR_POINTING_HAND if hotspot else Input.CURSOR_ARROW)


func _unhandled_input(event: InputEvent) -> void:
	if not (event is InputEventMouseButton and event.pressed and event.button_index == MOUSE_BUTTON_LEFT):
		return
	var point := get_global_mouse_position()
	var hotspot := _hotspot_at(point)
	if hotspot:
		_pending = hotspot
		player.walk_to(hotspot.get_walk_target())
	elif _is_on_floor(point):
		_pending = null
		player.walk_to(point)


func _hotspot_at(point: Vector2) -> Hotspot:
	var nodes := get_tree().get_nodes_in_group("hotspots")
	# Rückwärts, damit das zuoberst gezeichnete Objekt gewinnt.
	for i in range(nodes.size() - 1, -1, -1):
		var hotspot := nodes[i] as Hotspot
		if hotspot and hotspot.contains(point):
			return hotspot
	return null


func _is_on_floor(point: Vector2) -> bool:
	return Geometry2D.is_point_in_polygon(floor_area.to_local(point), floor_area.polygon)


func _on_player_arrived() -> void:
	if _pending and is_instance_valid(_pending):
		var hotspot := _pending
		_pending = null
		hotspot.interact()


func _on_message(text: String) -> void:
	message_label.text = text
	message_timer.start(4.0)


func _update_inventory() -> void:
	var names: Array[String] = []
	for item_name in Game.inventory.values():
		names.append(str(item_name))
	inventory_label.text = "Inventar: " + (", ".join(names) if names.size() > 0 else "leer")


func _on_door_solved() -> void:
	door.color = Color(0.08, 0.06, 0.05)
	door.display_name = "Offene Tür"
	door.description = "Frische Luft! Ende der Demo – baue hier den nächsten Raum."
