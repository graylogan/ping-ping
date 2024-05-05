#ifndef PRINT_H
#define PRINT_H

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

#endif