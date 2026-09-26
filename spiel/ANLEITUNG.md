# KlickAbenteuer – Point-and-Click-Adventure mit Unreal Engine 5

## 1. Was dein PC braucht

| | Minimum | Empfohlen |
|---|---|---|
| System | Windows 10/11 64-bit | Windows 11 |
| Grafikkarte | GTX 1070 / RX 5700 (DirectX 12) | RTX 3060 oder besser |
| RAM | 16 GB | 32 GB |
| Speicher | ca. 150 GB frei (SSD!) | |

## 2. Programme herunterladen (einmalig)

1. **Epic Games Launcher**
   - Seite öffnen: https://www.unrealengine.com/download
   - Kostenloses Epic-Konto anlegen und den Launcher installieren.
2. **Unreal Engine 5 installieren**
   - Launcher starten → links auf **„Unreal Engine“** → oben auf **„Bibliothek“**.
   - Auf **„+“** neben „Engine-Versionen“ klicken und die neueste 5.x-Version wählen → **Installieren**.
   - Dauert je nach Internet 1–3 Stunden (~60–100 GB).
3. **Visual Studio 2022 Community** (kostenlos, nötig für C++)
   - https://visualstudio.microsoft.com/de/downloads/
   - Beim Installieren diese Workloads anhaken:
     - **„Spieleentwicklung mit C++“** (rechts zusätzlich „Unreal Engine-Installer“ und „Unreal Engine-Testadapter“ anhaken)
     - **„Desktopentwicklung mit C++“**
   - Unter „Einzelne Komponenten“: ein **.NET 8 SDK** oder neuer (für die Unreal-Build-Tools).

## 3. Projekt auf deinen PC holen

Neuen Ordner anlegen, z. B. `C:\Spiele\`, und dort das Repo klonen:

```
cd C:\Spiele
git clone https://github.com/sergiobiondoriolo/buchhaltung.git
cd buchhaltung
git checkout claude/upbeat-ramanujan-cr8wub
```

Das Spiel liegt dann in **`C:\Spiele\buchhaltung\spiel\`**.

> Kein Git? → https://git-scm.com/download/win installieren, oder auf GitHub
> „Code → Download ZIP“ und entpacken.

## 4. Projekt öffnen

1. Im Ordner `spiel\` **Rechtsklick auf `KlickAbenteuer.uproject`**
   → **„Switch Unreal Engine version…“** → deine installierte Version wählen.
2. **Doppelklick auf `KlickAbenteuer.uproject`**.
3. Frage „Module fehlen, jetzt bauen?“ → **Ja**. Der erste Build dauert ein paar Minuten.

## 5. Erstes Level bauen (ca. 10 Minuten)

1. **File → New Level → Basic** → speichern als `Content/Maps/Raum1`.
2. **Navigation für Klick-Laufen:** Oben „+“ (Quick Add) → *Volumes* → **Nav Mesh Bounds Volume**
   ins Level ziehen und so groß skalieren, dass es den Boden umschließt.
   Taste **P** zeigt den begehbaren Bereich grün an.
3. **Anklickbares Objekt:** Im *Place Actors*-Fenster nach **„Interactable Actor“** suchen und ins Level ziehen.
   Rechts im *Details*-Panel:
   - **Mesh** → Static Mesh auswählen (z. B. `Cube` oder ein Megascans-Objekt)
   - **Abenteuer → Display Name**: „Alte Truhe“
   - **Description**: „Sie ist verschlossen.“
4. **Rätsel bauen:**
   - Objekt A („Schlüssel“): `Can Pick Up` ✔, `Item Id` = `Schluessel`
   - Objekt B („Tür“): `Required Item Id` = `Schluessel`, `Solved Text` = „Die Tür knarrt auf!“,
     `Missing Item Text` = „Abgeschlossen. Ich brauche einen Schlüssel.“
5. **Edit → Project Settings → Maps & Modes** → *Editor Startup Map* und *Game Default Map* = `Raum1`.
6. Oben auf **▶ Play** klicken.

### Steuerung
- **Linksklick auf den Boden** → Figur läuft hin
- **Maus über Objekt** → Name erscheint, Cursor wird zur Hand
- **Linksklick auf Objekt** → Figur läuft hin und schaut es an, hebt es auf oder benutzt einen Gegenstand

## 6. Realistisch aussehen lassen

- **Fab / Quixel Megascans**: fotorealistische Objekte und Oberflächen, direkt im Editor über **Window → Fab**.
- **Lumen und Virtual Shadows** sind in `Config/DefaultEngine.ini` bereits eingeschaltet.
- **Spielfigur:** Content Browser → *Add → Blueprint Class* → Elternklasse **AdventureCharacter**.
  Dort unter *Mesh* eine Figur zuweisen (z. B. „Manny“ aus *Add Feature or Content Pack → Third Person*
  oder einen **MetaHuman**). Danach in einem eigenen GameMode-Blueprint als *Default Pawn* eintragen.
- **Eigene Aktionen:** Blueprint von *InteractableActor* anlegen und die Events
  **On Interacted** / **On Solved** nutzen (Tür-Animation, Sound, Levelwechsel …).

## 7. Projektstruktur

```
spiel/
├── KlickAbenteuer.uproject      ← Doppelklick zum Öffnen
├── Config/                      ← Grafik- und Spieleinstellungen
├── Content/                     ← Level, Modelle, Sounds (im Editor erstellt)
└── Source/KlickAbenteuer/
    ├── AdventureGameMode        ← verbindet alles
    ├── AdventureCharacter       ← Spielfigur + Kamera
    ├── AdventurePlayerController← Klick-Steuerung + Inventar
    ├── InteractableActor        ← anklickbare Objekte / Rätsel
    └── AdventureHUD             ← Texte auf dem Bildschirm
```

> Tipp: Unreal-Dateien (`.uasset`, `.umap`) werden schnell groß. Wenn du sie auf GitHub speichern willst,
> installiere **Git LFS** (https://git-lfs.com) und führe im Repo `git lfs track "*.uasset" "*.umap"` aus.
