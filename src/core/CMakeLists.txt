set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

list(APPEND SRCS_CLASSES
        timetracker
        timeplanner
        workday
        journalentry
        generalworkperiod
        duration
        datetime
        workdaycollectionreader
        workdaycollectionwriter)

set(SRC_DIR "src/core")

set(HDRS_FILES "")
set(SRCS_FILES "")
foreach(file IN LISTS SRCS_CLASSES)
    set(HDRS_FILES ${HDRS_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/${file}.h)
    set(SRCS_FILES ${SRCS_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/${file}.cpp)
endforeach(file)


set(PUGI_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/pugixml-1.9/src)
set(EXT_SRC_LIBS ${PUGI_LIB_DIR}/pugixml.hpp ${PUGI_LIB_DIR}/pugixml.cpp)

add_library(TimeTracker_CLion SHARED
        ${HDRS_FILES} ${SRCS_FILES} ${EXT_SRC_LIBS})
target_include_directories(TimeTracker_CLion PUBLIC ${PUGI_LIB_DIR})


## Tests

set(TEST_FILES tests.cpp)
add_executable(Test_TimeTracker-Core
        ${HDRS_FILES} ${SRCS_FILES} ${EXT_SRC_LIBS} ${TEST_FILES})
target_include_directories(Test_TimeTracker-Core PUBLIC ${PUGI_LIB_DIR})