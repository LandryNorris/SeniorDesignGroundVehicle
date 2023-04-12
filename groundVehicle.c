//
// Created by landry on 4/6/23.
//

#include <string.h>
#include <stdlib.h>
#include "groundVehicle.h"
#include "commands.h"
#include "driveState.h"
#include "math.h"

void (*driveCallback)(DriveState*);
void (*ircSend)(char*);
void (*delay)(int);

int robotState = 0;

int isStopped = 0;

double toRadians(int degrees) {
    return degrees * M_PI / 180.0;
}

void handleDrive() {
    isStopped = 0;
    robotState = 0;
    while(1) {
        char* driveText = strtok(NULL, " ");
        if(!driveText) break;

        int offset = 0;
        if(driveText[0] == '(') offset = 1;
        int power = atoi(driveText + offset);

        char* thetaText = strtok(NULL, " ");
        if(!thetaText) break;
        int theta = atoi(thetaText);

        char* tText = strtok(NULL, " ");
        if(!tText) break;
        int t = atoi(tText);

        DriveCommand* command = malloc(sizeof(DriveCommand));
        command->power = power;
        command->theta = theta;
        command->t = t;

        int driveX = (int) (command->power * sin(toRadians(theta)));
        int driveY = (int) (command->power * cos(toRadians(theta)));

        DriveState* state = malloc(sizeof(DriveState));
        state->powerX = driveX;
        state->powerY = driveY;

        if(isStopped) break;
        driveCallback(state);

        if(delay) delay(t);
    }
    DriveState* state = malloc(sizeof(DriveState));
    state->powerX = 0;
    state->powerY = 0;
    driveCallback(state);
}

void stop() {
    isStopped = 1;
    robotState = 0;
    DriveState* state = malloc(sizeof(DriveState));
    state->powerX = 0;
    state->powerY = 0;
    if(driveCallback) driveCallback(state);
}

void setDriveCallback(void (*callback)(DriveState*)) {
    driveCallback = callback;
}

void onIRCMessageReceived(char* message) {
    char buffer[1000];
    strncpy(buffer, message, 1000);
    char* command = strtok(buffer, " ");

    if(strcmp("drive", command) == 0) {
        robotState = 1;
    } else if(strcmp("stop", command) == 0) {
        robotState = 0;
    }
}

void loop() {
    if(robotState == 1) handleDrive();
    if(robotState == 2) stop();
}

void setOnIRCMessageSend(void (*callback)(char*)) {
    ircSend = callback;
}

void onLaserDetected() {
    stop();
    if(ircSend) ircSend("Got hit by laser!");
}

void setOnDelay(void (*callback)(int)) {
    delay = callback;
}
