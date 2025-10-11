cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(attractor VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Ofast")

# VTK packages
find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  CommonDataModel
  FiltersSources
  IOImage
  ImagingCore
  InteractionStyle
  InteractionWidgets
  RenderingAnnotation
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "Attractor: Unable to find the VTK build folder.")
endif()

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/inc
)

set(SOURCES
    src/main.cpp
    src/utils.cpp
    src/Attractor.cpp
    src/Points.cpp
    src/formulas.cpp
)

# Header files
set(HEADERS
    inc/Attractor.hpp
    inc/Points.hpp
    inc/main.hpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${VTK_LIBRARIES}
)

# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS ${PROJECT_NAME}
  MODULES ${VTK_LIBRARIES}
)
