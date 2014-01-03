# ------------------------------------------------------------------------------
#  Project:      FlowEngine
#  Description:  Statically built library
#  Dependencies: FlowCore, FlowGraphics, FlowGL, Boost
# ------------------------------------------------------------------------------
#  Author:       ralphw
#  Date:         2012/11/26
# ------------------------------------------------------------------------------


INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

# ------------------------------------------------------------------------------
# SOURCE FILES

# Automatically create a list of source files
FILE(GLOB FlowEngineSources RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")


# Automatically create a list of header files
FILE(GLOB FlowEngineHeaders RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# ------------------------------------------------------------------------------
# BUILD TARGET

# Specify build target
ADD_LIBRARY (FlowEngine ${FlowEngineSources})

# Link necessary libraries
TARGET_LINK_LIBRARIES (FlowEngine FlowCore
                                  FlowGraphics
                                  FlowGL
                                  ${Boost_LIBRARIES})

# ------------------------------------------------------------------------------
# INSTALLATION

# Install the library
INSTALL (TARGETS FlowEngine DESTINATION ${CMAKE_SOURCE_DIR}/bin)

# Install the include headers
INSTALL (FILES ${FlowEngineHeaders} DESTINATION ${CMAKE_SOURCE_DIR}/include/FlowEngine)