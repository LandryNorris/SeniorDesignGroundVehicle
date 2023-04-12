//
// Created by landry on 4/6/23.
//

#ifndef SENIOR_DESIGN_GROUND_VEHICLE_H
#define SENIOR_DESIGN_GROUND_VEHICLE_H

#include "driveState.h"

void onIRCMessageReceived(char* message);

void setDriveCallback(void (*callback)(DriveState*));
void setOnIRCMessageSend(void (*callback)(char*));
void setOnDelay(void (*callback)(int));

void onLaserDetected();
void loop();

#endif //SENIOR_DESIGN_GROUND_VEHICLE_H
