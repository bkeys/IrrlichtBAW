file(COPY ${CMAKE_SOURCE_DIR}/examples_tests DESTINATION ${CMAKE_BINARY_DIR})

add_executable(01.HelloWorld ${CMAKE_BINARY_DIR}/examples_tests/01.HelloWorld/main.cpp)
target_link_libraries(01.HelloWorld IrrlichtBAW)
set_target_properties(01.HelloWorld PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples_tests/01.HelloWorld")

add_executable(03.GPU_Mesh ${CMAKE_BINARY_DIR}/examples_tests/03.GPU_Mesh/main.cpp)
target_link_libraries(03.GPU_Mesh IrrlichtBAW)
set_target_properties(03.GPU_Mesh PROPERTIES COMPILE_FLAGS "-std=c++14")
set_target_properties(03.GPU_Mesh PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples_tests/03.GPU_Mesh")

#add_executable(03.GPU_Mesh ${CMAKE_SOURCE_DIR}/examples_tests/03.GPU_Mesh/main.cpp)
#target_link_libraries(03.GPU_Mesh IrrlichtBAW)