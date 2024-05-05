#ifndef EXECUTE_H
#define EXECUTE_H

#include <sqlite3.h>
#include <iostream>
#include <string>
using namespace std;

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

#endif