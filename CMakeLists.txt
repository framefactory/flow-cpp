# ------------------------------------------------------------------------------
#  Project:      Flow
#  Description:  Library
# ------------------------------------------------------------------------------
#  Author:       ralphw
#  Date:         2012/11/26
# ------------------------------------------------------------------------------

CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (Flow)

SET (Flow_VERSION_MAJOR 1)
SET (Flowcd_VERSION_MINOR 0)

MESSAGE("Current Source Directory: ${CMAKE_CURRENT_SOURCE_DIR}")
MESSAGE("Current Binary Directory: ${CMAKE_CURRENT_BINARY_DIR}")

# ------------------------------------------------------------------------------
# Global Settings

SET(CMAKE_BUILD_TYPE Debug)

if(CMAKE_COMPILER_IS_GNUCXX)

	#Compiler flags
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -Wall")
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Wall")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -msse4")

    #Linker flags
    #SET(CMAKE_EXE_LINKER_FLAGS "-s")

endif()

# ------------------------------------------------------------------------------
# 3RD PARTY LIBRARIES

# Boost
SET (Boost_USE_STATIC_LIBS ON)
SET (Boost_USE_MULTITHREADED ON) 
SET (Boost_USE_STATIC_RUNTIME OFF)
SET (Boost_ADDITIONAL_VERSIONS "1.52" "1.52.0")
SET (BOOST_ROOT "/usr/local/Boost/1.52.0")

FIND_PACKAGE (Boost 1.52.0 COMPONENTS locale signals thread system filesystem serialization wserialization REQUIRED)

if(NOT Boost_FOUND)
	MESSAGE(FATAL_ERROR "Could not find boost library")
	RETURN()
endif()

MESSAGE(STATUS "Boost library found: ${Boost_INCLUDE_DIRS}")

# OpenGL


# ------------------------------------------------------------------------------
# Add Project Components

ADD_SUBDIRECTORY (src)
ADD_SUBDIRECTORY (test)
