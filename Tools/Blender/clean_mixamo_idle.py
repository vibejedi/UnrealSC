"""Run in Blender background, with -- <input FBX> <output FBX>.
Removes Mixamo's exported default Cube, camera and light; keeps skinned Marine.
This script clears the working Blender scene. Use a backup.
"""
import bpy
from pathlib import Path
import sys

args = sys.argv[sys.argv.index("--") + 1:] if "--" in sys.argv else []
source = Path(args[0]).expanduser() if args else Path.home() / "Downloads" / "Marine_Idle.fbx"
target = Path(args[1]).expanduser() if len(args) > 1 else source.with_name("Marine_Idle_Clean.fbx")
if not source.is_file():
    raise FileNotFoundError(str(source))

bpy.ops.object.select_all(action="SELECT")
bpy.ops.object.delete(use_global=False)
bpy.ops.import_scene.fbx(filepath=str(source), use_anim=True)
meshes = [x for x in bpy.context.scene.objects if x.type == "MESH"]
arms = [x for x in bpy.context.scene.objects if x.type == "ARMATURE"]
if len(arms) != 1 or not meshes:
    raise RuntimeError(f"Expected 1 Armature and meshes, got {len(arms)} arms and {len(meshes)} meshes")
marine = max(meshes, key=lambda x: len(x.data.vertices))
if len(marine.data.vertices) < 1000:
    raise RuntimeError("The Marine geometry was not found")
if not any(m.type == "ARMATURE" for m in marine.modifiers) or not marine.vertex_groups:
    raise RuntimeError("The Marine does not appear to be skinned")
for obj in list(bpy.context.scene.objects):
    if obj.type in {"CAMERA", "LIGHT"} or (obj.type == "MESH" and obj != marine):
        bpy.data.objects.remove(obj, do_unlink=True)
bpy.ops.object.select_all(action="DESELECT")
marine.select_set(True)
arms[0].select_set(True)
bpy.context.view_layer.objects.active = arms[0]
target.parent.mkdir(parents=True, exist_ok=True)
bpy.ops.export_scene.fbx(
    filepath=str(target), use_selection=True,
    object_types={"MESH","ARMATURE"}, add_leaf_bones=False,
    bake_anim=True, bake_anim_use_all_actions=False,
    bake_anim_use_nla_strips=False,
    axis_forward="-Z", axis_up="Y",
)
print(f"UnrealSC: exported cleaned Marine to {target}; mesh={marine.name}; verts={len(marine.data.vertices)}")
