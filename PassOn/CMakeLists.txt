cmake_minimum_required(VERSION 3.5)
project(PassOn)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(custom_msgs REQUIRED)

# Add include directories
include_directories(include)

# Create executable
add_executable(PassOn src/PassOn.cpp)

# Link the executable with the required libraries
ament_target_dependencies(PassOn rclcpp std_msgs custom_msgs)

# Install executables
install(TARGETS
  PassOn
  DESTINATION lib/${PROJECT_NAME}
)

# Install launch files
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

# Install package.xml
install(FILES package.xml
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
