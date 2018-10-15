INCLUDE_DIRECTORIES(${PROJECT_SRC_DIR}/header)
INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR}/header)

set(CMAKE_CXX_STANARD 11)

# compiler
set(CMAKE_C_COMPILER "g++")

add_compile_options(-std=c++11)
# -lboost_system -lcrypto -lssl -lcpprest

add_executable(../TOMSA main.cpp Line.cpp Position.cpp ConcavetToConvex.cpp PointInPolygonAlgorithm.cpp TimeOptimizationAlgorithm.cpp ODsay.cpp)
target_link_libraries(../TOMSA -lboost_system)
target_link_libraries(../TOMSA -lcrypto)
target_link_libraries(../TOMSA -lssl)
target_link_libraries(../TOMSA -lcpprest)