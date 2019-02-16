#include "system_events.h"
#include <iostream>



SystemEvents::SystemEvents()
{}

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
