#ifndef GIZMO_MANAGER_H
#define GIZMO_MANAGER_H
class GizmoManager
{
public:
	GizmoManager();
	void TrackMotion(int x, int y);
private:
	int lastX = 0;
	int lastY = 0;
	int deltaX = 0;
	int deltaY = 0;
};
#endif
