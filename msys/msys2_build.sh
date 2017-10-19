#!/bin/bash

#    TapTempo, a command line tap tempo.
#    Copyright (C) 2017 Francois Mazen
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https:#www.gnu.org/licenses/>.

START_TIME=$SECONDS

function check_return_code
{
	if [ $1 -ne 0 ]
	then
		(>&2 echo "BUILD FAILED")
		exit $1
	fi
}

BUILD_INDEX=$(date +%Y%m%d%H%M%S)
RELEASE_FOLDER=${BUILD_INDEX}

echo =================================
echo Create root folder $RELEASE_FOLDER
echo =================================
mkdir $RELEASE_FOLDER
check_return_code $?
cd $RELEASE_FOLDER
check_return_code $?

echo ========
echo Build 64
echo ========

cmake -G "MSYS Makefiles" ../..
check_return_code $?

make
check_return_code $?

make DESTDIR="output" install
check_return_code $?

echo =====================
echo Copy DLL dependencies
echo =====================

python ../mingw-bundledlls.py --copy "$PWD/output/Program Files (x86)/taptempo/taptempo.exe"
check_return_code $?

echo ===
echo End
echo ===
ELAPSED_TIME=$(($SECONDS - $START_TIME))
echo "$(($ELAPSED_TIME/60)) min $(($ELAPSED_TIME%60)) sec"

echo "BUILD SUCCESS"

exit 0

