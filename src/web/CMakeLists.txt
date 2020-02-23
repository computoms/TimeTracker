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

add_executable(${PROJECT_NAME}
        ${HDRS_FILES} ${SRCS_FILES} serve.cpp)
target_link_libraries(${PROJECT_NAME} TimeTracker_Core)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)

add_executable(Test_webclient
        client.cpp)