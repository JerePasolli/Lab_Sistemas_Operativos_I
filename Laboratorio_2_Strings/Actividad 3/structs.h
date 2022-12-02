#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    char a; // 1 byte
    char b; // 1 byte
    int  x; // 4 bytes
    unsigned short int y; // 2 bytes
    char c; // 1 byte
    unsigned short int z; // 2 bytes
    char d[3]; // 3 bytes
} BaseData;


typedef struct {
    char a; // 1 byte
    char b; // 1 byte
    int  x; // 4 bytes
    unsigned short int y; // 2 bytes
    unsigned short int z; // 2 bytes
    char c; // 1 byte
    char d[3]; // 3 bytes
} ReorderData;


typedef struct {
    long unsigned int ll; // 8 bytes
    char a; // 1 byte
    char b; // 1 byte
    unsigned short int y; // 2 bytes
    int  x; // 4 bytes
    unsigned short int z; // 2 bytes
    unsigned short int w; // 2 bytes
    char c; // 1 byte
    char d[3]; // 3 bytes
} ExtendedData;

typedef struct  __attribute__((packed)) {
    char a; // 1 byte
    char b; // 1 byte
    int  x; // 4 bytes
    unsigned short int y; // 2 bytes
    char c; // 1 byte
    unsigned short int z; // 2 bytes
    char d[3]; // 3 bytes
} BaseDataPacked;

#endif

