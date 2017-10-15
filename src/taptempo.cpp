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
