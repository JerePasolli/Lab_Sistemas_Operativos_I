#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "measurements.h"

measurements *getStructures(char *path, int *structures){

    int fd;
    int status;
    size_t size;
    struct stat s;

    fd = open (path, O_RDONLY);
    if(fd<0){
        fd = open("./rawdata/datos", O_RDONLY);
    }

    if(fd<0){
        fprintf(stderr, "Opening file failed\n");
        exit(EXIT_FAILURE);
    }
        
	status = fstat (fd, &s);

    if(status<0){
        fprintf(stderr, "Obtaining stats of the file failed\n");
        exit(EXIT_FAILURE);
    }
        
    size = s.st_size;

    *structures = size/sizeof(measurements);
    
	measurements *data = mmap (NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    
    if(data == MAP_FAILED){
        fprintf(stderr,"Mapping data Failed\n");
        exit(EXIT_FAILURE);
    }
    close (fd);
    
    return data;
}

int getAverage(measurements *data, int structures){

    int average = 0;
    for(int i=0; i<structures; i++){
        average += data[i].validSamples;
    }
    return average/structures;
}