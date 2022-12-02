#ifndef EXECUTEBINARYS_H_
#define EXECUTEBINARYS_H_
#define MAX_LENGHT 301

void spawn (char*, char* [], char*, char*);
void executeNormal(char*, char* [], char*, char*);
void executeBackground(char*, char* [], char*, char*);
void handler(int);
void executeBinary(char [MAX_LENGHT], char*, char*);
void executePipes(char [MAX_LENGHT], char*, char*);
void processPipe(int, char *[], char*, char*);

#endif