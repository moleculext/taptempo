#include <iostream>

#include "taptempo.h"
#include "taptempo_config.h"

#define DEFAULT_SAMPLE_SIZE 5

int main() 
{
	std::cout << "TAP TEMPO v" <<  TapTempo_VERSION << std::endl;
    std::cout << "Hit enter key for each beat (q to quit)." << std::endl;

	TapTempo tapTempo(DEFAULT_SAMPLE_SIZE);

	return tapTempo.run();
}
