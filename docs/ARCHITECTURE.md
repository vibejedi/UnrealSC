# Architecture decision record — UnrealSC

## Goal
Reproduce Brood War's *behavior* while rendering a separate modern 3D presentation in Unreal Engine 5. The first UE milestone is deliberately standalone and uses no Blizzard or OpenBW assets/code.

## Authority boundary
- **External simulation (future):** unit orders, stable unit IDs, positions, economy, attacks, fog, win/loss, pathfinding, and frame timing.
- **Unreal:** camera, selection overlay, UI, meshes, skeletal animation, interpolation, audio, and effects.
- Unreal must not use its physics or NavMesh to authoritatively change unit positions or combat results.

## Bridge milestone (NOT implemented yet)
Run the simulation as a separate OS process, initially using versioned messages over local TCP. Keep any simulation-dependent implementation in `External/` or an out-of-tree checkout until licensing and build requirements are established.

Prototype message envelopes (proposal; subject to actual OpenBW API audit):

```json
{"version":1,"type":"step","frame":24,"steps":1}
{"version":1,"type":"command","execute_frame":25,"player":0,"unit_ids":[42],"order":"move","x":320,"y":480}
{"version":1,"type":"snapshot","frame":25,"units":[{"id":42,"type":0,"owner":0,"x":321,"y":480,"hp":40}]}
```

No assumption is made that OpenBW accepts these messages today: the adapter must implement them explicitly. Use integers in simulation space and map to Unreal world coordinates only at the rendering boundary. Add sequence numbers and deterministic snapshot checksums prior to multiplayer support.

## Fixed-step behavior
Drive OpenBW at its game-defined step cadence, independent of the UE render tick. The presentation can interpolate between consecutive immutable snapshots. Never derive authoritative simulation steps from render FPS.

## Security and licensing
Do not commit Blizzard MPQs, textures, sounds, maps, copyrighted assets, or extracted game data. Do not vendor OpenBW code without verifying its license and permissions. Any public release needs a separate IP/licensing review.

## Known gaps
UE5 compilation and runtime not yet verified. OpenBW process, build, frame interface, data loader, map conversion, unit view, selection, and input command translation not implemented.
