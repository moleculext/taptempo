#include <iostream>

#include <libintl.h>

#include "taptempo.h"
#include "taptempo_config.h"

#define DEFAULT_SAMPLE_SIZE 5

int main() 
{
    // Setting the i18n environment.
    setlocale(LC_ALL, "");
    bindtextdomain(TAPTEMPO_PACKAGE_NAME, TAPTEMPO_LOCALE_DIR);
    textdomain(TAPTEMPO_PACKAGE_NAME);
  
    printf(gettext("TAP TEMPO v%s\n"), TAPTEMPO_VERSION);
    printf(gettext("Hit enter key for each beat (q to quit).\n"));

    TapTempo tapTempo(DEFAULT_SAMPLE_SIZE);

    return tapTempo.run();
}
