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

#include <chrono>
#include <queue>

class TapTempo
{
public:
    TapTempo(size_t sampleSize);
    
    int run();
    
private:
    typedef std::chrono::steady_clock::time_point TIME_POINT;
    
    TIME_POINT getCurrentTime() const;
    double computeBPM(const TIME_POINT& currentTime, const TIME_POINT& lastTime, size_t occurenceCount) const;
    
    size_t sampleSize;
    std::queue<TIME_POINT> hitTimePoints;
    
};
