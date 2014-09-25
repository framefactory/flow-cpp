# ------------------------------------------------------------------------------
# BUILD FLOW LIBRARY COMPONENTS

# Add base include path for all libraries
include_directories (${CMAKE_CURRENT_SOURCE_DIR})

# Add all libraries
ADD_SUBDIRECTORY(FlowCore)
ADD_SUBDIRECTORY(FlowGraphics)
#ADD_SUBDIRECTORY(FlowUI)
#ADD_SUBDIRECTORY(FlowEngine)
#ADD_SUBDIRECTORY(FlowQ)
#ADD_SUBDIRECTORY(FlowGL)
#ADD_SUBDIRECTORY(FlowKinect)
#ADD_SUBDIRECTORY(FlowRender)
