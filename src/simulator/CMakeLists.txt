# folder: icp-project/src/simulator
# author: Kevin Lackó (xlacko08)

set(SOURCES main.cpp)

add_executable(mqtt-simulator ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/src/)
	
target_link_libraries(mqtt-simulator mqtt-core ${REQUIRED_LIBS_QUALIFIED})
