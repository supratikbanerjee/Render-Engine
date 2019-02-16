#ifndef SYSTEM_EVENTS_H
#define SYSTEM_EVENTS_H
class SystemEvents
{
public:
	SystemEvents();
	bool getProcessMouseMovementStatus();
	void setProcessMouseMovementStatus(bool status);

	bool getRenderEngineUIStatus();
	void setRenderEngineUIStatus(bool status);
private:
	bool processMouseMovement = false;;
	bool renderEngineUI = true;
};
#endif