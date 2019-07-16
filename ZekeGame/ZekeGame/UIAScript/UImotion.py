#coding:utf-8

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
path += "UI1.uim"
with open(path,"wb") as file:
    file.write("UIM".encode())
    
    key = (bpy.data.scenes[0].frame_end - bpy.data.scenes[0].frame_start) * len(objs)
    print(key)
    file.write(key.to_bytes(4,"little"))
    print(bpy.data.scenes[0].frame_end)
    dtime = 1.0/30.0
    for fm in range(bpy.data.scenes[0].frame_start,bpy.data.scenes[0].frame_end+1):
        bpy.data.scenes[0].frame_current = fm
        bpy.data.scenes[0].update()
        bpy.ops.object.paths_calculate()
        
        time = dtime * fm
        file.write(struct.pack("f",time))
        
        cnt = 0
        for obj in objs:
            pos = obj.location*100
            sca = obj.scale
            rot = obj.rotation_euler.to_quaternion()
            
            file.write(cnt.to_bytes(4,"little"))
            
            for p in pos:
                file.write(struct.pack("f",p))
                
            for s in sca:
                file.write(struct.pack("f",s))
            
            file.write(struct.pack("f",rot.x))
            file.write(struct.pack("f",rot.y))
            file.write(struct.pack("f",rot.z))
            file.write(struct.pack("f",rot.w))
            
            #print(cnt)
            #print(pos)
            #print(sca)
            #print(rot)
                
            cnt+=1