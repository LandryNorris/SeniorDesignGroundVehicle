//
// Created by landry on 4/6/23.
//

#include "groundVehicle.h"
#include "test/test.h"

DriveState* states[100];
int numStates = 0;

void drive(DriveState* command) {
    states[numStates++] = command;
}

TEST_START(driveTest)
    numStates = 0;
    onIRCMessageReceived("drive 100 40 20");
    loop();
    ASSERT_EQUALS(64, states[0]->powerX)
    ASSERT_EQUALS(76, states[0]->powerY)
TEST_END

TEST_START(forwardDriveTest)
    numStates = 0;
    onIRCMessageReceived("drive 100 0 20");
    loop();
    ASSERT_EQUALS(0, states[0]->powerX)
    ASSERT_EQUALS(100, states[0]->powerY)
TEST_END

TEST_START(crossDriveTest)
    numStates = 0;
    onIRCMessageReceived("drive 100 90 20");
    loop();
    ASSERT_EQUALS(100, states[0]->powerX)
    ASSERT_EQUALS(0, states[0]->powerY)
TEST_END

TEST_START(multiDriveTest)
    numStates = 0;
    onIRCMessageReceived("drive (100 90 20) (50 0 5) (20 45 10)");
    loop();
    ASSERT_EQUALS(100, states[0]->powerX)
    ASSERT_EQUALS(0, states[0]->powerY)
    ASSERT_EQUALS(0, states[1]->powerX)
    ASSERT_EQUALS(50, states[1]->powerY)
    ASSERT_EQUALS(14, states[2]->powerX)
    ASSERT_EQUALS(14, states[2]->powerY)
TEST_END

TEST_START(driveAndStopTest)
    numStates = 0;
    onIRCMessageReceived("drive 100 40 20");
    loop();
    ASSERT_EQUALS(64, states[0]->powerX)
    ASSERT_EQUALS(76, states[0]->powerY)
    onIRCMessageReceived("stop");
    loop();
    ASSERT_EQUALS(0, states[1]->powerX)
    ASSERT_EQUALS(0, states[1]->powerY)
TEST_END

TEST_START(driveAndStopAtEndTest)
    numStates = 0;
    onIRCMessageReceived("drive 100 40 20");
    loop();
    ASSERT_EQUALS(64, states[0]->powerX)
    ASSERT_EQUALS(76, states[0]->powerY)
    ASSERT_EQUALS(0, states[1]->powerX)
    ASSERT_EQUALS(0, states[1]->powerY)
TEST_END

int main() {
    printf("Starting drive tests\n");
    setDriveCallback(&drive);
    driveTest();
    forwardDriveTest();
    crossDriveTest();
    driveAndStopTest();
    multiDriveTest();
    driveAndStopAtEndTest();

    printf("All tests passed!");

    return 0;
}
