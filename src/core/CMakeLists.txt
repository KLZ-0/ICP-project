# folder: icp-project/src/core
# author: Kevin Lackó (xlacko08)

set(SOURCES
	client.cpp
	client.hpp
	callback.cpp
	callback.hpp
	action_listener.cpp
	action_listener.hpp
	)

add_library(mqtt-core STATIC ${SOURCES})
target_link_libraries(mqtt-core ${REQUIRED_LIBS_QUALIFIED})
