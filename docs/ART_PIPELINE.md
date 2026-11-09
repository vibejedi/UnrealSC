# Art direction and technical asset pipeline

## North star
A gritty, readable, high-end sci-fi RTS battle at an industrial outpost. Prioritize the standard RTS camera; close-ups are a secondary showcase. Clear silhouettes and animation timings matter more than excessive particles or tiny surface detail.

Create original custom assets for this project. Do not commit assets extracted from Blizzard games.

## First two deliverables
- One fully textured, rigged bipedal powered-armor infantry unit (Marine role), with idle, locomotion, aim/fire, hit and death states.
- One quadrupedal predatory alien (Zergling role), with idle, fast run, melee strike, hit and death.
- One environment tile set: ground, concrete/steel platform, lights, walls, mining equipment and cover.

## Import pipeline
1. Create a consistent concept sheet with front, back, side and 3/4 references and an agreed silhouette.
2. Model and retopologize in Blender or Tripo + Blender. Verify topology at joints.
3. Rig with stable orientation and scale. For Unreal use centimeters (1 UE unit = 1 cm), Z up, and an intentional forward axis.
4. Export FBX for tested skeletal animation paths (or use an approved GLB/Interchange pipeline if animations import correctly); explicitly test armature scale and root motion.
5. Import to `Content/Units/Marine` or `Content/Units/Zergling`, make Animation Blueprints and unit Blueprint children.
6. Assign the SkeletalMesh component in the Blueprint unit, then assign Blueprint classes to `BP_CombatSandbox` in the level.
7. Add socket-based muzzle/impact effects and audio to the Blueprint events. Use Niagara for production effects.
8. Test readability with 5 vs 8 units at the normal gameplay zoom before scaling up.

## Initial performance targets (guidance, not a proven budget)
On a MacBook Pro, prototype LOD0 character budgets around 15k–35k triangles per unit, with simpler LODs for RTS camera distances. Keep materials/texture resolution proportionate to visible size; use a profiler to establish platform-specific budgets. The final budget will differ for hundreds of units.

## Quality gates
- Visual silhouette instantly differentiates each role at 1080p RTS zoom.
- Clear anticipation, action and recovery for each attack.
- Hit/death feedback doesn't obscure control or target selection.
- Unit collision & gameplay locations remain simulation-owned when a bridge arrives.
- No copyrighted game files or unlicensed third-party content committed.
