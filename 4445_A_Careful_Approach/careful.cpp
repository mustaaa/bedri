
#include "careful.h"
#include "math.h"
#include <iostream>

using namespace std;

#define END_OF_LIST (-1)

void LandingScheduler::resetLandingScheduler(int n)
{
    numberOfLandings=n;
    for (int i=0 ; i<9 ; i++)
    {
        /*sortedLandingIntervals[i].index=i;
        if(i==8)
            */sortedLandingIntervals[i].index=END_OF_LIST;
        sortedLandingIntervals[i].isUsed=false;
        sortedLandingIntervals[i].begin=sortedLandingIntervals[i].end=0;
            
        for (int k=0 ; k<9 ; k++)
            intersectionList[i][k]=END_OF_LIST;

        suggestionArray[i].sortedIndex=bestScheduleSoFar[i].sortedIndex=END_OF_LIST;
    }
    bestMinimumSoFar=0;
    return;
}

void LandingScheduler::findSolution(void)
{
    int n=0;
    fillIntersectionList();
    tryAllPossibleLandings(n);
    printSolution();

}
int  LandingScheduler::getSolution(void)
{
    return bestMinimumSoFar;
}
void LandingScheduler::printSolution(void)
{
    cout<<"\n\ngreatest smallest interval is "<<bestMinimumSoFar/60<<":"<<bestMinimumSoFar%60<< " min long";
    cout<<"\none of the satisfying schedules is :";
    for (int i=0; i<numberOfLandings ; i++)
    {
        cout<<"\n"<<bestScheduleSoFar[i].sortedIndex+1<<"-"<<bestScheduleSoFar[i].landingTimeConf/60<<":"<<bestScheduleSoFar[i].landingTimeConf%60;
    }
}

LandingScheduler::intersectionRetVals LandingScheduler::hasIntersection (int index1, int index2)
{
    if (index1 == index2)
        return IntervalItsself;
    if (sortedLandingIntervals[index1].begin == sortedLandingIntervals[index2].begin &&
        sortedLandingIntervals[index1].end   == sortedLandingIntervals[index2].end
        )
        return SameInterval;
    if ( InsideInterval == checkLandingForInterval(index1 , sortedLandingIntervals[index2].begin) || 
         InsideInterval == checkLandingForInterval(index2 , sortedLandingIntervals[index1].begin)
        )
        return HasIntersection;
    return NoIntersection;
}

LandingScheduler::landingCheckRetVals LandingScheduler::checkLandingForInterval (int intervalIndex, int landingSecond)
{
    if (sortedLandingIntervals[intervalIndex].begin > landingSecond)
        return BeforeInterval;
    if (sortedLandingIntervals[intervalIndex].end < landingSecond)
        return AfterInterval;
    return InsideInterval;
}



void LandingScheduler::fillIntersectionList (void)
{
    int sortedLandingIntervalsIndex = 0;
    int ColIndex = 0;                       // coloumn index for intersectionList
    int rowIndex = 0;                       // row index for intersectionList

    for (int i = 0 ; i < numberOfLandings ; i++)    //coloumn index for intersectionList and sortedLandingIntervals
    {
        for (int k = 0 ; k < numberOfLandings ; k++)    //to go through the sortedLandingIntervals
        {
            switch (hasIntersection(i,k))
            {
            case NoIntersection:
                // do nothing
                break;
            case HasIntersection:
            case IntervalItsself:
                // put this flight to the intersection list of that i'th flight
                intersectionList[i][rowIndex] = k;
                rowIndex++;
                break;
            case SameInterval:
                // if they have the same interval it does not matter which one is the first do not enter it in their intersection lists - optimization -
                break;
            }
        }
        rowIndex = 0;
    }
}

