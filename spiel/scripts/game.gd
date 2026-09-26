extends Node
## Globaler Spielzustand (Autoload "Game"): Inventar und Meldungen.

signal inventory_changed
signal message_shown(text: String)

## item_id -> Anzeigename
var inventory: Dictionary = {}


func add_item(item_id: String, display_name: String) -> void:
	inventory[item_id] = display_name
	inventory_changed.emit()


func remove_item(item_id: String) -> void:
	inventory.erase(item_id)
	inventory_changed.emit()


func has_item(item_id: String) -> bool:
	return inventory.has(item_id)


func say(text: String) -> void:
	message_shown.emit(text)
