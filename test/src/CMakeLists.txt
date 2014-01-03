# ------------------------------------------------------------------------------
# BUILD FLOW TEST COMPONENTS

# Add base include path for all libraries
include_directories (${CMAKE_CURRENT_SOURCE_DIR})
include_directories (${CMAKE_SOURCE_DIR}/src)

# Add all test applications
ADD_SUBDIRECTORY(FlowTest)