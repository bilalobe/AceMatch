#ifndef MATCHSCHEDULE_H
#define MATCHSCHEDULE_H

#include <vector>
#include "Match.h"

class MatchSchedule {
public:
    void addMatch(const Match& match);
    std::vector<Match> getMatches() const;
    void displaySchedule() const;

private:
    std::vector<Match> matches;
};

#endif // MATCHSCHEDULE_H
