cmake_minimum_required(VERSION 3.14)

project(ExplorerCommon LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)

add_executable(${PROJECT_NAME}
        src/http_message.cpp
        src/http_request.cpp
        src/http_request_parser.cpp
        src/http_response.cpp
        src/http_response_parser.cpp
        include/http_message.h
        include/http_request.h
        include/http_request_parser.h
        include/http_response.h
        include/http_response_parser.h
        include/http_exception.h
        )

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} Qt5::Core)
