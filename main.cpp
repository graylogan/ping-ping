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

// sets up db connection, executes query, and closes the connection, printing any errors that happen
void execute(string query, int (*callback)(void *, int, char **, char **), void *vp);
// takes vector of pairs where first value is the attribute value and the second is a bool for if it needs to be quoted in the query
// returns formated, comma-seperated list of values from the vector
string buildValueList(vector<pair<string, bool>> values);

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
        execute(*it, NULL, NULL);
    }
}

void demo() {
    vector<string> queries;
    ifstream fin;
    string str;

    // start by creating empty database
    init();

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
        execute(*it, NULL, NULL);
    }
}

void addPlayer() {
    string fname = "", lname = "", residence, grip, height, weight, age;
    vector<pair<string, bool>> values;

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
    values.push_back(pair<string, bool>(newID, 0));
    values.push_back(pair<string, bool>(fname, 1));
    values.push_back(pair<string, bool>(lname, 1));
    values.push_back(pair<string, bool>(residence, 1));
    values.push_back(pair<string, bool>(height, 0));
    values.push_back(pair<string, bool>(weight, 0));
    values.push_back(pair<string, bool>(age, 0));
    values.push_back(pair<string, bool>(grip, 1));
    string query = "INSERT INTO PLAYER VALUES(" + buildValueList(values) + ");";

    // add player
    execute(query, NULL, NULL);
}

void addPaddle() {
    string brand, model, weight, color;
    vector<pair<string, bool>> values;

    // collect attribute data
    cout << "On each of the following lines, input the paddle information:" << endl;
    while (brand == "") { // names are required
        cout << "Brand: ";
        getline(cin, brand);
    }
    while (model == "") {
        cout << "Model: ";
        getline(cin, model);
    }
    cout << "weight (optional): ";
    getline(cin, weight);

    // build query
    values.push_back(pair<string, bool>(brand, 1));
    values.push_back(pair<string, bool>(model, 1));
    values.push_back(pair<string, bool>(weight, 0));
    string query = "INSERT INTO PADDLE VALUES(" + buildValueList(values) + ");";

    // add paddle
    execute(query, NULL, NULL);

    // remove weight value if it exists
    if (values.size() == 3)
        values.pop_back();

    cout << "Enter as many paddle colors as you want, and press enter on an empty line when you are done." << endl;
    cout << "Color: ";
    getline(cin, color);
    while (color != "") { // colect color, add it to table, repeat
        values.push_back(pair<string, bool>(color, 1));
        query = "INSERT INTO PADDLE_COLOR VALUES(" + buildValueList(values) + ");";
        execute(query, NULL, NULL);
        values.pop_back();
        cout << "Color: ";
        getline(cin, color);
    }
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

string buildValueList(vector<pair<string, bool>> values) {
    string result = "";

    // add first value to result
    if (values[0].first == "") {
        result += "NULL";
    }
    else {
        if (values[0].second) {
            result += "'" + values[0].first + "'";
        }
        else {
            result += values[0].first;
        }
    }

    // add remaining values
    for (auto it = ++values.begin(); it != values.end(); it++) {
        result += ", ";
        if (it->first == "") {
            result += "NULL";
            continue;
        }
        if (it->second) {
            result += "'" + it->first + "'";
        }
        else {
            result += it->first;
        }
    }
    return result;
}