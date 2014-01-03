# ------------------------------------------------------------------------------
#  Project:      FlowQ
#  Description:  Statically built library
#  Dependencies: FlowCore, FlowUI, Qt, Boost
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
SET (FlowQMocHeaders MainWindowBase.h
                     LogWidget.h)

QT4_WRAP_CPP (FlowQMocFiles ${FlowQMocHeaders})

# Qt Resources
SET (FlowQResources resources/Resources.qrc)

QT4_ADD_RESOURCES(FlowQResourceFiles ${FlowQResources})

# ------------------------------------------------------------------------------
# SOURCE FILES

# Automatically create a list of source files
FILE(GLOB FlowQSources RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")


# Automatically create a list of header files
FILE(GLOB FlowQHeaders RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# ------------------------------------------------------------------------------
# BUILD TARGET

# Specify build target
ADD_LIBRARY (FlowQ ${FlowQSources} ${FlowQMocFiles} ${FlowQResourceFiles})

# Link necessary libraries
TARGET_LINK_LIBRARIES (FlowQ FlowCore
                             FlowUI
                             ${Boost_LIBRARIES}
                             ${QT_LIBRARIES})

# ------------------------------------------------------------------------------
# INSTALLATION

# Install the library
INSTALL (TARGETS FlowQ DESTINATION ${CMAKE_SOURCE_DIR}/bin)

# Install the include headers
INSTALL (FILES ${FlowQHeaders} DESTINATION ${CMAKE_SOURCE_DIR}/include/FlowQ)