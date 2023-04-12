//
// Created by landry on 4/7/23.
//

#include "test.h"
#include "driveState.h"
#include "groundVehicle.h"

DriveState* states[100];
int numStates = 0;
char* lastMessage = NULL;

void drive(DriveState* command) {
    states[numStates++] = command;
}

void sendIrcMessage(char* message) {
    lastMessage = message;
}

TEST_START(testReceiveLaser)
    lastMessage = NULL;
    numStates = 0;
    setOnIRCMessageSend(&sendIrcMessage);

    ASSERT_EQUALS(NULL, lastMessage)
    onLaserDetected();

    ASSERT_STRING_EQUALS("Got hit by laser!", lastMessage);
TEST_END

TEST_START(testStopOnReceiveLaser)
    lastMessage = NULL;
    numStates = 0;
    setOnIRCMessageSend(&sendIrcMessage);
    loop();
    setDriveCallback(drive);

    onIRCMessageReceived("drive 100 45 4");
    loop();

    ASSERT_EQUALS(NULL, lastMessage)
    onLaserDetected();

    ASSERT_STRING_EQUALS("Got hit by laser!", lastMessage)
    ASSERT_EQUALS(0, states[1]->powerX)
    ASSERT_EQUALS(0, states[1]->powerX)
TEST_END

int main() {
    testReceiveLaser();
    testStopOnReceiveLaser();

    printf("All tests passed!");
}
