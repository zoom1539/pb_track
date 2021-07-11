cmake_minimum_required(VERSION 3.0.0)

# OpenCV
find_package(OpenCV 3.4.8 REQUIRED PATHS ~/PLATFORM/3rdparty/opencv348)
# find_package(OpenCV REQUIRED)



#
aux_source_directory(. LIB_SRC)
message(${LIB_SRC})
add_library(tracker SHARED ${LIB_SRC} )

target_include_directories(tracker 
            PUBLIC ${OpenCV_INCLUDE_DIRS})

target_link_libraries(tracker ${OpenCV_LIBS})

# cd build 
# make install
install(FILES class_tracker.h DESTINATION include)
install(TARGETS tracker LIBRARY DESTINATION lib)