void LandingScheduler::tryAllPossibleLandings(int& Depth)  // recursive, start with 0 depth
{
    int index = 0;
    while( intersectionList[Depth][index]!=END_OF_LIST )
    {
        if (!sortedLandingIntervals[intersectionList[Depth][index]].isUsed)
        {
            suggestionArray[Depth].sortedIndex  = intersectionList[Depth][index];                 // copy this into suggestion array
            sortedLandingIntervals[intersectionList[Depth][index]].isUsed=true;     // this interval is used, do not use this anymore
            if (intersectionList[Depth+1][0] == END_OF_LIST)                        // if we have reached the end of intersection list. make a landing suggestion
            {
                if (isLandingSuggestionPossible())
                    findSolutionArray();
            }
            else    
            {
                tryAllPossibleLandings(++Depth);                                        // go deeper to form a suggestion array
            }
            sortedLandingIntervals[intersectionList[Depth][index]].isUsed=false;
            suggestionArray[Depth].sortedIndex = END_OF_LIST;                                   //we are finished with testin this landing order
        }
        index++;
    }
    Depth--;
    return;
}

bool LandingScheduler::isLandingSuggestionPossible(void)
{
    for (int i=0 ; i<(numberOfLandings-1) ; i++)
    {
        for (int k=(i+1) ; k<numberOfLandings ; k++)
        {
            // if a later landing in the suggestion list has a smaller index in sortedLandingIntervals i'th and k'th landings should have an intersection 
            // otherwise this is an imposible landing scenario, if ith and kth landings are the same it means there is a bug in code:)!
            if (sortedLandingIntervals[suggestionArray[k].sortedIndex].index < sortedLandingIntervals[suggestionArray[i].sortedIndex].index )
            {
                switch (hasIntersection(sortedLandingIntervals[suggestionArray[k].sortedIndex].index ,sortedLandingIntervals[suggestionArray[i].sortedIndex].index))
                {
                case NoIntersection:  //non intersecting kth landing cannot be earlier than ith (kth landing interval ends before ith)
                    return false;
                    break;
                case HasIntersection:
                case SameInterval:
                    break;      //do nothing
                case IntervalItsself:
                    // This case should never be: BUG!!!
                    break;
                }
            }
        }
    }
    return true;
}

void LandingScheduler::findSolutionArray(void)
{
    int begin, end, i;
    for (i=0;i<numberOfLandings;i++)
        suggestionArray[i].intervalCheck= landingUnconfirmed;
    // for the current suggestion list set the first landing as the first elements intervals begin time 
    suggestionArray[0].intervalCheck=landingConfirmed;
    suggestionArray[0].landingTimeConf = sortedLandingIntervals[suggestionArray[0].sortedIndex].begin;
    // for the current suggestion list set the last landing as the last elements intervals end time 
    suggestionArray[numberOfLandings-1].intervalCheck=landingConfirmed;
    suggestionArray[numberOfLandings-1].landingTimeConf = sortedLandingIntervals[suggestionArray[numberOfLandings-1].sortedIndex].end;

    while (!allLandingsConfirmed())
    {
        for (i=begin=0,end=1; i<numberOfLandings ; i++)
        {
            if (suggestionArray[begin].intervalCheck==landingConfirmed && suggestionArray[begin+1].intervalCheck!=landingConfirmed)
            {   // beginning of an interval means that beginth element is confirmed but the next one is not
                // do not increment begin anymore
            }
            else
            {
                begin++;
            }
            if (suggestionArray[end].intervalCheck==landingConfirmed && suggestionArray[end-1].intervalCheck!=landingConfirmed)
            {   // end of an interval means that endth element is confirmed but the previous one is not
                // do not increment end anymore, break the loop to call processInterval
                break;
            }
            else
            {
                end++;
            }
        }
        processInterval(begin,end);
    }
    // now all landings have been confirmed and scheduled do their ideal times for this particular order of landing, 
    // check against the best found so far
    checkConfirmedSuggestion();
}

void LandingScheduler::checkConfirmedSuggestion(void)
{
    unsigned int min=0;
    min--;  // set to Largest integer
    for (int i=0; i<numberOfLandings-1 ; i++ )
    {
        if (min > (suggestionArray[i+1].landingTimeConf - suggestionArray[i].landingTimeConf))
            min = suggestionArray[i+1].landingTimeConf - suggestionArray[i].landingTimeConf;
    }
    if (min > bestMinimumSoFar)
    {
        bestMinimumSoFar = min;
        for (int i=0; i<numberOfLandings ; i++)
        {
            bestScheduleSoFar[i]=suggestionArray[i];
        }
    }
}

