#include "stdafx.h"
#include "PhysicsDebugDraw.h"

void PhysicsDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color){
	char str[256];
	sprintf_s(str, "from.x ...%f, y... %f, z... %f\n",from.getX(),from.getY(),from.getZ());
	OutputDebugStringA(str);
}