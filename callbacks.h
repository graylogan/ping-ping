#ifndef CALLBACKS_H
#define CALLBACKS_H

/*#include <iostream>
#include <cstdio>
#include <string>
*/

using namespace std;

static int callback(void * sharedMemory, int argc, char **argv, char **colName) { // gets called for every row of result
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", colName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

static int callbackAddPlayer(void * sharedMemory, int argc, char **argv, char **colName) { // loads shared memory with max player ID
   int *iValue = static_cast<int*>(sharedMemory);
   *iValue = (argv[0] == NULL ? 0 : stoi(string(argv[0])));
   return 0;
}

static int callbackPlayerName(void * sharedMemory, int argc, char **argv, char **colName) {
   string *sValue = static_cast<string*>(sharedMemory);
   *sValue = string(argv[0]);
   return 0;
}

static int callbackPlayerInfo(void * sharedMemory, int argc, char **argv, char **colName) {
   string attributes[7] = {"ID", "Name", "Residence", "Height", "Weight", "Age", "Grip"};
   cout << attributes[0] << ": " << argv[0] << endl;
   cout << attributes[1] << ": " << argv[1] << " " << argv[2] << endl;
   for (int i = 2; i < 7; i++) {
      cout << attributes[i] << ": " << (argv[i + 1] == NULL ? "NULL" : argv[i + 1]) << endl;
   }
   cout << endl;
   return 0;
}

static int callbackMatchesPlayed(void * sharedMemory, int argc, char **argv, char **colName) {
   vector<string> *value = static_cast<vector<string>*>(sharedMemory);
   value->push_back(string(argv[0]));
   return 0;
}

static int callbackCount(void * sharedMemory, int argc, char **argv, char **colName) {
   int *value = static_cast<int*>(sharedMemory);
   *value = stoi(string(argv[0]));
   return 0;
}

static int callbackDecLosses(void * sharedMemory, int argc, char **argv, char **colName) {
   int *value = static_cast<int*>(sharedMemory);
   *value -= 1;
   return 0;
}

static int callbackGamePoints(void * sharedMemory, int argc, char **argv, char **colName) {
   pair<int, int> *value = static_cast<pair<int, int>*>(sharedMemory);
   value->first += stoi(string(argv[0]));
   value->second += (argv[1] == NULL ? 0 : stoi(string(argv[1])));
   return 0;
}

static int callbackPlayerIDs(void * sharedMemory, int argc, char **argv, char **colName) {
   vector<string> *value = static_cast<vector<string>*>(sharedMemory);
   value->push_back(string(argv[0]));
   return 0;
}

static int callbackNameFromID(void * sharedMemory, int argc, char **argv, char **colName) {
   string *sValue = static_cast<string*>(sharedMemory);
   *sValue = string(argv[0]) + " " + string(argv[1]);
   return 0;
}

#endif