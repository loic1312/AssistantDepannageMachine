cmake_minimum_required (VERSION 3.0)
project (GestionAffichageCmd)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra)

IF(${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_definitions(-D_DEBUG)
ENDIF(${CMAKE_BUILD_TYPE} MATCHES Debug)

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include_directories(header)

set(SOURCES
	src/main.cpp
	src/InterfaceCmd.cpp
	src/DTODataPrint.cpp
	)
	
set(HEADERS
	header/InterfaceCmd.h
	header/DTODataPrint.h
	)
	
set(Libraries_FOUND True)

if(Libraries_FOUND)
	add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
	target_link_libraries(${PROJECT_NAME} pthread dl rt)
endif()
