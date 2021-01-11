cmake_minimum_required(VERSION 3.14)

project(ExplorerClient LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Network REQUIRED)

set(SERVER_SOURCES
        qml.qrc
        src/main.cpp
        src/tcp_client.cpp
        include/tcp_client.h
        src/file_list/file.cpp
        include/file_list/file.h
        src/file_list/file_list_model.cpp
        include/file_list/file_list_model.h
        src/file_list/file_list_model_proxy.cpp
        include/file_list/file_list_model_proxy.h
        src/file_tree/file_tree_node.cpp
        include/file_tree/file_tree_node.h
        src/file_tree/file_tree_model.cpp
        include/file_tree/file_tree_model.h
        src/error_text.cpp
        include/error_text.h
        src/file_list/file_list.cpp
        include/file_tree/dir.h
        src/file_tree/dir.cpp
        include/file_list/file_list.h
        include/busy_indicator.h
        )

set(COMMON_DIR "../common")

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
        Qt5::Quick
        Qt5::Network
        )
