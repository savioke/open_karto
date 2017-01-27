cmake_minimum_required(VERSION 2.8.3)
project(open_karto)

find_package(catkin REQUIRED)

find_package(Boost REQUIRED COMPONENTS thread system)

catkin_package(
  DEPENDS Boost
  INCLUDE_DIRS
    include
  LIBRARIES
    karto
)

include_directories(include ${catkin_INCLUDE_DIRS})
add_library(karto SHARED src/Karto.cpp src/Mapper.cpp)
target_link_libraries(karto ${Boost_LIBRARIES})

install(DIRECTORY include/ DESTINATION include)
install(TARGETS karto
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)


#############
## Testing ##
#############
if (CATKIN_ENABLE_TESTING)
  catkin_add_gtest(graph_operations_test test/graph_operations_test.cpp)
  target_link_libraries(graph_operations_test karto ${Boost_LIBRARIES} gtest_main)
  set_target_properties(graph_operations_test PROPERTIES COMPILE_FLAGS "-std=c++11")

endif()
