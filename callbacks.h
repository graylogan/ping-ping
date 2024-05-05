#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

static int callback(void *passedValue, int argc, char **argv, char **colName) { // gets called for every row of result
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", colName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

static int callbackAddPlayer(void *passedValue, int argc, char **argv, char **colName) {
   int *iValue = static_cast<int*>(passedValue);
   *iValue = (argv[0] == NULL ? 0 : stoi(string(argv[0])));
   return 0;
}

static int callbackPlayerName(void *passedValue, int argc, char **argv, char **colName) {
   string *sValue = static_cast<string*>(passedValue);
   *sValue = string(argv[0]);
   return 0;
}

#endif