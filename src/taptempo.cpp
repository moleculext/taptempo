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
#include <libintl.h>

TapTempo::TapTempo(size_t sampleSize) :
    sampleSize(sampleSize)
{
    if(this->sampleSize == 0)
    {
        this->sampleSize = 1;
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

int TapTempo::run()
{
    int returnCode = 0;
    
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
            this->hitTimePoints.push(getCurrentTime());
            if(this->hitTimePoints.size() > 1)
            {
                printf("\r");
                printf(gettext("Tempo: %.2f bpm\t"), computeBPM(this->hitTimePoints.back(), this->hitTimePoints.front(), this->hitTimePoints.size() - 1));
            }

            while (this->hitTimePoints.size() > this->sampleSize)
            {
                this->hitTimePoints.pop();
            }
        }
    }
    
    return returnCode;
}
