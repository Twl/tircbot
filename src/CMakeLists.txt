set (tircbot_SOURCES "main.cpp")

add_executable(tircbot ${tircbot_SOURCES})
target_link_libraries(tircbot ${tirclib_REQUIRED_LIBRARIES} tirc)

install(TARGETS tircbot DESTINATION bin)

