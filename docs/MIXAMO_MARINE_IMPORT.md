# Mixamo Marine — validated import plan for Unreal Engine 5.8

User-supplied files were inspected at the FBX binary structure level. **All five contain identical ordered 65-bone names and bone-parent hierarchy**. The first file is the skinned character; all other files are animation-only.

| File | Mesh | Duration (approx.) | Purpose |
|---|---|---:|---|
| Marine_Idle.fbx | Yes | 2.00 s | Main skinned Marine + idle |
| Marine_Running.fbx | No | 0.50 s | Run, nearly zero net hip displacement |
| Marine_Shooting.fbx | No | 0.20 s | Short firing motion |
| Marine_Hit.fbx | No | 1.53 s | Damage reaction |
| Marine_Death.fbx | No | 2.07 s | Death fall; includes large hip displacement |

## Known cleanup

Idle contains two meshes: an unrelated Blender default `Cube` (8 vertices), plus `tripo_mesh_e7255c17` (300,216 vertices), and a camera/light. Delete the Cube/camera/light before game import. The FBX contains just one linked texture media entry, so the original Tripo textured GLB should be retained for final PBR material rebuilding.

Run our helper on your Mac, with Blender installed:

```bash
cd "$HOME/Documents/Unreal Projects/UnrealSC"
"/Applications/Blender.app/Contents/MacOS/Blender" --background --python Tools/Blender/clean_mixamo_idle.py -- "$HOME/Downloads/Marine_Idle.fbx" "$HOME/Downloads/Marine_Idle_Clean.fbx"
```

The helper is **not yet tested** on the user's Blender installation. If it errors, delete the Cube manually in the Blender Outliner and export only the skinned Marine and its armature. Keep your original FBXs as backups.

## Unreal import sequence

1. Open Content Browser `/Game/Units/Marine`. Import `Marine_Idle_Clean.fbx` as a **new Skeletal Mesh** plus **Animation**, creating a new Skeleton. Preview it and ensure there is no Cube.
2. Rename assets `SK_Marine_MK1`, `SK_Marine_MK1_Skeleton`, `A_Marine_Idle`.
3. Import `Marine_Running.fbx`, `Marine_Shooting.fbx`, `Marine_Hit.fbx`, `Marine_Death.fbx` as **Animation only**, with **Import Mesh off**, explicitly selecting `SK_Marine_MK1_Skeleton` for all four. Never create four extra skeletal meshes.
4. Inspect imported sequences. Running is intended to be in-place; keep root motion disabled because `SandboxUnit` owns movement. Death's root translation may need retarget/cleanup. A Blender re-export of the Idle character can alter bone orientations, so validate animation compatibility before proceeding.
5. Create `BP_MarineUnit` subclass of `SandboxUnit`, set inherited `ArtMesh` to `SK_Marine_MK1`. The C++ proxy cube hides automatically when ArtMesh has a skeletal asset.
6. Create `ABP_Marine` with Idle/Run blend driven by `GetVisualMoveSpeed()`, and slots for Shooting, Hit and Death montages. Hook montages through `BP_OnAttack`, `BP_OnDamaged`, `BP_OnDeath` in `BP_MarineUnit`; these are presentation-only events, not damage authority.
7. Create/place `BP_CombatSandbox` and set `MarineClass = BP_MarineUnit` in `LV_TerranOutpost`. Playtest at the RTS camera zoom.

## Limits and quality gate

- Rig is approximately 300k source mesh vertices, far too heavy for a mass-army RTS without retopology and LODs.
- Shot clip is only ~0.2 s; hit is ~1.53 s and may be interrupted during rapid attacks. Death lasts ~2.07 s; sandbox destroys units after ~2.5 s.
- No dedicated rifle mesh, firing muzzle socket, complete PBR material maps, or author-tested UE5 Animation Blueprint is included.
- Unreal's FBX import UI varies with 5.8's Interchange pipeline.
- No user-provided FBX binaries have been committed to GitHub. Keep local source files and validate rights before any public release.

This document captures source-file inspection and the proposed workflow, **not a successful Unreal Editor import test**.
