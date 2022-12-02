#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "measurements.h"

int main ()
{
    measurements *data;
    int structures;
	
	data = getStructures("../rawdata/datos", &structures);
    printf("The binary file contains %d instances of measurements\n", structures);

    int average = getAverage(data, structures);
    printf("The average value for validSamples is %d\n", average);
	
	return 0;
}