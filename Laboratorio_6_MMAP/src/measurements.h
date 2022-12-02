#ifndef MEASUREMENTS_H_
#define MEASUREMENTS_H_

#include <stdbool.h>

typedef struct __attribute__((__packed__)){
        unsigned short int version;
        unsigned short int drxVersion;
        char r1[4];
        double initCW;
        float azimuth;
        float elevation;
        unsigned short int idVolumen;
        unsigned short int idBarrido;
        unsigned short int idConjunto;
        unsigned short int idGrupo; 
        unsigned short int idPulso;
        bool iniBarrido;
        bool finBarrido;
        bool finGrupo;
        bool inhibido;
        unsigned short int validSamples;
        unsigned short int nroAdquisicion;
        char r2[2];
        unsigned int nroSecuencia;
        unsigned long int readTime_high;
        unsigned long int readTime_low;
        char r3[64];
    }measurements;

    measurements* getStructures(char*, int *);
    int getAverage(measurements*, int);

#endif