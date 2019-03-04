#include "gizmo_manager.h"
#include <iostream>


GizmoManager::GizmoManager()
{
}

void GizmoManager::TrackMotion(int x, int y)
{
	deltaX = x - lastX;
	deltaY = lastY - y;
	lastX = x;
	lastY = y;
	//printf("%d %d %d %d %d, %d\n", deltaX, lastX, x, deltaY, lastY, y);
}