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


class Options
{
public:
    static Options createFromArgs(int argc, char **argv);

    bool getShouldExit() const;
    unsigned int getSampleSize() const;
    unsigned int getResetTime() const;
    unsigned int getPrecision() const;

private:
    Options();

    static void printVersion();
    static void printHelp();

    bool shouldExit;
    unsigned int sampleSize;
    unsigned int resetTime;
    unsigned int precision;

    // Default values.
    static const unsigned int defaultSampleSize;
    static const unsigned int defaultResetTime;
    static const unsigned int defaultPrecision;
    static const unsigned int maxPrecision;
};
