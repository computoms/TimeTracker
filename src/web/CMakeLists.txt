project(webserver)

list(APPEND SRCS_CLASSES
        webserver
        http
        clientsocket
        pagegenerator
        actioncontroller
        pageaddress)

set(SRC_DIR "src/web")

set(HDRS_FILES "")
set(SRCS_FILES "")
foreach(file IN LISTS SRCS_CLASSES)
    set(HDRS_FILES ${HDRS_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/${file}.h)
    set(SRCS_FILES ${SRCS_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/${file}.cpp)
endforeach(file)

add_executable(webserver_Test
        ${HDRS_FILES} ${SRCS_FILES} test.cpp)
target_link_libraries(webserver_Test TimeTracker_CLion)
target_include_directories(webserver_Test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)

add_executable(webclient_Test
        client.cpp)