#ifndef SYSTEM_EVENTS_H
#define SYSTEM_EVENTS_H

static bool processMouseMovement = false;;
static bool renderEngineUI = true;
static bool FirstPersonCamera = false;

class SystemEvents
{
public:
	SystemEvents();
	bool getProcessMouseMovementStatus();
	void setProcessMouseMovementStatus(bool status);

	bool getRenderEngineUIStatus();
	void setRenderEngineUIStatus(bool status);

	bool getFirstPersonCameraStatus();
	void setFirstPersonCameraStatus(bool*);
private:

};
#endif