cmake_minimum_required(VERSION 3.10)
project(ClassType LANGUAGES OBJC)
find_library(FOUNDATION_FRAMEWORK Foundation)
add_executable(class_type 
    class_type.m 
    Person.m
)
target_link_libraries(class_type PRIVATE ${FOUNDATION_FRAMEWORK})

