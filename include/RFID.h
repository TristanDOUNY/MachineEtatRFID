#ifndef RFID_H
#define RFID_H

#include "config.h"

// Déclaration des fonctions
void rfid_init();
void rfidddd();
bool rfid1Block(byte block );
int** processMatrix(int* matriceNonDecode);
int** matrixToNodes(int** matrix);
int* dijkstra(int** nodes, int start[]);
int* path (int* prev,int goal[], int start[]);
int* antecedant(int* prev, int goal[], int start[]);
char deterDir(int startNode[]);
int indicePath(int* pathdijk1);
int* seqInstruct2(int* pathdijk, int startNode[]);
bool isNodeInPath(int* pathdijk, int shortNode[]);
#endif