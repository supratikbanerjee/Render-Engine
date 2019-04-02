#include "system_events.h"
#include <iostream>



SystemEvents::SystemEvents()
{
	printf("System Events\n");
}

bool SystemEvents::getProcessMouseMovementStatus()
{
	return processMouseMovement;
}
void SystemEvents::setProcessMouseMovementStatus(bool status)
{
	processMouseMovement = status;
}

bool SystemEvents::getRenderEngineUIStatus()
{
	return renderEngineUI;
}

void SystemEvents::setRenderEngineUIStatus(bool status)
{
	renderEngineUI = status;
}

bool SystemEvents::getFirstPersonCameraStatus()
{
	return FirstPersonCamera;
}


void SystemEvents::setFirstPersonCameraStatus(bool* status)
{
	FirstPersonCamera = *status;
}
