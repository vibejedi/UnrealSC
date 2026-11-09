# Marine art integration — milestone 4

## Goal
Replace the Marine cube with a rigged original powered-armor infantry model while preserving the current RTS controls and disposable combat sandbox. No Blizzard game assets are needed or included.

## Generated asset provenance
Concept reference generated via Higgsfield GPT Image 2.6; a Tripo H3.1 mesh and a Meshy rig are produced as separate generation jobs. **Generation output is not automatically committed to GitHub or imported into Unreal**. Validate each downloaded file before use.

## Coordinate conventions
The new unit actor uses a neutral SceneRoot located at ground level (spawn Z = 12 cm on the sandbox floor). The temporary cubes are offset upward inside the actor. The `ArtMesh` skeletal component is at local origin, where the imported character's feet should land. A Marine should be about 225–250 cm tall in its Unreal Blueprint after scale adjustment. Face the character toward +X in Unreal; adjust relative rotation of `ArtMesh` if the exporter uses another axis.

## Import checklist
1. Download the **rigged** version of the generated model; save the original unrigged GLB separately as the source mesh.
2. In Blender, import the rigged GLB (File > Import > glTF 2.0) and verify that an Armature exists and joints bend reasonably (hips, knees, shoulders, elbows). If no Armature or weights: it isn't yet a playable skeletal mesh.
3. Remove unwanted transforms and bake/export an FBX with skeletal hierarchy and textures. Keep a single intentional skeleton, correct bone weights at armor joints, consistent orientation, and feet at local Z=0.
4. In Unreal 5.8 import FBX into `/Game/Units/Marine/` as a **Skeletal Mesh** with **Import Mesh**, **Import Animations** only if an actual animation exists, and a new skeleton for the first import. Validate material texture maps under Unreal's lighting.
5. Create `BP_MarineUnit` based on `SandboxUnit`, assign its `ArtMesh` Skeletal Mesh, and create an Anim Blueprint using the imported skeleton. When an asset is assigned, the cube is hidden automatically. Read `GetVisualMoveSpeed` or `IsVisuallyMoving` from the owning actor to blend idle/run; use `BP_OnAttack`, `BP_OnDamaged`, `BP_OnDeath` to play animation montages and Niagara effects.
6. Create `BP_CombatSandbox` (parent `CombatSandbox`) and assign `MarineClass = BP_MarineUnit`. Place **one** BP_CombatSandbox actor in `LV_TerranOutpost` in the Editor. The native GameMode will not spawn a second sandbox when one is placed.
7. Press Play and check units maintain ground contact, selection works, death and attack calls fire, and 5-v-8 battle remains readable at ordinary RTS zoom.

## Caveats
Rigging with a generic humanoid auto-rigger may deform heavy shoulder plates and rigid armor. Expect manual weight painting, hard-surface armor segmentation, and a separate rifle mesh with a hand socket. An idle action does not equal a complete animation set; running, firing and death animations remain separate production tasks.

Do not commit the licensed or otherwise third-party asset bundle to GitHub unless rights are confirmed. Generated original character art should be archived in a project asset folder with generation settings and attribution, not only in transient URLs.

## Generated Marine MK-I QA result

The first source rig has 24 joints and an Idle animation. Separately generated RunFast, Side_Shot, and Shot_and_Fall_Backward clips have matching bone names and parent hierarchy but **different inverse-bind matrices**. Retarget the extra clips before combining them on one Unreal skeleton; never treat bone-name equality as sufficient. See [MARINE_MK1_VALIDATION.md](MARINE_MK1_VALIDATION.md). The high source vertex count also demands optimization/LODs before scaling to large RTS battles.
