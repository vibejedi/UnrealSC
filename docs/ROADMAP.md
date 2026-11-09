# UnrealSC development milestones

- [x] Initialize UE5 native module, RTS camera and player controller; user confirmed UE5.8 Mac launch and camera.
- [x] Build 5 Marine / 8 Zergling sandbox with single-unit selection and right-click mock move; user confirmed it works.
- [x] Add code for mock enemy AI, ranged/melee attacks, health/deaths, attack orders and Blueprint animation/VFX events (not yet compiled).
- [ ] Compile and playtest milestone 3 on UE5.8 Apple Silicon.
- [ ] Import first original rigged Marine-style and Zergling-style units; replace cubes through BP children.
- [ ] Implement character Animation Blueprints and Niagara/SFX presentation.
- [ ] Build polished Terran outpost terrain module and light it for RTS camera readability.
- [ ] Add multi-unit box selection, attack-move and control groups.
- [ ] Settle long-term simulation: audit OpenBW license, build and actual API; never silently substitute placeholder gameplay for Brood War fidelity.
- [ ] Implement and compare authoritative simulation via an external bridge if appropriate.
- [ ] Scale battles with proper profiling, LODs and efficient unit representations.

Core principle: raise presentation quality immediately without letting temporary UE-specific gameplay become the permanent source of truth.
