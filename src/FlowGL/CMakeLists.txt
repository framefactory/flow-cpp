# ------------------------------------------------------------------------------
#  Project:      FlowGL
#  Description:  Statically built library
#  Dependencies: FlowCore, Boost
# ------------------------------------------------------------------------------
#  Author:       ralphw
#  Date:         2012/11/26
# ------------------------------------------------------------------------------


INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

# ------------------------------------------------------------------------------
# SOURCE FILES

# Automatically create a list of source files
FILE(GLOB FlowGLSources RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")


# Automatically create a list of header files
FILE(GLOB FlowGLHeaders RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# ------------------------------------------------------------------------------
# BUILD TARGET

# Specify build target
ADD_LIBRARY (FlowGL ${FlowGLSources})

# Link necessary libraries
TARGET_LINK_LIBRARIES (FlowGL FlowCore
                              FlowGraphics
                              ${Boost_LIBRARIES})

# ------------------------------------------------------------------------------
# INSTALLATION

# Install the library
INSTALL (TARGETS FlowGL DESTINATION ${CMAKE_SOURCE_DIR}/bin)

# Install the include headers
INSTALL (FILES ${FlowGLHeaders} DESTINATION ${CMAKE_SOURCE_DIR}/include/FlowGL)