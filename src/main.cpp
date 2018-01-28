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

#include "taptempo.h"
#include "taptempo_config.h"

#include "options.h"

int main(int argc, char **argv) 
{
    // Setting the i18n environment.
    setlocale(LC_ALL, "");
    bindtextdomain(TAPTEMPO_PACKAGE_NAME, TAPTEMPO_LOCALE_DIR);
    textdomain(TAPTEMPO_PACKAGE_NAME);
    
    // Parse the command line arguments.
    Options options = Options::createFromArgs(argc, argv);

    int exitCode = 0;
    if(!options.getShouldExit())
    {
        TapTempo tapTempo(options.getSampleSize(), options.getResetTime(), options.getPrecision());
        exitCode = tapTempo.run();
    }

    return exitCode;
}
