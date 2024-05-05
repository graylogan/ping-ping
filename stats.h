#ifndef STATS_H
#define STATS_H

using namespace std;

vector<string> getTimestamps(string pid) {
    void *vTimestamps = new vector<string>();
    execute("SELECT DISTINCT TIMESTAMP FROM GAME WHERE F_PID = " + pid + " OR S_PID = " + pid + ";", callbackMatchesPlayed, vTimestamps);
    return *static_cast<vector<string>*>(vTimestamps);
}

pair<int, int> getPoints(string pid) {
    void* vPoints = new pair<int, int>();
    execute("SELECT F_SCORE, F_EDGE FROM GAME WHERE F_PID = " + pid + ";", callbackGamePoints, vPoints);
    execute("SELECT S_SCORE, S_EDGE FROM GAME WHERE S_PID = " + pid + ";", callbackGamePoints, vPoints);
    return *static_cast<pair<int, int>*>(vPoints);
}

int getMatchesWon(string pid, vector<string> timestamps) {
    int matchesWon = 0;
    for (auto it = timestamps.begin(); it != timestamps.end(); it++) {
        // get number of associated games
        void *vGames = new int();
        execute("SELECT count(*) FROM (SELECT * FROM GAME WHERE TIMESTAMP = '" + *it + "');", callbackCount, vGames);
        int numGames = *static_cast<int*>(vGames);

        // get number of associated winning games
        execute("SELECT count(*) FROM (SELECT * FROM GAME WHERE TIMESTAMP = '" + *it
        + "' AND ((F_PID = " + pid + " AND F_SCORE > S_SCORE) OR (S_PID = " + pid + " AND S_SCORE > F_SCORE)));", callbackCount, vGames);
        int winGames = *static_cast<int*>(vGames);

        // add to count if won more than half
        if (winGames > numGames / 2) {
            matchesWon++;
        }
    }
    return matchesWon;
}

int getRSweeps(string pid, vector<string> timestamps) {
    int matchesWon = 0, totalGames = 0, gamesWon = 0, sweeps = 0, rSweeps = 0;
    for (auto it = timestamps.begin(); it != timestamps.end(); it++) {
        // get number of associated games
        void *vGames = new int();
        execute("SELECT count(*) FROM (SELECT * FROM GAME WHERE TIMESTAMP = '" + *it + "');", callbackCount, vGames);
        int numGames = *static_cast<int*>(vGames);
        totalGames += numGames;

        // check rSweep conditions
        void *vCount = new int(numGames / 2);
        for (int i = 0; i < numGames / 2; i++) {
            execute("SELECT * FROM GAME WHERE GAME_NUM = " + to_string(i + 1) + " AND TIMESTAMP = '" + *it
        + "' AND ((F_PID = " + pid + " AND F_SCORE < S_SCORE) OR (S_PID = " + pid + " AND S_SCORE < F_SCORE));", callbackDecLosses, vCount);
        }

        // get number of associated winning games
        execute("SELECT count(*) FROM (SELECT * FROM GAME WHERE TIMESTAMP = '" + *it
        + "' AND ((F_PID = " + pid + " AND F_SCORE > S_SCORE) OR (S_PID = " + pid + " AND S_SCORE > F_SCORE)));", callbackCount, vGames);
        int winGames = *static_cast<int*>(vGames);
        gamesWon += winGames;

        // add to count if won more than half
        if (winGames > numGames / 2) {
            matchesWon++;
            if (winGames == numGames)
                sweeps++;
            else if (!*static_cast<int*>(vCount))
                rSweeps++;
        }
    }
    return rSweeps;
}

int getSweeps(string pid, vector<string> timestamps) {
    int matchesWon = 0, totalGames = 0, gamesWon = 0, sweeps = 0, rSweeps = 0;
    for (auto it = timestamps.begin(); it != timestamps.end(); it++) {
        // get number of associated games
        void *vGames = new int();
        execute("SELECT count(*) FROM (SELECT * FROM GAME WHERE TIMESTAMP = '" + *it + "');", callbackCount, vGames);
        int numGames = *static_cast<int*>(vGames);
        totalGames += numGames;

        // get number of associated winning games
        execute("SELECT count(*) FROM (SELECT * FROM GAME WHERE TIMESTAMP = '" + *it
        + "' AND ((F_PID = " + pid + " AND F_SCORE > S_SCORE) OR (S_PID = " + pid + " AND S_SCORE > F_SCORE)));", callbackCount, vGames);
        int winGames = *static_cast<int*>(vGames);
        gamesWon += winGames;

        // add to count if won more than half
        if (winGames > numGames / 2) {
            matchesWon++;
            if (winGames == numGames)
                sweeps++;
        }
    }
    return sweeps;
}

int getGames(string pid, vector<string> timestamps) {
    int totalGames = 0;
    for (auto it = timestamps.begin(); it != timestamps.end(); it++) {
        // get number of associated games
        void *vGames = new int();
        execute("SELECT count(*) FROM (SELECT * FROM GAME WHERE TIMESTAMP = '" + *it + "');", callbackCount, vGames);
        int numGames = *static_cast<int*>(vGames);
        totalGames += numGames;
    }
    return totalGames;
}

int getGamesWon(string pid, vector<string> timestamps) {
    int gamesWon = 0;
    for (auto it = timestamps.begin(); it != timestamps.end(); it++) {
        // get number of associated winning games
        void *vGames = new int();
        execute("SELECT count(*) FROM (SELECT * FROM GAME WHERE TIMESTAMP = '" + *it
        + "' AND ((F_PID = " + pid + " AND F_SCORE > S_SCORE) OR (S_PID = " + pid + " AND S_SCORE > F_SCORE)));", callbackCount, vGames);
        int winGames = *static_cast<int*>(vGames);
        gamesWon += winGames;
    }
    return gamesWon;
}

#endif