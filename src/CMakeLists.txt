# author: Adrián Kálazi (xkalaz00)

set(SOURCES main.cpp test_button.cpp test_button.h)

add_executable(${PROJECT_NAME} ${SOURCES})
add_executable(publish publish.cpp)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(publish ${REQUIRED_LIBS_QUALIFIED})

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
