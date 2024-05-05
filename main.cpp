#include <iostream>
#include <fstream>
#include <sqlite3.h>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include "callbacks.h"
#include "print.h"
using namespace std;

void usage(); // prints usage info and exits with status 1
void init(); // reads sql file to configure schemas and create empty database
void demo(); // creates a database populated with example tuples to demonstrate functionality
void addPlayer();
void addPaddle();
void addBall();
void addMatch();

void execute(string query, int (*callback)(void *, int, char **, char **), void *vp);

int main(int argc, char *argv[]) {
    // switch first command line argument
    if (argc <= 1)
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

    else if (!strcmp(argv[1], "add")) {
        if (argc <= 2)
            usage();
        else if (!strcmp(argv[2], "player"))
            addPlayer();
        else if (!strcmp(argv[2], "paddle"))
            addPaddle();
        else if (!strcmp(argv[2], "ball"))
            addBall();
        else if (!strcmp(argv[2], "match"))
            addMatch();
        else
            usage();
    }

    else {
        usage();
    }
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

void addPlayer() {
    string fname = "", lname = "", residence, grip, height, weight, age;

    // collect attribute data
    cout << "On each of the following lines, input the player information or press enter to skip (lines with an asterisk (*) cannot be skipped):" << endl;
    while (fname == "") { // names are required
        cout << "*First name: ";
        getline(cin, fname);
    }
    while (lname == "") {
        cout << "*Last name: ";
        getline(cin, lname);
    }
    cout << "Residence: ";
    getline(cin, residence);
    cout << "Height: ";
    getline(cin, height);
    cout << "Weight: ";
    getline(cin, weight);
    cout << "Age: ";
    getline(cin, age);
    cout << "Grip: ";
    getline(cin, grip);
    
    // get next available ID
    void *vmaxID = new int(0); // shares memory with callback
    execute("SELECT max(ID) FROM PLAYER;", callbackAddPlayer, vmaxID);
    int *maxID = static_cast<int*>(vmaxID); // convert to int* to access data
    string newID = to_string((*maxID) + 1);

    // build query
    string query = "INSERT INTO PLAYER VALUES(" + newID + ", '" + fname + "', '" + lname + "', "
        + (residence == "" ? "NULL" : ("'" + residence + "'")) + ", " + (height == "" ? "NULL" : height) + ", "
        + (weight == "" ? "NULL" : weight) + ", " + (age == "" ? "NULL" : age) + ", "
        + (grip == "" ? "NULL" : ("'" + grip + "'")) + ");";
    
    // add player
    execute(query, NULL, NULL);
}

void addPaddle() {

}

void addBall() {

}

void addMatch() {

}

void execute(string query, int (*callback)(void *, int, char **, char **), void *vp) {
    sqlite3 *db;
    char *err;
    int rc;

    // open and connect database to db
    if (sqlite3_open("ping.db", &db)) {
        cout << "Failed to open database" << endl;
        exit(69);
    }

    // execute query
    rc = sqlite3_exec(db, query.c_str(), callback, vp, &err); // execute query
    if (rc != 0) {
        cout << err << endl;
        sqlite3_free(err);
    }

    // close db connection
    sqlite3_close(db);
}