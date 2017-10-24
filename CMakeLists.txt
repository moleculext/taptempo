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
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.


cmake_minimum_required (VERSION 2.6)
project (taptempo)

set(TAPTEMPO_VERSION_MAJOR 1)
set(TAPTEMPO_VERSION_MINOR 1)
set(TAPTEMPO_VERSION_REVISION 2)
set(TAPTEMPO_PACKAGE_NAME taptempo)

if(MSYS)
	set(TAPTEMPO_LOCALE_DIR "share/locale")
	set(TAPTEMPO_INSTALL_DIR ${CMAKE_INSTALL_PREFIX})
else()
	set(TAPTEMPO_LOCALE_DIR "${CMAKE_INSTALL_PREFIX}/share/locale")
	set(TAPTEMPO_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/bin)
endif()

add_executable(${TAPTEMPO_PACKAGE_NAME} src/main.cpp src/taptempo.cpp src/taptempo.h)

configure_file (
	"${PROJECT_SOURCE_DIR}/src/taptempo_config.h.in"
	"${PROJECT_BINARY_DIR}/taptempo_config.h"
	)
include_directories("${PROJECT_BINARY_DIR}")

# Gettext and Intl.
find_package(Gettext REQUIRED)
find_package(Intl REQUIRED)
include_directories("${Intl_INCLUDE_DIRS}")
target_link_libraries(taptempo "${Intl_LIBRARIES}")

# Create a translation target to generate mo files from po files, then copy them in the localization folder.
set(MO_FILES)
file(GLOB PO_FILES po/*.po)
foreach(PO_FILE ${PO_FILES})
	get_filename_component(PO_LANG ${PO_FILE} NAME_WE)
	set(MO_FILE ${CMAKE_CURRENT_BINARY_DIR}/${PO_LANG}.mo)
	add_custom_command(OUTPUT ${MO_FILE} COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} -o ${MO_FILE} ${PO_FILE} DEPENDS ${PO_FILE})
	install(FILES ${MO_FILE} DESTINATION ${TAPTEMPO_LOCALE_DIR}/${PO_LANG}/LC_MESSAGES RENAME ${TAPTEMPO_PACKAGE_NAME}.mo)
	set(MO_FILES ${MO_FILES} ${MO_FILE})
endforeach()
set(TRANSLATIONS_TARGET_NAME "${TAPTEMPO_PACKAGE_NAME}-translations")
add_custom_target(${TRANSLATIONS_TARGET_NAME} ALL DEPENDS ${MO_FILES})

# Create install target.
install(TARGETS ${TAPTEMPO_PACKAGE_NAME} DESTINATION ${TAPTEMPO_INSTALL_DIR})


