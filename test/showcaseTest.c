//
// Created by landry on 4/7/23.
//

#include <sys/time.h>
#include "driveState.h"
#include "groundVehicle.h"
#include "test.h"

DriveState* states[100];
int numStates = 0;

long timeToShootLaser = 9999999;
int laserShot = 0;

long now() {
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);

    return currentTime.tv_usec/1000 + currentTime.tv_sec*1000;
}

void drive(DriveState* command) {
    states[numStates++] = command;
}

long lastDelayStart = 0;

void runDelay(int time) {
    lastDelayStart = now();
    long endTime = lastDelayStart + time*1000;

    while(now() <= endTime) {
        if(!laserShot && now() - lastDelayStart >= timeToShootLaser) {
            onLaserDetected();
            laserShot = 1;
        }
        loop();
    }
}

TEST_START(showcase1)
    setDriveCallback(&drive);
    setOnDelay(&runDelay);

    onIRCMessageReceived("drive 0 0 10");
    loop();

    ASSERT_EQUALS(2, numStates)
    ASSERT_EQUALS(0, states[0]->powerY)
    ASSERT_EQUALS(0, states[0]->powerX)
TEST_END

TEST_START(showcase1WithShoot)
    timeToShootLaser = 3000;
    setDriveCallback(&drive);
    setOnDelay(&runDelay);

    onIRCMessageReceived("drive 0 0 10");
    loop();

    ASSERT_EQUALS(3, numStates)
    ASSERT_EQUALS(0, states[0]->powerY)
    ASSERT_EQUALS(0, states[0]->powerX)
TEST_END

TEST_START(showcase2)
    setDriveCallback(&drive);
    setOnDelay(&runDelay);

    onIRCMessageReceived("drive 20 0 10");
    loop();

    ASSERT_EQUALS(2, numStates)
    ASSERT_EQUALS(20, states[0]->powerY)
    ASSERT_EQUALS(0, states[0]->powerX)
TEST_END

TEST_START(showcase2WithShoot)
    timeToShootLaser = 3000;
    setDriveCallback(&drive);
    setOnDelay(&runDelay);

    onIRCMessageReceived("drive 20 0 10");
    loop();

    ASSERT_EQUALS(3, numStates)
    ASSERT_EQUALS(20, states[0]->powerY)
    ASSERT_EQUALS(0, states[0]->powerX)
TEST_END

TEST_START(showcase3)
    setDriveCallback(&drive);
    setOnDelay(&runDelay);

    onIRCMessageReceived("drive (20 0 10) (20 90 10)");
    loop();

    ASSERT_EQUALS(3, numStates)
    ASSERT_EQUALS(20, states[0]->powerY)
    ASSERT_EQUALS(0, states[0]->powerX)
    ASSERT_EQUALS(0, states[1]->powerY)
    ASSERT_EQUALS(20, states[1]->powerX)
    ASSERT_EQUALS(0, states[2]->powerY)
    ASSERT_EQUALS(0, states[2]->powerX)
TEST_END

TEST_START(showcase3WithShoot)
    timeToShootLaser = 3000;
    setDriveCallback(&drive);
    setOnDelay(&runDelay);

    onIRCMessageReceived("drive (20 0 10) (20 90 10)");
    loop();

    ASSERT_EQUALS(3, numStates) //shoot should cause it to stop before second drive
    ASSERT_EQUALS(20, states[0]->powerY)
    ASSERT_EQUALS(0, states[0]->powerX)
    ASSERT_EQUALS(0, states[1]->powerY)
    ASSERT_EQUALS(0, states[1]->powerX)
    ASSERT_EQUALS(0, states[2]->powerY)
    ASSERT_EQUALS(0, states[2]->powerX)
TEST_END

TEST_START(showcase4)
    setDriveCallback(&drive);
    setOnDelay(&runDelay);

    onIRCMessageReceived("drive (20 0 10) (20 90 10) (20 0 10)");
    loop();

    ASSERT_EQUALS(4, numStates)
    ASSERT_EQUALS(20, states[0]->powerY)
    ASSERT_EQUALS(0, states[0]->powerX)
    ASSERT_EQUALS(0, states[1]->powerY)
    ASSERT_EQUALS(20, states[1]->powerX)
    ASSERT_EQUALS(20, states[2]->powerY)
    ASSERT_EQUALS(0, states[2]->powerX)
    ASSERT_EQUALS(0, states[3]->powerY)
    ASSERT_EQUALS(0, states[3]->powerX)
TEST_END

TEST_START(showcase4WithShoot)
    timeToShootLaser = 13000;
    setDriveCallback(&drive);
    setOnDelay(&runDelay);

    onIRCMessageReceived("drive (20 0 10) (20 90 10) (20 0 10)");
    loop();

    ASSERT_EQUALS(4, numStates) //shoot should cause it to stop before second drive
    ASSERT_EQUALS(20, states[0]->powerY)
    ASSERT_EQUALS(0, states[0]->powerX)
    ASSERT_EQUALS(20, states[1]->powerY)
    ASSERT_EQUALS(0, states[1]->powerX)
    ASSERT_EQUALS(0, states[2]->powerY)
    ASSERT_EQUALS(0, states[2]->powerX)
    ASSERT_EQUALS(0, states[3]->powerY)
    ASSERT_EQUALS(0, states[3]->powerX)
TEST_END

void reinitialize() {
    numStates = 0;
    timeToShootLaser = 99999999;
    lastDelayStart = 0;
    laserShot = 0;
}

int main() {
    showcase1();
    reinitialize();
    showcase1WithShoot();
    reinitialize();

    showcase2();
    reinitialize();
    showcase2WithShoot();
    reinitialize();

    showcase3();
    reinitialize();
    showcase3WithShoot();
    reinitialize();
}