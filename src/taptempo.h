
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
