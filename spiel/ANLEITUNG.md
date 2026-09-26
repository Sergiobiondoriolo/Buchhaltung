# KlickAbenteuer – Point-and-Click-Adventure mit Unreal Engine 5

## 1. Was dein PC braucht

| | Minimum | Empfohlen |
|---|---|---|
| System | Windows 10/11 64-bit | Windows 11 |
| Grafikkarte | GTX 1070 / RX 5700 (DirectX 12) | RTX 3060 oder besser |
| RAM | 16 GB | 32 GB |
| Speicher | ca. 150 GB frei (SSD!) | |

## 2. Programme herunterladen (einmalig)

1. **Epic Games Launcher**: https://www.unrealengine.com/download
2. **Unreal Engine 5.8** installieren
   - Launcher → links **„Unreal Engine“** → oben **„Bibliothek“** → gelber Knopf **„Engine installieren“**.
   - Das Projekt ist auf **5.8** eingestellt.
   - **Fab UE Plugin** → „In Engine installieren“ (für fotorealistische Modelle). **Quixel Bridge** brauchst du nicht, es wurde durch Fab ersetzt.
3. **Git + Visual Studio 2022** (für C++): **PowerShell** öffnen (Windows-Taste → „PowerShell“) und einfügen:

   ```powershell
   winget install --id Git.Git -e
   winget install --id Microsoft.VisualStudio.2022.Community -e --override "--passive --wait --includeRecommended --add Microsoft.VisualStudio.Workload.NativeGame --add Microsoft.VisualStudio.Workload.NativeDesktop --add Microsoft.VisualStudio.Workload.ManagedDesktop"
   ```

   Bei Fragen mit **J** bzw. **Y** bestätigen. Visual Studio ist ca. 10–20 GB groß.

## 3. Projektordner anlegen (automatisch)

Wenn Git installiert ist: **PowerShell schließen und neu öffnen**, dann einfügen:

```powershell
New-Item -ItemType Directory -Force C:\Spiele | Out-Null
cd C:\Spiele
git clone -b claude/upbeat-ramanujan-cr8wub https://github.com/sergiobiondoriolo/buchhaltung.git
explorer C:\Spiele\buchhaltung\spiel
```

Beim ersten Mal öffnet sich ein GitHub-Login-Fenster → anmelden.
Danach öffnet sich der Ordner **`C:\Spiele\buchhaltung\spiel\`** mit dem Spiel.

Später neue Änderungen holen:

```powershell
cd C:\Spiele\buchhaltung
git pull
```

## 4. Projekt öffnen (wenn Engine + Visual Studio fertig sind)

1. Im Ordner `spiel\` **Doppelklick auf `KlickAbenteuer.uproject`**.
2. Frage „Module fehlen, jetzt bauen?“ → **Ja**. Der erste Build dauert ein paar Minuten.
3. Falls nach der Engine-Version gefragt wird: **5.8** wählen.

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
