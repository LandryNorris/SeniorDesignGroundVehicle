//
// Created by landry on 4/6/23.
//

#ifndef SENIORDESIGNGROUNDVEHICLE_TEST_H
#define SENIORDESIGNGROUNDVEHICLE_TEST_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define ASSERT_EQUALS(expected, actual) if((expected) != (actual)) { \
    printf(#expected " does not equal " #actual "\n");                  \
    exit(1);                                                         \
}

#define ASSERT_STRING_EQUALS(expected, actual) if(strcmp((expected), (actual)) != 0) { \
    printf(#expected " does not equal " #actual "\n");                  \
    exit(1);                                                         \
}

#define TEST_START(name) void name () { \
    printf(#name "\n");

#define TEST_END printf("Test passed!\n"); \
}


#endif //SENIORDESIGNGROUNDVEHICLE_TEST_H
