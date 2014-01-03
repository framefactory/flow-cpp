# ------------------------------------------------------------------------------
#  Project:      FlowUI
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
FILE(GLOB FlowUISources RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")


# Automatically create a list of header files
FILE(GLOB FlowUIHeaders RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# ------------------------------------------------------------------------------
# BUILD TARGET

# Specify build target
ADD_LIBRARY (FlowUI ${FlowUISources})

# Link necessary libraries
TARGET_LINK_LIBRARIES (FlowUI FlowCore
                              ${Boost_LIBRARIES})

# ------------------------------------------------------------------------------
# INSTALLATION

# Install the library
INSTALL (TARGETS FlowUI DESTINATION ${CMAKE_SOURCE_DIR}/bin)

# Install the include headers
INSTALL (FILES ${FlowUIHeaders} DESTINATION ${CMAKE_SOURCE_DIR}/include/FlowUI)