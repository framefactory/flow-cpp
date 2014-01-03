# ------------------------------------------------------------------------------
#  Project:      FlowTest
#  Description:  Test Application
#  Dependencies: Qt, Boost
# ------------------------------------------------------------------------------
#  Author:       ralphw
#  Date:         2012/11/26
# ------------------------------------------------------------------------------


INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

# ------------------------------------------------------------------------------
# QT 4

find_package (Qt4 4.8.2 REQUIRED QtCore QtGui)
include (${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

# Qt MOC headers
SET (FlowTestMocHeaders MainWindow.h)

qt4_wrap_cpp (FlowTestMocFiles ${FlowTestMocHeaders})

# ------------------------------------------------------------------------------
# SOURCE FILES

# Automatically create a list of source files
FILE(GLOB FlowTestSources RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")


# Automatically create a list of header files
FILE(GLOB FlowTestHeaders RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# ------------------------------------------------------------------------------
# BUILD TARGET

# Specify build target
ADD_EXECUTABLE (FlowTest ${FlowTestSources} ${FlowTestMocFiles})

# Link necessary libraries
TARGET_LINK_LIBRARIES (FlowTest ${Boost_LIBRARIES}
                                ${QT_LIBRARIES}
                                FlowCore
                                FlowUI
                                FlowQ)

# ------------------------------------------------------------------------------
# INSTALLATION

# Install the application
INSTALL (TARGETS FlowTest DESTINATION ${CMAKE_SOURCE_DIR}/bin)

