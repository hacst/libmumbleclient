cmake_minimum_required (VERSION 2.6)
project (libmumbleclient)
set (libmumbleclient_VERSION_MAJOR 0)
set (libmumbleclient_VERSION_MINOR 0)

include(FindPkgConfig)

if (WIN32)
	set(Boost_USE_STATIC_LIBS ON)
endif()
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.38.0 REQUIRED COMPONENTS system thread date_time regex)
find_package(OpenSSL REQUIRED)
find_package(Protobuf REQUIRED)

pkg_check_modules(CELT celt>=0.7.0)

if (NOT CELT_FOUND)
	add_subdirectory(celt-build)
	set(CELT_LIBRARIES celt0)
	set(CELT_INCLUDE_DIR celt/libcelt)
endif()

SET(CMAKE_BUILD_TYPE Debug)
if (NOT WIN32)
	SET(COMMON_CFLAGS "-g -Wall -Wextra -Wfatal-errors -Wshadow -fvisibility=hidden -fvisibility-inlines-hidden")
	SET(CMAKE_C_FLAGS_DEBUG  "${COMMON_CFLAGS} -pedantic")
	SET(CMAKE_CXX_FLAGS_DEBUG "${COMMON_CFLAGS} -Woverloaded-virtual -Wold-style-cast")
endif()

if (WIN32)
	add_definitions(-D_WIN32_WINNT=0x0501 -DBUILDING_STATIC)
endif()

include_directories(. ${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR} ${CELT_INCLUDE_DIR} ${PROTOBUF_INCLUDE_DIR})

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS Mumble.proto)

add_library(mumbleclient client.cc client_lib.cc CryptState.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(mumbleclient ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${PROTOBUF_LIBRARY})

option(WITH_MPG123 "Add mp3 playback support" ON)

if (WITH_MPG123)
	add_definitions(-DWITH_MPG123)
	set(LIBRARIES mpg123)
endif()

add_executable (main main.cc)
target_link_libraries (main mumbleclient ${LIBRARIES} ${CELT_LIBRARIES} ${Boost_LIBRARIES})
