include_directories(gui)
include_directories(data)

set(SOURCES
    main.cpp
    main_window.cpp
    main_window.hpp
    explorer.cpp
    explorer.hpp
    dashboard.cpp
    dashboard.hpp
    dashboard_item.cpp
    dashboard_item.hpp
    topic_selection_window.cpp
    topic_selection_window.hpp
    explorer_item.cpp
    explorer_item.hpp
    data/data_model.cpp
    data/data_model.hpp
    data/topic.cpp
    data/topic.hpp
    publish_window.cpp
    publish_window.hpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})
#add_executable(publish publish.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src/core)
include_directories(.)
include_directories(data)

#target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
#target_link_libraries(publish ${REQUIRED_LIBS_QUALIFIED})

target_link_libraries(${PROJECT_NAME} mqtt-core ${REQUIRED_LIBS_QUALIFIED})

if (WIN32)
    get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                       COMMAND "${CMAKE_COMMAND}" -E
                       env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
                       "$<TARGET_FILE:${PROJECT_NAME}>"
                       COMMENT "Running windeployqt..."
                       )
else ()
    install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR})
endif ()
