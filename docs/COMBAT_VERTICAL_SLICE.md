# Milestone 3 — mock combat vertical slice

## What exists in this branch

- Five Marine proxy units and eight Zergling proxy units spawn in the map.
- Enemy Zerglings automatically acquire and chase nearby Marines.
- Marines automatically shoot Zerglings entering range; the attacks have brief debug tracers.
- Both teams have mock health, damage, cooldowns and death/despawn.
- Left-click selects one friendly unit. Right-click on empty terrain moves it; right-click on an enemy orders an attack.
- Selectable Blueprint events on unit actors support later animation / sound / Niagara integration.

## Not implemented / not promised

This is NOT canonical Brood War combat. The numbers, attack cadence, target acquisition, collision behavior and movement are temporary, and there is no authoritative OpenBW simulation, pathfinding, multiplayer, production, squads or formation control. High-quality meshes, animations, VFX and audio do NOT ship with this branch. This is an interaction test and a presentation integration seam.

## Test

1. Close Unreal Editor before updating/building native code.
2. Switch to `feat/combat-vertical-slice` and pull.
3. Build UnrealSCEditor using the UE 5.8 Mac toolchain.
4. Open `LV_TerranOutpost` (your local level) and press Play.
5. Zerglings should move toward Marines; Marines should fire when enemies enter range.
6. Left-click a Marine while alive, then right-click an enemy to focus attack or the ground to move.
7. Observe damage numbers in the unit labels and deaths. Press Stop/Play to reset.

## Hook for character art

Create a Blueprint child of `SandboxUnit`. In Components > `ArtMesh`, assign the imported skeletal mesh and appropriate Animation Blueprint. At BeginPlay, the placeholder cube is hidden automatically when an ArtMesh skeletal mesh is assigned.

Implement these optional presentation events in the child Blueprint:
- `BP_OnAttack(TargetUnit)`: muzzle flash, attacks, weapon/audio.
- `BP_OnDamaged(RemainingHealth, TotalHealth)`: reactions, health bars, hit VFX.
- `BP_OnDeath()`: animation, effects, sound.
- `BP_OnMoveOrder(Destination)`: movement animation transitions.

Create two Blueprint children `BP_MarineUnit` and `BP_ZerglingUnit`, and one Blueprint child `BP_CombatSandbox`. Place `BP_CombatSandbox` in your test level, then set its `MarineClass` and `ZerglingClass` references to the appropriate Blueprint children. The GameMode detects an existing combat sandbox and will not auto-spawn another.

IMPORTANT: a single click into the viewport may be needed before input is captured. All combat motion is temporary C++ logic.

## Next acceptance gate

1. Local Mac UE 5.8 C++ build succeeds.
2. No crashes when units die, auto acquire new targets, or when the player right-clicks a dead/vanished actor.
3. A hand-authored animated mesh replaces one Marine proxy without changing any targeting code.
