# folder: icp-project/src
# author: Kevin Lackó (xlacko08)
# author: Adrián Kálazi (xkalaz00)

set(SOURCES
    main.cpp
    test_button.cpp
    test_button.h
    gui/main_window.cpp
    gui/main_window.hpp
    gui/explorer.cpp
    gui/explorer.hpp
    gui/dashboard.cpp
    gui/dashboard.hpp
    gui/dashboard_item.cpp
    gui/dashboard_item.hpp
    gui/topic_selection_window.cpp
    gui/topic_selection_window.hpp
    gui/explorer_item.cpp
    gui/explorer_item.hpp
    data/data_model.cpp
    data/data_model.hpp
    data/topic.cpp
    data/topic.hpp
    )

include_directories(gui)
include_directories(data)

add_subdirectory(core)
add_subdirectory(explorer)
add_subdirectory(simulator)

add_executable(${PROJECT_NAME} ${SOURCES})
add_executable(publish publish.cpp)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(publish ${REQUIRED_LIBS_QUALIFIED})

if (MSVC)
    install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/exe)
else ()
    install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR})
endif ()
