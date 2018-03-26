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

#include "options.h"

#include "taptempo_config.h"
#include <libintl.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

const unsigned int Options::defaultSampleSize = 5;
const unsigned int Options::defaultResetTime = 5;
const unsigned int Options::defaultPrecision = 0;
const unsigned int Options::maxPrecision = 5;

static struct option longOptions[] =
{
    {"help",    no_argument,    0, 'h'},
    {"version", no_argument,    0, 'v'},
    {"sample-size", required_argument,  0, 's'},
    {"reset-time",  required_argument,  0, 'r'},
    {"precision",  required_argument,  0, 'p'},
    {0, 0, 0, 0}
};

Options Options::createFromArgs(int argc, char **argv)
{
    Options options;

    bool shouldPrintHelp = false;
    bool shouldPrintVersion = false;

    int optionIndex = 0;
    int c = 0;
    int conversionBuffer = 0;
    while((c = getopt_long (argc, argv, "hvs:r:p:", longOptions, &optionIndex)) != -1)
    {
        switch(c)
        {
            case 'h':
                shouldPrintHelp = true;
                options.shouldExit = true;
                break;
            case 'v':
                shouldPrintVersion = true;
                options.shouldExit = true;
                break;
            case '?':
                /* getopt_long already printed an error message. */
                options.shouldExit = true;
                break;
            case 's':
                conversionBuffer = atoi(optarg);
                if(conversionBuffer <= 0)
                {
                    options.sampleSize = Options::defaultSampleSize;
                }
                else
                {
                    options.sampleSize = conversionBuffer;
                }
                break;
            case 'r':
                conversionBuffer = atoi(optarg);
                if(conversionBuffer <= 0)
                {
                    options.resetTime = Options::defaultResetTime;
                }
                else
                {
                    options.resetTime = conversionBuffer;
                }
                break;
            case 'p':
                conversionBuffer = atoi(optarg);
                if(conversionBuffer <= 0)
                {
                    options.precision = Options::defaultPrecision;
                }
                else if(conversionBuffer > Options::maxPrecision)
                {
                    options.precision = Options::maxPrecision;
                }
                else
                {
                    options.precision = conversionBuffer;
                }
                break;
            default:
                break;
        }
    }

    if(shouldPrintHelp)
    {
        printHelp();
    }
    else if(shouldPrintVersion)
    {
        printVersion();
    }

    return options;
}

bool Options::getShouldExit() const
{
    return this->shouldExit;
}

unsigned int Options::getSampleSize() const
{
    return this->sampleSize;
}

unsigned int Options::getResetTime() const
{
    return this->resetTime;
}

unsigned int Options::getPrecision() const
{
    return this->precision;
}

Options::Options() :
    shouldExit(false),
    sampleSize(this->defaultSampleSize),
    resetTime(this->defaultResetTime),
    precision(this->defaultPrecision)
{

}

void Options::printVersion()
{
    printf(gettext("Tap Tempo %s\n"), TAPTEMPO_VERSION);
    printf(gettext("Copyright (C) 2017-2018 Francois Mazen\n"));
    printf(gettext("License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\nThis is free software: you are free to change and redistribute it.\nThere is NO WARRANTY, to the extent permitted by law.\n"));
}

void Options::printHelp()
{
    printVersion();
    printf("\n");
    printf(gettext("Usage: taptempo [options]\n"));
    printf("\n");
    printf(gettext("Options:\n"));
    printf(gettext("  -h, --help\t\tdisplay this help message\n"));
    printf(gettext("  -p, --precision\tset the decimal precision of the tempo display\n\t\t\tdefault is %i digits, max is %i digits\n"), Options::defaultPrecision, Options::maxPrecision);
    printf(gettext("  -r, --reset-time\tset the time in second to reset the computation\n\t\t\tdefault is %i seconds\n"), Options::defaultResetTime);
    printf(gettext("  -s, --sample-size\tset the number of samples needed to compute the tempo\n\t\t\tdefault is %i samples\n"), Options::defaultSampleSize);
    printf(gettext("  -v, --version\t\tdisplay the version\n"));
    printf("\n");
}

