cmake_minimum_required(VERSION 3.5)
project(arpis_server)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tachimawari REQUIRED)
find_package(arpis_network REQUIRED)
find_package(geometry_msgs REQUIRED)

add_library(${PROJECT_NAME} SHARED
  "src/${PROJECT_NAME}/node/server_node.cpp"
  "src/${PROJECT_NAME}/joint/joint.cpp"  
  "src/${PROJECT_NAME}/joint/tachimawari/connector.cpp"
  "src/${PROJECT_NAME}/joint/tachimawari/reader.cpp"  
  "src/${PROJECT_NAME}/joint/dummy/connector.cpp"  
  "src/${PROJECT_NAME}/joint/dummy/reader.cpp"  
  "src/${PROJECT_NAME}/utils/arg_parser.cpp" 
)

install(DIRECTORY "include" DESTINATION ".")

ament_target_dependencies(${PROJECT_NAME}
  "arpis_network"
  "rclcpp"
  "tachimawari"
  "geometry_msgs"  
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

  
add_executable(arpis_main src/arpis_main.cpp)
target_include_directories(arpis_main PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_link_libraries(arpis_main ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}  
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib"
  RUNTIME DESTINATION "bin")
  
install(TARGETS
  arpis_main
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
