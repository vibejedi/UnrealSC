# UnrealSC development milestones

- [x] Initialize repository and UE5 native module on a feature branch.
- [x] Implement basic WASD camera pan and mouse-wheel zoom (uncompiled source implementation).
- [ ] Verify editor loads project, camera input, and packaged build on Windows.
- [ ] Audit OpenBW license, dependencies, build and actual step/action/state APIs using a pinned revision.
- [ ] Run OpenBW independently with owned game data; record a deterministic combat test.
- [ ] Design/test versioned IPC protocol and external bridge process.
- [ ] Render external simulation snapshots in UE5 using primitive unit proxies.
- [ ] Translate RTS selection/right-click/attack-move into authoritative commands.
- [ ] Render terrain from owned map input; retain original walkability and simulation grid.
- [ ] Implement deterministic regression tests against recorded simulation behavior.
- [ ] Add custom 3D assets and animation once core behavior is proven.

## First acceptance test
A locally running external simulation drives five Marine proxies and eight Zergling proxies across a UE5 scene. Mouse commands travel to the external engine; UE only interpolates unit visuals. No original game assets are required for this test.
