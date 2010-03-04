
#ifndef CAREFUL_H
#define CAREFUL_H


class LandingScheduler
{
public:
    void resetLandingScheduler(int n);
    void insertLandingInterval(int begin , int end);
    void findSolution(void);
private:
    enum intersectionRetVals
    {
        NoIntersection,         //two intervals dont intersect
        HasIntersection,        //two intervals intersect
        SameInterval,           //two intervals have same begin and end
        IntervalItsself         //it is the interval itsself
    };
    enum landingCheckRetVals
    {
        BeforeInterval,         //suggested landing time falls before the interval
        InsideInterval,         //suggested landing time is in the interval
        AfterInterval,          //suggested landing time falls after the interval 
        landingConfirmed,       //landing time is set for this interval
        landingUnconfirmed      //landing time is not yet set for this interval
    };
    struct LandingInterval {
        int index;
        bool isUsed;
        int begin;
        int end;
    };
    struct Suggestion {
        int sortedIndex;
        landingCheckRetVals intervalCheck;
        int landingTimeConf;
        int landingTimeSug;
    };

    int numberOfLandings;
    LandingInterval     sortedLandingIntervals[9];
    int                 intersectionList[9][9];
    Suggestion          suggestionArray[9];
    Suggestion          bestScheduleSoFar[9];
    unsigned int        bestMinimumSoFar;

    void fillIntersectionList (void);
    void tryAllPossibleLandings(int& Depth);
    bool isLandingSuggestionPossible(void);
    intersectionRetVals hasIntersection (int index1, int index2);
    landingCheckRetVals checkLandingForInterval(int landingIime , int landingSecond);
    void findSolutionArray(void);
    bool allLandingsConfirmed(void);
    void processInterval(int begin , int end);
    void checkConfirmedSuggestion(void);
    void printSolution(void);
    int  getSolution(void);
};




















#endif //CAREFUL.H
