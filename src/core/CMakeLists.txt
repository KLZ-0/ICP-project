# folder: icp-project/src/core
# author: Kevin Lackó (xlacko08)

set(SOURCES 
	client.cpp
	client.hpp
	)

add_library(mqtt-core STATIC ${SOURCES})
target_link_libraries(mqtt-core ${REQUIRED_LIBS_QUALIFIED})
