# UnrealSC

UE 5.8 C++ RTS prototype, exploring a modern 3D Brood War-inspired game. Community prototype; not affiliated with Blizzard Entertainment.

## Status

- **Milestone 1** (Mac UE5.8 foundation): verified by user.
- **Milestone 2** (5-v-8 mock units, RTS selection and movement): verified by user.
- **Milestone 3** (combat and Blueprint art hooks): source committed, awaiting Mac UE5.8 compile/playtest.

This branch implements temporary arcade-like combat, **not authentic Brood War simulation**. No imported unit meshes, animations or Blizzard-owned game data are bundled.

## On your Mac

```bash
cd "$HOME/Documents/Unreal Projects/UnrealSC"
git fetch origin
git switch feat/combat-vertical-slice
git pull --ff-only origin feat/combat-vertical-slice
```

Close the Unreal Editor before rebuilding. If your local level is untracked or modified, commit/back it up separately instead of cleaning the working tree.

See [Combat test](docs/COMBAT_VERTICAL_SLICE.md), [Asset pipeline](docs/ART_PIPELINE.md), and [Architecture](docs/ARCHITECTURE.md).

## Legal / assets

No StarCraft archives, extracted art, sounds, maps, or OpenBW code are included. Original art is required for any independently distributable project, and a separate licensing review is needed for any public StarCraft-branded remake.
