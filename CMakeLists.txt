cmake_minimum_required(VERSION 2.8.3)
project(ar_tag_pad)

add_compile_options(-std=c++11)

find_package(catkin COMPONENTS
  genmsg
  roscpp
  rospy
  std_msgs
  image_transport
  message_generation
  sensor_msgs
  )

find_package(OpenCV REQUIRED)

generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
  )

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS
  std_msgs
  roscpp
  rospy
  message_runtime
  image_transport
  geometry_msgs
  )

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  )


add_executable(ar_tag_pad src/ar_tag_pad.cpp)

add_dependencies(ar_tag_pad ${PROJECT_NAME}_generate_messages_cpp)
target_link_libraries(ar_tag_pad ${catkin_LIBRARIES})
target_link_libraries(ar_tag_pad ${OpenCV_LIBS})


install(DIRECTORY include/${PROJECT_NAME}/
    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)


install(TARGETS ar_tag_pad
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

