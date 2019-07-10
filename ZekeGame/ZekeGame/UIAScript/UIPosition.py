#coding: utf-8

import bpy
import mathutils as bmath
import struct

sobjs = bpy.context.selected_objects
objs = sobjs
for i in range(len(sobjs)):
    for j in range(len(sobjs)-1):
        #if int.from_bytes(objs[j].name.encode(),"little") >= int.from_bytes(objs[j+1].name.encode(),"little"):
        if objs[j].name >= objs[j+1].name:
            ob = objs[j+1]
            objs[j+1] = objs[j]
            objs[j] = ob
for o in objs:
    print(o.name)
path = __file__[:__file__.rfind("\\",2)]
print(path)
path = path[:path.rfind("\\",2)+1]
path += "UI.uip"
with open(path,"wb") as file:
    file.write("UPI".encode())
    file.write(len(objs).to_bytes(4,"little"))
    for obj in objs:
        nlen = len(obj.name)+1
        name = obj.name
        if name[len(name)-4] == ".":
            name = name[:len(name)-4]
            nlen = len(name)+1
        dim = [obj.dimensions[0]*100,obj.dimensions[1]*100]
        pos = obj.location*100
        sca = obj.scale
        rot = obj.rotation_euler.to_quaternion()
        
        if False:
            print(name)
            print(nlen)
            print(dim)
            print(pos)
            print(sca)
            print(rot)
            print("\n")
        
        file.write(nlen.to_bytes(4,"little"))
        
        file.write(name.encode())
        file.write(b"\x00")
        
        for d in dim:
            file.write(struct.pack("f",d))
        
        for p in pos:
            file.write(struct.pack("f",p))
            
        for s in sca:
            file.write(struct.pack("f",s))
        
        file.write(struct.pack("f",rot.x))
        file.write(struct.pack("f",rot.y))
        file.write(struct.pack("f",rot.z))
        file.write(struct.pack("f",rot.w))
            
print("perfect!!!!!")