/* TO-DO:
 * Fix REFERENCES constraint so it applies to new tuples
 * Option to add paddles to a player
 * Track first server for each game
 * Make function parameters const pass by reference where possible
*/


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
void addGame(string datetime, string p1, string p1Name, string p2, string p2Name, int gameNum);

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
    string fname, lname, residence, grip, height, weight, age;
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
    string brand, tier, design;
    vector<pair<string, bool>> values;

    // collect attribute data
    cout << "On each of the following lines, input the ball information:" << endl;
    while (brand == "") { // names are required
        cout << "Brand: ";
        getline(cin, brand);
    }
    while (tier == "") {
        cout << "Tier: ";
        getline(cin, tier);
    }
    cout << "Design: ";
    getline(cin, design);

    // build query
    values.push_back(pair<string, bool>(brand, 1));
    values.push_back(pair<string, bool>(tier, 0));
    values.push_back(pair<string, bool>(design, 1));
    string query = "INSERT INTO BALL VALUES(" + buildValueList(values) + ");";

    // add ball
    execute(query, NULL, NULL);
}

void addMatch() {
    string numGamesStr, date, time, p1, p2;
    int numGames;

    // collect match information
    cout << "Enter the following information about the match:" << endl;
    while (date == "") {
    cout << "Day (YYYY-MM-DD): ";
    getline(cin, date);
    }
    while (time == "") {
        cout << "Time (HH:MM): "; // !!! need seconds??
        getline(cin, time);
    }
    while (p1 == "") {
        cout << "Player 1 ID: ";
        getline(cin, p1);
    }
    while (p2 == "") {
        cout << "Player 2 ID: ";
        getline(cin, p2);
    }
    while (numGamesStr == "") {
        cout << "Number of games in match: ";
        getline(cin, numGamesStr);
    }
    numGames = stoi(numGamesStr);
    
    // add match
    string value = "'" + date + " " + time + "'";
    execute("INSERT INTO MATCH VALUES(" + value + ");", NULL, NULL);

    // get player names
    string p1Name, p2Name;
    void *vp = new string();
    execute("SELECT FNAME FROM PLAYER WHERE ID = " + p1 + ";", callbackPlayerName, vp);
    string *sp = static_cast<string*>(vp);
    p1Name = *sp;
    if (p1Name == "") {
        cout << "There is no player with ID " << p1 << "." << endl;
        exit(69);
    }
    delete sp;
    sp = NULL;
    vp = new string();
    execute("SELECT FNAME FROM PLAYER WHERE ID = " + p2 + ";", callbackPlayerName, vp);
    sp = static_cast<string*>(vp);
    p2Name = *sp;
    if (p2Name == "") {
        cout << "There is no player with ID " << p2 << "." << endl;
        exit(69);
    }
    p1Name += " (" + p1 + ")";
    p2Name += " (" + p2 + ")";

    // add each game
    for (int i = 0; i < numGames; i++) {
        addGame(date + " " + time, p1, p1Name, p2, p2Name, i + 1);
    }
}

void addGame(string datetime, string p1, string p1Name, string p2, string p2Name, int gameNum) {
    vector<pair<string, bool>> values;
    string p1Points, p2Points, p1Edge, p2Edge, p1PadBrand, p1PadModel, p2PadBrand, p2PadModel, p1TableSide, ballBrand, ballTier;

    // collect game info
        cout << "On each of the following lines, input information about game #" << gameNum
            << " or press enter to skip (lines with an asterisk (*) cannot be skipped):" << endl;
        while (p1Points == "") {
            cout << "*Points by " << p1Name << ": ";
            getline(cin, p1Points);
        }
        while (p2Points == "") {
            cout << "*Points by " << p2Name << ": ";
            getline(cin, p2Points);
        }
        cout << "Edge points by " << p1Name << ": ";
        getline(cin, p1Edge);
        cout << "Edge points by " << p2Name << ": ";
        getline(cin, p2Edge);
        cout << "Paddle brand of " << p1Name << ": ";
        getline(cin, p1PadBrand);
        cout << "Paddle Model of " << p1Name << ": ";
        getline(cin, p1PadModel);
        cout << "Paddle brand of " << p2Name << ": ";
        getline(cin, p2PadBrand);
        cout << "Paddle Model of " << p2Name << ": ";
        getline(cin, p2PadModel);
        cout << "Table side of " << p1Name << " (N=1, E=2, S=3, W=4): ";
        getline(cin, p1TableSide);
        cout << "Ball Brand: ";
        getline(cin, ballBrand);
        cout << "Ball Tier: ";
        getline(cin, ballTier);

        // build query
        values.push_back(pair<string, bool>(to_string(gameNum), 0));
        values.push_back(pair<string, bool>(datetime, 1));
        values.push_back(pair<string, bool>(p1PadBrand, 1));
        values.push_back(pair<string, bool>(p1PadModel, 1));
        values.push_back(pair<string, bool>(p2PadBrand, 1));
        values.push_back(pair<string, bool>(p2PadModel, 1));
        values.push_back(pair<string, bool>(p1, 0));
        values.push_back(pair<string, bool>(p2, 0));
        values.push_back(pair<string, bool>(p1Edge, 0));
        values.push_back(pair<string, bool>(p2Edge, 0));
        values.push_back(pair<string, bool>(p1TableSide, 0));
        values.push_back(pair<string, bool>(p1Points, 0));
        values.push_back(pair<string, bool>(p2Points, 0));
        values.push_back(pair<string, bool>(ballBrand, 1));
        values.push_back(pair<string, bool>(ballTier, 0));

        // add game
        execute("INSERT INTO GAME VALUES(" + buildValueList(values) + ");", NULL, NULL);
}

void execute(string query, int (*callback)(void *, int, char **, char **), void *vp) {
    sqlite3 *db;
    char *err;
    int rc;

    // enable foreign key constraint
    query = "PRAGMA foreign_keys = ON; " + query;

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
    cout << "result: " << result << endl;
    return result;
}