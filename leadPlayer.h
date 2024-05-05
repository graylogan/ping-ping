#ifndef LEADPLAYER_H
#define LEADPLAYER_H

#include <string>
using namespace std;

template <class T>
class LeadPlayer {
    public:
    string name, id;
    T stat;

    LeadPlayer<T>(string name, string id, T stat) {
        this->name = name;
        this->id = id;
        this->stat = stat;
    }

    bool operator<(LeadPlayer RHS) {
        return (stat < RHS.stat);
    }
};

#endif