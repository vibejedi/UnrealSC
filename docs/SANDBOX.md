# Combat sandbox — milestone 2

This prototype is deliberately **not a Brood War simulation**. It verifies 3D world placement, RTS mouse picking, input commands, and camera behavior using primitive shapes; it contains no Blizzard art or OpenBW source.

## Try it in Unreal Engine 5.8

1. Build the `UnrealSCEditor` target on macOS.
2. Open `UnrealSC.uproject`, then create/open a **Basic** level.
3. Click **Play**. The default game mode spawns one flat test arena, five MARINE cubes and eight ZERGLING cubes. (Any existing floor in the Basic level may also be visible.)
4. **WASD** pans the camera; **mouse wheel** zooms.
5. **Left-click** one Marine to select it. **Right-click** the ground to give it a temporary move target.
6. Zerglings are static test targets. Combat, group selection, attack-move, health, fog, economy, pathfinding, and original unit mechanics are **not** implemented.

## Definition of done

- Editor builds for UE 5.8 on Apple Silicon
- Play mode shows 5 + 8 unit proxies
- Mouse selection highlights a Marine
- Right-click movement works on a selectable Marine
- Existing camera controls still work

## When OpenBW is connected

Replace `SetMockMoveTarget` with an outbound command to the simulation bridge, replace per-actor movement ticks with positions from authoritative snapshots, preserve stable numeric unit IDs, and leave rendering interpolation on the Unreal side.

See [ARCHITECTURE.md](ARCHITECTURE.md) for the planned authority boundary.
