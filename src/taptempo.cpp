//    TapTempo, a command line tap tempo.
//    Copyright (C) 2017 Francois Mazen
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "taptempo.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <libintl.h>

TapTempo::TapTempo(size_t sampleSize, size_t resetTimeInSecond, size_t precision) :
    sampleSize(sampleSize),
    resetTimeInSecond(resetTimeInSecond),
    precision(precision)
{
    if(this->sampleSize == 0)
    {
        this->sampleSize = 1;
    }
    
    if(this->resetTimeInSecond == 0)
    {
        this->resetTimeInSecond = 1;
    }
}

double TapTempo::computeBPM(const TapTempo::TIME_POINT& currentTime, const TapTempo::TIME_POINT& lastTime, size_t occurenceCount) const
{
    if (occurenceCount == 0)
    {
        occurenceCount = 1;
    }

    double elapsedTime = std::chrono::duration_cast<std::chrono::duration<double> >(currentTime - lastTime).count();
    double meanTime = elapsedTime / occurenceCount;
    double bpm = 60.0 / meanTime;

    return bpm;
}

TapTempo::TIME_POINT TapTempo::getCurrentTime() const
{
    return std::chrono::steady_clock::now();
}

bool TapTempo::isResetTimeElapsed(const TIME_POINT& currentTime, const TIME_POINT& lastTime) const
{
    double elapsedTime = std::chrono::duration_cast<std::chrono::duration<double> >(currentTime - lastTime).count();
    return elapsedTime > this->resetTimeInSecond;
}


int TapTempo::run()
{
    int returnCode = 0;

    printf(gettext("Hit enter key for each beat (q to quit).\n"));
    
    bool shouldContinue = true;
    while (shouldContinue)
    {
        int i = 0;
        do
        {
            i = std::cin.get();
            if(i == 'q')
            {
                shouldContinue = false;
                printf(gettext("Bye Bye!\n"));
                break;
            }
        } while (i != 10);

        if(shouldContinue)
        {
            TIME_POINT currentTime = getCurrentTime();
            
            // Reset if the hit diff is too big.
            if(!this->hitTimePoints.empty() && isResetTimeElapsed(currentTime, this->hitTimePoints.back()))
            {
                // Clear the history.
                while(!this->hitTimePoints.empty())
                {
                    this->hitTimePoints.pop();
                }
            }
            
            this->hitTimePoints.push(currentTime);
            if(this->hitTimePoints.size() > 1)
            {
                printf("\r");
                double bpm = computeBPM(this->hitTimePoints.back(), this->hitTimePoints.front(), this->hitTimePoints.size() - 1);
                std::stringstream bpmRepresentation;
                bpmRepresentation << std::fixed << std::setprecision(precision) << bpm;
                printf(gettext("Tempo: %s bpm\t"), bpmRepresentation.str().c_str());
            }
            else
            {
                printf("\r");
                printf(gettext("[Hit enter key one more time to start bpm computation...]"));
            }

            while (this->hitTimePoints.size() > this->sampleSize)
            {
                this->hitTimePoints.pop();
            }
        }
    }
    
    return returnCode;
}
