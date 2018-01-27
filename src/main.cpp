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

#include <iostream>

#include <libintl.h>
#include <getopt.h>

#include "taptempo.h"
#include "taptempo_config.h"

#define DEFAULT_SAMPLE_SIZE 5
#define DEFAULT_RESET_TIME 5
#define DEFAULT_PRECISION 0
#define MAX_PRECISION 5

void printVersion()
{
    printf(gettext("Tap Tempo %s\n"), TAPTEMPO_VERSION);
    printf(gettext("Copyright (C) 2017-2018 Francois Mazen\n"));
    printf(gettext("License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\nThis is free software: you are free to change and redistribute it.\nThere is NO WARRANTY, to the extent permitted by law.\n"));
}

static struct option longOptions[] =
{
    {"help",    no_argument,    0, 'h'},
    {"version", no_argument,    0, 'v'},
    {"sample-size", required_argument,  0, 's'},
    {"reset-time",  required_argument,  0, 'r'},
    {"precision",  required_argument,  0, 'p'},
    {0, 0, 0, 0}
};

void printHelp()
{
    printVersion();
    printf("\n");
    printf(gettext("Usage: taptempo [options]\n"));
    printf("\n");
    printf(gettext("Options:\n"));
    printf(gettext("  -h, --help\t\tdisplay this help message\n"));
    printf(gettext("  -p, --precision\tset the decimal precision of the tempo display\n\t\t\tdefault is %i digits, max is %i digits\n"), DEFAULT_PRECISION, MAX_PRECISION);
    printf(gettext("  -r, --reset-time\tset the time in second to reset the computation\n\t\t\tdefault is %i seconds\n"), DEFAULT_RESET_TIME);
    printf(gettext("  -s, --sample-size\tset the number of sample needed to compute the tempo\n\t\t\tdefault is %i samples\n"), DEFAULT_SAMPLE_SIZE);
    printf(gettext("  -v, --version\t\tdisplay the version\n"));
    printf("\n");
}

int main(int argc, char **argv) 
{
    // Setting the i18n environment.
    setlocale(LC_ALL, "");
    bindtextdomain(TAPTEMPO_PACKAGE_NAME, TAPTEMPO_LOCALE_DIR);
    textdomain(TAPTEMPO_PACKAGE_NAME);
    
    // Parse the command line arguments.
    bool shouldExit = false;

    int sampleSize = DEFAULT_SAMPLE_SIZE;
    int resetTime = DEFAULT_RESET_TIME;
    int precision = DEFAULT_PRECISION;
    
    int optionIndex = 0;
    int c = 0;
    while((c = getopt_long (argc, argv, "hvs:r:p:", longOptions, &optionIndex)) != -1)
    {
        switch(c)
        {
            case 'h':
                printHelp();
                shouldExit = true;
                break;
            case 'v':
                printVersion();
                shouldExit = true;
                break;
            case '?':
                /* getopt_long already printed an error message. */
                shouldExit = true;
                break;
            case 's':
                sampleSize = atoi(optarg);
                if(sampleSize <= 0)
                {
                    sampleSize = DEFAULT_SAMPLE_SIZE;
                }
                break;
            case 'r':
                resetTime = atoi(optarg);
                if(resetTime <= 0)
                {
                    resetTime = DEFAULT_RESET_TIME;
                }
                break;
            case 'p':
                precision = atoi(optarg);
                if(precision <= 0)
                {
                    precision = DEFAULT_PRECISION;
                }
                else if(precision > MAX_PRECISION)
                {
                    precision = MAX_PRECISION;
                }
                break;
            default:
                break;
        }
    }

    int exitCode = 0;
    if(!shouldExit)
    {
        TapTempo tapTempo(sampleSize, resetTime, precision);
        exitCode = tapTempo.run();
    }

    return exitCode;
}
