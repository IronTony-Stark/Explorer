cmake_minimum_required(VERSION 3.14)

project(ExplorerServer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)
find_package(Qt5Network)

set(SERVER_SOURCES
        src/main.cpp
        src/file_info.cpp
        src/filesystem.cpp
        src/http_server.cpp
        include/http_server.h
        src/dir_info.cpp
        include/dir_info.h
        )

set(COMMON_DIR ../common)

set(COMMON_SOURCES
        ${COMMON_DIR}/src/http_message.cpp
        ${COMMON_DIR}/src/http_request.cpp
        ${COMMON_DIR}/src/http_request_parser.cpp
        ${COMMON_DIR}/src/http_response.cpp
        ${COMMON_DIR}/src/http_response_parser.cpp
        ${COMMON_DIR}/include/http_exception.h
        ${COMMON_DIR}/include/http_message.h
        ${COMMON_DIR}/include/http_request.h
        ${COMMON_DIR}/include/http_request_parser.h
        ${COMMON_DIR}/include/http_response.h
        ${COMMON_DIR}/include/http_response_parser.h
        )

add_executable(${PROJECT_NAME} ${SERVER_SOURCES} ${COMMON_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include ${COMMON_DIR}/include)

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Network
        )
