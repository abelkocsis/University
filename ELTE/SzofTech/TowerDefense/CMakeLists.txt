cmake_minimum_required(VERSION 2.6)
SET(CMAKE_CXX_FLAGS "-std=gnu++11")

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(FILES_TO_TEST "TowerDefense/GameModel.cpp"
                  "TowerDefense/Soldier.cpp"
                  "TowerDefense/Tower.cpp"
                  "TowerDefense/Player.cpp"
                  "TowerDefense/Structures.cpp"
		  "TowerDefense/mock_network.cpp")



# Link runTests with what we want to test and the GTest and pthread library
add_library(codeToTest ${FILES_TO_TEST})

add_executable(runTests test.cpp)
target_link_libraries(runTests codeToTest)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)