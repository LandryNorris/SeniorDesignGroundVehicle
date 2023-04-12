cmake_minimum_required(VERSION 3.23)
project(SeniorDesignGroundVehicle C)

set(CMAKE_C_STANDARD 99)

include_directories(".")

add_executable(SeniorDesignGroundVehicle main.c groundVehicle.c groundVehicle.h commands.h driveState.h)
add_executable(DriveTest groundVehicle.c test/driveTest.c)
add_executable(LaserTest groundVehicle.c test/laserTest.c)
add_executable(ShowcaseTest groundVehicle.c test/showcaseTest.c)

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(DriveTest PUBLIC ${MATH_LIBRARY})
    target_link_libraries(LaserTest PUBLIC ${MATH_LIBRARY})
    target_link_libraries(ShowcaseTest PUBLIC ${MATH_LIBRARY})
    target_link_libraries(SeniorDesignGroundVehicle PUBLIC ${MATH_LIBRARY})
endif()
