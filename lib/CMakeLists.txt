cmake_minimum_required(VERSION 3.0.0)

# OpenCV
find_package(OpenCV 3.4.8 REQUIRED PATHS /root/PLATFORM/3rdparty/opencv348)
# find_package(OpenCV REQUIRED)

# boost
set(BOOST_INCLUDE_DIR /root/PLATFORM/3rdparty/boost_1_76_0/include)

# eigen
set(EIGEN_INCLUDE_DIR /usr/include/eigen3)


#
# aux_source_directory(. LIB_SRC)
# message(${LIB_SRC})
FILE (GLOB_RECURSE  LIB_SRC "*.cpp" "*.c")
message(${LIB_SRC})

add_library(tracker SHARED ${LIB_SRC} )

target_include_directories(tracker 
            PUBLIC ${OpenCV_INCLUDE_DIRS}
            PUBLIC ${BOOST_INCLUDE_DIR}
            PUBLIC ${EIGEN_INCLUDE_DIR}
            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sort
            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/deep_sort
            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(tracker ${OpenCV_LIBS})

# cd build 
# make install
install(FILES class_tracker.h DESTINATION include)
install(TARGETS tracker LIBRARY DESTINATION lib)
