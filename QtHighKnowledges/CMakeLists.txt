if(NOT DEFINED CMAKE_PREFIX_PATH AND NOT DEFINED Qt5_DIR)
    set(CMAKE_PREFIX_PATH "E:/Software/Qt/5.15.2/msvc2019_64" CACHE PATH "Qt5 prefix")
endif()

find_package(Qt5 5.15.2 EXACT REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Network
    Sql
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.qrc"
)

add_executable(QtHighKnowledges
    ${APP_SOURCES}
)

target_include_directories(QtHighKnowledges PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(QtHighKnowledges PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
    Qt5::Sql
)
