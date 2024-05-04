#include <iostream>
#include <fstream>
#include <sqlite3.h>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;

static int callback(void *passedValue, int argc, char **argv, char **colName); // sqlite3_exec() returns query tuples here
void usage(); // prints usage info and exits with status 1
void init(); // reads sql file to configure schemas and create empty database
void demo(); // creates a database populated with example tuples to demonstrate functionality
void print();

int main(int argc, char *argv[]) {
    // switch first argument that was passed
    if (argc <= 1) // quit if no arguments were passed
        usage();
    if (!strcmp(argv[1], "init")) {
        init();
        cout << "New database initialized" << endl;
    }
    else if (!strcmp(argv[1], "demo")) {
        demo();
        cout << "Demo database has been configured" << endl;
    }
    else if (!strcmp(argv[1], "print")) {
        print();
    }
    return 0;
}

static int callback(void *passedValue, int argc, char **argv, char **colName) { // gets called for every row of result
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", colName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

void usage() {
    cout << "Usage: lol" << endl;
    exit(69);
}

void init() {
    vector<string> queries;
    ifstream fin;
    string str;
    sqlite3 *db;
    char *err;
    int rc;
    
    // prompt user if database already exists
    fin.open("ping.db");
    if (fin.good()) {
        cout << "You are about to reset the database. All existing data will be lost. Are you sure you want to continue [y/n]?: ";
        char c;
        cin.get(c);
        if (c != 'y') {
            cout << "reset cancelled" << endl;
            exit(43);
        }
    }
    fin.close();

    // remove existing database
    remove("ping.db");

    // open and connect database to db
    if (sqlite3_open("ping.db", &db)) {
        cout << "Failed to open database" << endl;
        exit(69);
    }

    // read in queries
    fin.open("init.sql");
    if (!fin.good()) {
        cout << "Failed to read sql file" << endl;
        exit(69);
    }
    while (getline(fin, str, ';')) {
        queries.push_back(str + ';');
    }

    // execute queries to initialize database
    for (auto it = queries.begin(); it != queries.end(); it++) {
        rc = sqlite3_exec(db, it->c_str(), callback, 0, &err);
        if (rc != 0) {
            cout << err << endl;
            sqlite3_free(err);
        }
    }

    // close db connection
    sqlite3_close(db);    
}

void demo() {
    vector<string> queries;
    ifstream fin;
    string str;
    sqlite3 *db;
    char *err;
    int rc;

    // start by creating empty database
    init();

    // open and connect database to db
    if (sqlite3_open("ping.db", &db)) {
        cout << "Failed to open database" << endl;
        exit(69);
    }

    // read in queries
    fin.open("demo.sql");
    if (!fin.good()) {
        cout << "Failed to read sql file" << endl;
        exit(69);
    }
    while (getline(fin, str, ';')) {
        queries.push_back(str + ';');
    }

    // execute queries to populate database
    for (auto it = queries.begin(); it != queries.end(); it++) {
        rc = sqlite3_exec(db, it->c_str(), callback, 0, &err);
        if (rc != 0) {
            cout << err << endl;
            sqlite3_free(err);
        }
    }

    // close db connection
    sqlite3_close(db);
}

void print() {
    sqlite3 *db;
    char *err;
    int rc;

    // open and connect database to db
    if (sqlite3_open("ping.db", &db)) {
        cout << "Failed to open database" << endl;
        exit(69);
    }

    rc = sqlite3_exec(db, "SELECT * FROM PLAYER;", callback, 0, &err);
    if (rc != 0) {
        cout << err << endl;
        sqlite3_free(err);
    }

    rc = sqlite3_exec(db, "SELECT * FROM PADDLE;", callback, 0, &err);
    if (rc != 0) {
        cout << err << endl;
        sqlite3_free(err);
    }

    rc = sqlite3_exec(db, "SELECT * FROM PADDLE_COLOR;", callback, 0, &err);
    if (rc != 0) {
        cout << err << endl;
        sqlite3_free(err);
    }

    rc = sqlite3_exec(db, "SELECT * FROM BALL;", callback, 0, &err);
    if (rc != 0) {
        cout << err << endl;
        sqlite3_free(err);
    }

    rc = sqlite3_exec(db, "SELECT * FROM MATCH;", callback, 0, &err);
    if (rc != 0) {
        cout << err << endl;
        sqlite3_free(err);
    }

    rc = sqlite3_exec(db, "SELECT * FROM GAME;", callback, 0, &err);
    if (rc != 0) {
        cout << err << endl;
        sqlite3_free(err);
    }

    rc = sqlite3_exec(db, "SELECT * FROM OWNS;", callback, 0, &err);
    if (rc != 0) {
        cout << err << endl;
        sqlite3_free(err);
    }

    // close db connection
    sqlite3_close(db);
}