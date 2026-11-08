# UnrealSC

Unreal Engine 5 C++ RTS presentation prototype with the longer-term goal of studying faithful Brood War gameplay behavior using a separate simulation process.

**Status:** Foundation source code only. UE5 compilation and runtime have **not** yet been tested. No simulation bridge is implemented yet.

## Quick start (Windows)
1. Install Unreal Engine 5.5+ and the matching Visual Studio C++ toolchain (Desktop development with C++ and Game development with C++).
2. Clone this repository and right-click `UnrealSC.uproject` → **Generate Visual Studio project files** (or open the project using the Unreal Editor).
3. Compile the **UnrealSCEditor** target and open the project.
4. Create a **Basic** level if the editor opens with an empty default; press Play and test **WASD** pan and **mouse wheel** zoom. Input currently uses classic axis bindings for minimal setup.

The initial game mode uses a native C++ RTS camera pawn and player controller. There are no game units, selection, terrain importer, external engine or packaged builds yet.

## Architecture
See [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) and [docs/ROADMAP.md](docs/ROADMAP.md).

## Legal / assets
Not affiliated with Blizzard Entertainment. This repository does not include StarCraft/Brood War assets or game data. OpenBW has not been included pending an explicit license and integration audit. Do not commit original game archives or extracted assets.
