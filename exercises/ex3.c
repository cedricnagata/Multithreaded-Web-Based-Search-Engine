// Cedric Nagata
// nagatac@uw.edu

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Point3d
{
    uint16_t x;
    uint16_t y;
    uint16_t z;
} Point3d;

Point3d *AllocatePoint3d(uint16_t x, uint16_t y, uint16_t z);

int main(int argc, char **argv) {
    Point3d *point = AllocatePoint3d(1, 1, 1);

    if (point == NULL || point -> x != 1 || point -> y != 1 || point -> z != 1) {
        fprintf(stderr, "Point3d Allocation Test failed\n");
        return EXIT_FAILURE;
    }

    free(point);
    
    printf("Point3d Allocation Test passed!\n");
    return EXIT_SUCCESS;
}

Point3d *AllocatePoint3d(uint16_t x, uint16_t y, uint16_t z) {
    Point3d *point = (Point3d*) malloc(sizeof(Point3d));

    if (point == NULL) {
        return NULL;
    }

    point -> x = x;
    point -> y = y;
    point -> z = z;

    return point;
}