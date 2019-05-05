project(webserver)

list(APPEND SRCS_CLASSES
        webserver
        http
        clientsocket)

set(SRC_DIR "src/web")

set(HDRS_FILES "")
set(SRCS_FILES "")
foreach(file IN LISTS SRCS_CLASSES)
    set(HDRS_FILES ${HDRS_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/${file}.h)
    set(SRCS_FILES ${SRCS_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/${file}.cpp)
endforeach(file)

add_executable(webserver_Test
        ${HDRS_FILES} ${SRCS_FILES} test.cpp)

add_executable(webclient_Test
        client.cpp)