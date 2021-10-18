cmake_minimum_required (VERSION 3.0)
project (MachineExpertMaxiCoffee)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra)

IF(${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_definitions(-D_DEBUG)
ENDIF(${CMAKE_BUILD_TYPE} MATCHES Debug)

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "../libraries:/home/machine/MC_SOFT/libraries:$ORIGIN/")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

if ("${CMAKE_CXX_COMPILER}" MATCHES ".*arm-linux-gnueabihf-")
	include_directories(/opt/maxicoffee/crosstools/ARM/raspberry/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/libc/usr/include)
	set(BOOST_ROOT "../../DALT_LINUX_DEPENDENCIES/boost/boost_1_75_0_ARMV4")
else()
	set(BOOST_ROOT "../../DALT_LINUX_DEPENDENCIES/boost/boost_1_75_0_X64")
endif()

include_directories(${BOOST_ROOT}/include)

link_directories(${BOOST_ROOT}/lib)

include_directories(header)

set(SOURCES
	src/main.cpp
	src/InterfaceCmd.cpp
	src/DTODataPrint.cpp
	src/Fact.cpp
	src/BaseFact.cpp
	src/Rule.cpp
	src/BaseRule.cpp
	src/SteamInference.cpp
	src/RuleFactory.cpp
	src/DriverXml.cpp
	src/IHMCmd.cpp
	)
	
set(HEADERS
	header/InterfaceCmd.h
	header/DTODataPrint.h
	header/Fact.h
	header/BaseFact.h
	header/Rule.h
	header/BaseRule.h
	header/SteamInference.h
	header/RuleFactory.h
	header/DriverXml.h
	header/IHMCmd.h
	)
	
set(Libraries_FOUND True)

set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_DEBUG_LIBS         OFF)
set(Boost_USE_RELEASE_LIBS       ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)

find_package(Boost 1.75.0 COMPONENTS atomic thread regex system filesystem chrono date_time log log_setup locale)
if(NOT Boost_FOUND)
	set(Libraries_FOUND False)
else()
	if(${Boost_USE_STATIC_LIBS} MATCHES OFF)
		add_definitions(-DBOOST_ALL_DYN_LINK)
	endif()
endif()

if(Libraries_FOUND)
	add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

	target_link_libraries(${PROJECT_NAME} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_SYSTEM_LIBRARY})
	target_link_libraries(${PROJECT_NAME} ${Boost_FILESYSTEM_LIBRARY} ${Boost_CHRONO_LIBRARY} ${Boost_DATE_TIME_LIBRARY})
	target_link_libraries(${PROJECT_NAME} ${Boost_LOG_LIBRARY} ${Boost_LOG_SETUP_LIBRARY} ${Boost_LOCALE_LIBRARY})
	target_link_libraries(${PROJECT_NAME} ${Boost_ATOMIC_LIBRARY})

	target_link_libraries(${PROJECT_NAME} pthread dl rt)
endif()
