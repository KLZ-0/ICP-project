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
    )

include_directories(gui)

add_executable(${PROJECT_NAME} ${SOURCES})
add_executable(publish publish.cpp)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(publish ${REQUIRED_LIBS_QUALIFIED})

if (MSVC)
    install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/exe)
else ()
    install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR})
endif ()
