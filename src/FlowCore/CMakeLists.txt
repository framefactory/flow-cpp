# ------------------------------------------------------------------------------
#  Project:      FlowCore
#  Description:  Statically built library
#  Dependencies: Boost
# ------------------------------------------------------------------------------
#  Author:       ralphw
#  Date:         2012/11/26
# ------------------------------------------------------------------------------


INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

# ------------------------------------------------------------------------------
# SOURCE FILES

# Automatically create a list of source files
FILE(GLOB FlowCoreSources RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")


# Automatically create a list of header files
FILE(GLOB FlowCoreHeaders RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# ------------------------------------------------------------------------------
# BUILD TARGET

# Specify build target
ADD_LIBRARY (FlowCore ${FlowCoreSources})

# Link necessary libraries
TARGET_LINK_LIBRARIES (FlowCore ${Boost_LIBRARIES})

# ------------------------------------------------------------------------------
# INSTALLATION

# Install the library
INSTALL (TARGETS FlowCore DESTINATION ${CMAKE_SOURCE_DIR}/bin)

# Install the include headers
INSTALL (FILES ${FlowCoreHeaders} DESTINATION ${CMAKE_SOURCE_DIR}/include/FlowCore)