#coding: utf-8

import bpy

path = "C:\\Users\\GC1821\\source\\repos\\meTGame\\ZekeGame\\ZekeGame\\Assets\\Sprite\\GUI\\modeSelect\\"
path += "modesel_blackF.png"
with open(path,"rb") as file:
    file.read(16)
    x = int.from_bytes(file.read(4),"big")
    y = int.from_bytes(file.read(4),"big")
    print(x)
x = (x /100) / 2
y = (y /100) / 2
verts = []
verts.append([x,y,0])
verts.append([x*-1,y,0])
verts.append([x*-1,y*-1,0])
verts.append([x,y*-1,0])
faces = [[0, 1, 2, 3]]
edges = []

mesh = bpy.data.meshes.new(name='mesh')

mesh.from_pydata(verts, edges, faces)
obj = bpy.data.objects.new('Object', mesh)
obj.location = (0,0,0.5)
obj.name = path[path.rfind("\\")+1:path.rfind(".")]
bpy.context.scene.objects.link(obj)

#bpy.ops.mesh.primitive_plane_add()
#obj = bpy.context.active_object
#obj.name = path[path.rfind("\\")+1:path.rfind(".")-1]