bool LandingScheduler::allLandingsConfirmed(void)
{
    for (int i=0 ; i<numberOfLandings ; i++)
    {
        if (suggestionArray[i].intervalCheck!=landingConfirmed)
            return false;
    }
    return true;
}

void LandingScheduler::processInterval(int begin , int end)
{
    int intBeginSec = suggestionArray[begin].landingTimeConf;
    int intEndSec   = suggestionArray[end].landingTimeConf;
    int intSize     = intEndSec - intBeginSec; //(int) floor( ((double)(intEndSec - intBeginSec)/(double)end) + 0.5 );
    bool allInTheirOptimalPlace = true;
    for (int i=1; i<end-begin ; i++)    // fill in the intervalCheck parameter, it can be early late or in interval
    {
        suggestionArray[begin+i].landingTimeSug = intBeginSec + (int) floor( (double)((double)(intSize*i)/(double)(end-begin)) + 0.5 );
        suggestionArray[begin+i].intervalCheck=checkLandingForInterval(suggestionArray[begin+i].sortedIndex,suggestionArray[begin+i].landingTimeSug);
    }

    
    for (int i=1 ; i<end-begin ; i++)       //going from left to right first optimal point falling behind the landing interval of that plain
                                            //suggests that best landing time for that plain is the starting second of its interval
    {
        if (suggestionArray[begin+i].intervalCheck == BeforeInterval)
        {
            suggestionArray[begin+i].intervalCheck   = landingConfirmed;
            suggestionArray[begin+i].landingTimeConf = sortedLandingIntervals[suggestionArray[begin+i].sortedIndex].begin;
            allInTheirOptimalPlace = false;
            break; // break for loop
        }
        else if (suggestionArray[begin+i].intervalCheck==AfterInterval)   
            // here we ignore the case of landingConfirmed! it should never be the case  if it is so then we have problem
        {
            allInTheirOptimalPlace = false;
        }
    }

    for (int i=end-1 ; i>begin ; i--)       // going from right to left
    {
        if (suggestionArray[i].intervalCheck == AfterInterval)
        {
            suggestionArray[i].intervalCheck   = landingConfirmed;
            suggestionArray[i].landingTimeConf = sortedLandingIntervals[suggestionArray[i].sortedIndex].end;
            allInTheirOptimalPlace = false;
            break; // break for loop
        }
        else if (suggestionArray[i].intervalCheck==AfterInterval)   
            // here we ignore the case of landingConfirmed! it should never be the case  if it is so then we have problem
        {
            allInTheirOptimalPlace = false;
        }
    }
    if (allInTheirOptimalPlace)
    {
        for (int i=1 ; i<end-begin ; i++)
        {
            suggestionArray[begin+i].intervalCheck   = landingConfirmed;
            suggestionArray[begin+i].landingTimeConf = suggestionArray[begin+i].landingTimeSug;
        }
    }

}

void LandingScheduler::insertLandingInterval(int begin , int end)
{
    int cur = 0;
    LandingInterval interval ,tempInterval1 ,tempInterval2 ;
    
    interval.index  = END_OF_LIST;
    interval.isUsed = false;
    interval.begin  = begin*60;
    interval.end    = end*60;

    while (sortedLandingIntervals[cur].index!=END_OF_LIST && (sortedLandingIntervals[cur].begin <= interval.begin) )
        cur++;
    if (!cur)   // first element
    {
        interval.index = 0;
        sortedLandingIntervals[cur] = interval;
        return;
    }
    if( sortedLandingIntervals[cur].index!=END_OF_LIST  )   // somewhere inbetween
    {
        interval.index = sortedLandingIntervals[cur].index;
        tempInterval1  = sortedLandingIntervals[cur];
        tempInterval1.index++;
        sortedLandingIntervals[cur] = interval;
        cur++;

        while (sortedLandingIntervals[cur].index!=END_OF_LIST)
        {
            tempInterval2 = tempInterval1;
            tempInterval1 = sortedLandingIntervals[cur];
            tempInterval1.index++;
            sortedLandingIntervals[cur] = tempInterval2;
            cur++;
        }
        // now add the last element
        sortedLandingIntervals[cur]=tempInterval1;

    }
    else    // add to the end of list
    {
        interval.index = cur;
        sortedLandingIntervals[cur] = interval;
    }

}