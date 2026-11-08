# UnrealSC development milestones

- [x] Initialize UE5 native module, targets, RTS camera and player controller.
- [x] User confirmed the initial UE5.8 Mac editor build and camera work.
- [x] Add sandbox code: 5 Marine proxies, 8 Zergling proxies, single selection and mock movement (uncompiled).
- [ ] Compile/test the sandbox on UE5.8 Mac.
- [ ] Verify OpenBW license, dependencies and actual action/state APIs at a pinned revision.
- [ ] Build OpenBW headlessly and execute a deterministic combat scenario with owned game data.
- [ ] Implement versioned IPC adapter for commands and simulation snapshots.
- [ ] Replace mock per-actor movement with authoritative OpenBW positions.
- [ ] Add group selection, attack-move, combat state and HUD based on engine snapshots.
- [ ] Import/visualize terrain while retaining original pathing and collision grids.
- [ ] Run deterministic tests against simulation/replay outputs.
- [ ] Add original 3D meshes, animation and VFX after engine integration proves faithful.

## Important boundary

Mock movement is disposable. Unreal never becomes the gameplay authority in the final architecture. No proprietary assets or unlicensed OpenBW source are included.
