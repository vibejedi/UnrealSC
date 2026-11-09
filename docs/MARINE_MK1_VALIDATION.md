# UnrealSC Marine MK-I — Generated character asset validation

## Provenance
- Higgsfield GPT Image 2.6: T-pose front-view armored infantry concept.
- Tripo H3.1: high-detail textured PBR mesh requested with approximately 55k target faces and quad topology.
- The file delivered by Tripo with a `.glb` filename contained **FBX binary bytes**. It was converted using `assimpjs` into a valid GLB 2.0 file before auto-rigging.
- Meshy 3D Rigging: generated four separate skeletal GLBs (Idle, RunFast, Side_Shot, Shot_and_Fall_Backward).

## Structural validation (external asset files, not committed)
| Clip | Mesh | Skin | Joints | Animations | Mesh vertices |
|---|---:|---:|---:|---:|---:|
| Idle | 1 | 1 | 24 | 1 | 300,216 |
| RunFast | 1 | 1 | 24 | 1 | 300,216 |
| Side_Shot | 1 | 1 | 24 | 1 | 300,216 |
| Shot_and_Fall_Backward | 1 | 1 | 24 | 1 | 300,216 |

Each was a structurally valid GLB 2.0 and shared exactly the same **ordered joint names and parent hierarchy**. Their inverse-bind-matrix data did **not** match; per-element maximum absolute matrix differences were large (~196–273), not harmless floating-point noise.

**Therefore, DO NOT assume these are interchangeable animation clips for a single Unreal skeleton.** Use the Idle rig as the reference skeleton. Retarget RunFast, Side_Shot, and Death to that reference rig in Blender or Unreal (via IK Rig/IK Retargeter), inspecting rest pose, scale, axes and deformation. Even matching names and topology cannot substitute for that QA.

## Performance
The rigged GLBs are ~30 MB each, with a high-density mesh (300,216 POSITION vertices in the first primitive). Treat them as **source/hero meshes**, not final mass-RTS runtime meshes. Retopologize, optimize materials and textures, and build LODs; measure CPU skinning and GPU cost on the target Mac before spawning hundreds of soldiers. Triangle counts are not inferred from POSITION vertex count.

## Test in UE5.8
1. Import the Idle GLB into Blender, examine skeleton and mesh deformation at different frames.
2. Export as a skeletal FBX and import into UE5 as the first Marine skeleton.
3. Assign to `ArtMesh` on `BP_MarineUnit`, with root/feet grounded (see MARINE_ART_IMPORT.md).
4. Verify selection, attack effects, health/death, proper scale and camera framing using 5v8 encounter.
5. Retarget the three other motion sources onto the established Marine skeleton; test blend transitions.
6. Add a separate original rifle and muzzle socket. `Side_Shot` is body motion only, not a complete weapon firing rig.
7. Only then count the character as integrated / game-ready.

**Assets were generated separately in Higgsfield and are not committed in GitHub.** Consult the current chat's Higgsfield generation results for downloads. Public release needs asset rights review.
