# UnrealSC

Unreal Engine 5.8 C++ RTS prototype. Long-term goal: study faithful Brood War behavior with a separate authoritative simulation and modern 3D rendering.

**Status:** UE5.8 Mac foundation reported working; combat sandbox source awaiting compile/test. There is **no OpenBW bridge yet** and no authentic Brood War simulation.

## Quick start (macOS)

```bash
git clone -b feat/rts-combat-sandbox https://github.com/vibejedi/UnrealSC.git
open "$HOME/Documents/Unreal Projects/UnrealSC/UnrealSC.uproject"
```

If you already cloned it, switch branches and pull:

```bash
cd "$HOME/Documents/Unreal Projects/UnrealSC"
git fetch origin
git switch feat/rts-combat-sandbox
git pull
```

Compile the UnrealSCEditor target using your Unreal Engine 5.8 installation. Create a Basic level and click Play.

The sandbox spawns five Marine proxy cubes and eight Zergling proxy cubes. WASD pans, scroll zooms, left-click selects one Marine, and right-click orders placeholder movement. **This is a UI/control experiment, not the real simulation.** See [Sandbox guide](docs/SANDBOX.md), [architecture](docs/ARCHITECTURE.md) and [roadmap](docs/ROADMAP.md).

## Legal / assets

This project is not affiliated with Blizzard Entertainment. It includes no StarCraft assets, audio, archives, maps or extracted data. No OpenBW code is bundled pending verification of reuse rights.
