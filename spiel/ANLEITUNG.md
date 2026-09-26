# KlickAbenteuer – Point-and-Click-Adventure mit Godot 4

## 1. Projekt auf deinen PC holen

**PowerShell** öffnen (Windows-Taste → „PowerShell“) und einfügen:

```powershell
winget install --id Git.Git -e
```

PowerShell **schließen und neu öffnen**, dann:

```powershell
New-Item -ItemType Directory -Force C:\Spiele | Out-Null
cd C:\Spiele
git clone -b claude/upbeat-ramanujan-cr8wub https://github.com/sergiobiondoriolo/buchhaltung.git
explorer C:\Spiele\buchhaltung\spiel
```

Beim ersten Mal kommt ein GitHub-Login → anmelden.
Das Spiel liegt dann in **`C:\Spiele\buchhaltung\spiel\`**.

Später neue Änderungen holen:

```powershell
cd C:\Spiele\buchhaltung
git pull
```

## 2. In Godot öffnen

1. Godot starten → **„Importieren“** → Ordner `C:\Spiele\buchhaltung\spiel` wählen
   (bzw. die Datei `project.godot`) → **„Importieren & Bearbeiten“**.
2. Oben rechts auf **▶ (F5)** klicken → das Spiel startet.

## 3. Steuerung

- **Linksklick auf den Boden** → Figur läuft hin
- **Maus über Objekt** → Name erscheint, Cursor wird zur Hand
- **Linksklick auf Objekt** → Figur läuft hin und schaut es an, hebt es auf oder benutzt einen Gegenstand

Das Demo-Rätsel: Die Tür ist abgeschlossen → Schlüssel neben dem Teppich finden → Tür öffnen.

## 4. Projektstruktur

```
spiel/
├── project.godot        ← Projektdatei
├── scenes/
│   └── main.tscn        ← der Raum (Wand, Boden, Objekte, Figur, Textanzeige)
└── scripts/
    ├── game.gd          ← Inventar + Meldungen (global als „Game“ verfügbar)
    ├── main.gd          ← Klicks, Maus-Hover, Anzeige
    ├── player.gd        ← Spielfigur, läuft zum Klickpunkt
    └── hotspot.gd       ← anklickbare Objekte / Rätsel
```

## 5. Eigene Objekte hinzufügen

1. `scenes/main.tscn` öffnen.
2. Rechtsklick auf **Main** → **Node hinzufügen** → **Node2D**.
3. Im Inspektor unten bei **Script** → `res://scripts/hotspot.gd` reinziehen.
4. Rechts im Inspektor einstellen:
   - **Display Name**: „Truhe“
   - **Description**: „Sie ist verschlossen.“
   - **Size**: Größe der Klickfläche
   - **Walk Offset**: wo die Figur stehen bleibt (grüner Punkt im Editor)
   - Aufheben: **Can Pick Up** ✔ und **Item Id** (z. B. `hammer`)
   - Rätsel: **Required Item** = Item Id des nötigen Gegenstands, dazu **Solved Text** und **Missing Text**

## 6. Richtige Grafik statt bunter Kästen

- **Hintergrund:** ein gemaltes Bild (1280×720) als **Sprite2D** ganz oben in die Szene legen.
  Die Farben der Hotspots dann auf transparent stellen (Alpha = 0).
- **Figur:** unter `Player` ein **AnimatedSprite2D** mit Lauf-Animation einfügen und in
  `player.gd` die Funktion `_draw()` löschen.
- Kostenlose Grafiken: https://itch.io/game-assets/free/tag-point-and-click
