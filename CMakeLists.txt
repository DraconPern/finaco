cmake_minimum_required(VERSION 2.8)

project(finaco)

set(VERSION 1.0.0)

add_definitions(-DFINACO_VERSION="${VERSION}")

set (CMAKE_CXX_STANDARD 11)

if(WIN32)
	#VC++ stuff
	add_definitions(-DWIN32_LEAN_AND_MEAN)
	add_definitions(-D_UNICODE)	
	add_definitions(-D_BIND_TO_CURRENT_VCLIBS_VERSION=1)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd -DDEBUG")
endif()

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     ON)
find_package(Boost REQUIRED thread filesystem system regex date_time)

set(wxWidgets_USE_STATIC   ON)
#define this so that wxWidgets doesn't define it. Conflicts w/ dcmtk's declaration
add_definitions(-DHAVE_SSIZE_T)
find_package(wxWidgets COMPONENTS core base adv REQUIRED)
include(${wxWidgets_USE_FILE})

if(WIN32)
	#enable dcmtk filename to have wide version, only affects WIN32.  http://utf8everywhere.org/
	add_definitions(-DDCMTK_WIDE_CHAR_FILE_IO_FUNCTIONS=1)
endif(WIN32)
find_package(DCMTK REQUIRED CONFIG HINTS ${DCMTK_DIR})

#include zlib
find_package(ZLIB REQUIRED ${ZLIB_ROOT})

#include openjpeg
find_package(OpenJPEG REQUIRED HINTS ${OPENJPEG})
add_definitions(-DOPJ_STATIC)

#include fmjpeg2koj
find_package(fmjpeg2k REQUIRED HINTS ${FMJPEG2K})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/sqlite3 ${Boost_INCLUDE_DIRS} ${FMJPEG2K_INCLUDE_DIRS} ${DCMTK_INCLUDE_DIRS} ${VLD}/include)
LINK_DIRECTORIES(${FMJPEG2K}/lib ${Boost_LIBRARY_DIRS}  ${VLD}/lib/Win32)

set(finaco_HEADERS
	src/gui.h
	src/finaco_about.h
	src/finaco_destination.h
	src/finaco_mainFrame.h
	src/finaco_searchStatus.h
	src/finaco_moveStatus.h
	src/finaco_updateCheck.h
	sqlite3/sqlite3.h
	src/engine.h
	src/patientdata.h
	src/destinationentry.h
	src/dicomquery.h
	src/dicommover.h
	src/dcm2img.h
	src/update.h
	src/alphanum.hpp	
)

set(finaco_SRCS
  ${finaco_HEADERS}
	src/main.cpp
	src/gui.cpp
	src/finaco_about.cpp
	src/finaco_destination.cpp
	src/finaco_mainFrame.cpp
	src/finaco_searchStatus.cpp
	src/finaco_moveStatus.cpp
	src/finaco_updateCheck.cpp
	sqlite3/sqlite3.c
	sqlite3/sqlite3_exec_stmt.c
	src/engine.cpp
	src/patientdata.cpp
	src/dicomquery.cpp
	src/dicommover.cpp
	src/dcm2img.cpp
	src/update.cpp	
)

if(WIN32)
  set(finaco_SRCS ${finaco_SRCS} src/win/finaco.rc src/win/version.rc)

  string(REPLACE "." "," VER_FILEVERSION ${VERSION})

  add_definitions(-DVER_FILEVERSION=${VER_FILEVERSION})
  add_definitions(-DVER_FILEVERSION_STR="${VERSION}")
  add_definitions(-DVER_PRODUCTVERSION=${VER_FILEVERSION})
  add_definitions(-DVER_PRODUCTVERSION_STR="${VERSION}")

endif()

if(APPLE)
  set(finaco_SRCS ${finaco_SRCS} src/osx/finaco.icns src/osx/Info.plist.in)
endif()

ADD_EXECUTABLE(finaco WIN32 MACOSX_BUNDLE ${finaco_SRCS})

IF(WIN32)
  SET(OS_SPECIFIC_LIBS netapi32 wsock32 odbc32 Rpcrt4)
ELSE()
  IF(APPLE)
  ELSE()
    SET(OS_SPECIFIC_LIBS dl)
  ENDIF()
ENDIF()

if(APPLE)
  set_target_properties(finaco PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/src/osx/Info.plist.in)
  set_target_properties(finaco PROPERTIES MACOSX_BUNDLE_SHORT_VERSION_STRING ${VERSION})
	SET_SOURCE_FILES_PROPERTIES(${CMAKE_SOURCE_DIR}/src/osx/finaco.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
ENDIF()

TARGET_LINK_LIBRARIES(finaco
	${FMJPEG2K_LIBRARIES}
	${OPENJPEG_LIBRARIES}
	${ZLIB_LIBRARIES}
	${DCMTK_LIBRARIES}
	${wxWidgets_LIBRARIES}
	${Boost_LIBRARIES}
	${OS_SPECIFIC_LIBS}
	)
