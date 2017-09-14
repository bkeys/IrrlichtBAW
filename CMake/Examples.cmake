file(COPY ${CMAKE_SOURCE_DIR}/examples_tests DESTINATION ${CMAKE_BINARY_DIR})

add_executable(01.HelloWorld ${CMAKE_SOURCE_DIR}/examples_tests/01.HelloWorld/main.cpp)
target_link_libraries(01.HelloWorld IrrlichtBAW)
set_target_properties(01.HelloWorld PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples_tests/01.HelloWorld")

add_executable(03.GPU_Mesh ${CMAKE_SOURCE_DIR}/examples_tests/03.GPU_Mesh/main.cpp)
target_link_libraries(03.GPU_Mesh IrrlichtBAW)
set_target_properties(03.GPU_Mesh PROPERTIES COMPILE_FLAGS "-std=c++14")
set_target_properties(03.GPU_Mesh PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples_tests/03.GPU_Mesh")

add_executable(04.BuiltinNodes ${CMAKE_SOURCE_DIR}/examples_tests/04.BuiltinNodes/main.cpp)
target_link_libraries(04.BuiltinNodes IrrlichtBAW)
set_target_properties(04.BuiltinNodes PROPERTIES COMPILE_FLAGS "-std=c++14")
set_target_properties(04.BuiltinNodes PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples_tests/04.BuiltinNodes")

add_executable(05.SpherePoints ${CMAKE_SOURCE_DIR}/examples_tests/05.SpherePoints/main.cpp)
target_link_libraries(05.SpherePoints IrrlichtBAW)
set_target_properties(05.SpherePoints PROPERTIES COMPILE_FLAGS "-std=c++14")
set_target_properties(05.SpherePoints PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples_tests/05.SpherePoints")

add_executable(06.MeshLoaders ${CMAKE_SOURCE_DIR}/examples_tests/06.MeshLoaders/main.cpp)
target_link_libraries(06.MeshLoaders IrrlichtBAW)
set_target_properties(06.MeshLoaders PROPERTIES COMPILE_FLAGS "-std=c++14")
set_target_properties(06.MeshLoaders PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples_tests/06.MeshLoaders")

add_executable(07.HardwareSkinning ${CMAKE_SOURCE_DIR}/examples_tests/07.HardwareSkinning/main.cpp)
target_link_libraries(07.HardwareSkinning IrrlichtBAW)
set_target_properties(07.HardwareSkinning PROPERTIES COMPILE_FLAGS "-std=c++14")
set_target_properties(07.HardwareSkinning PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples_tests/07.HardwareSkinning")

add_executable(08.HardwareInstancing ${CMAKE_SOURCE_DIR}/examples_tests/08.HardwareInstancing/main.cpp)
target_link_libraries(08.HardwareInstancing IrrlichtBAW)
set_target_properties(08.HardwareInstancing PROPERTIES COMPILE_FLAGS "-std=c++14")
set_target_properties(08.HardwareInstancing PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples_tests/08.HardwareInstancing")

add_executable(09.PerfTest ${CMAKE_SOURCE_DIR}/examples_tests/09.PerfTest/main.cpp)
target_link_libraries(09.PerfTest IrrlichtBAW)
set_target_properties(09.PerfTest PROPERTIES COMPILE_FLAGS "-std=c++14")
set_target_properties(09.PerfTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples_tests/09.PerfTest")

add_executable(10.AllocPerfTest ${CMAKE_SOURCE_DIR}/examples_tests/10.AllocPerfTest/main.cpp)
target_link_libraries(10.AllocPerfTest IrrlichtBAW)
set_target_properties(10.AllocPerfTest PROPERTIES COMPILE_FLAGS "-std=c++14")
set_target_properties(10.AllocPerfTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples_tests/10.AllocPerfTest")

add_executable(11.RayCastCollision ${CMAKE_SOURCE_DIR}/examples_tests/11.RayCastCollision/main.cpp)
target_link_libraries(11.RayCastCollision IrrlichtBAW)
set_target_properties(11.RayCastCollision PROPERTIES COMPILE_FLAGS "-std=c++14")
set_target_properties(11.RayCastCollision PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples_tests/11.RayCastCollision")

add_executable(12.Splines ${CMAKE_SOURCE_DIR}/examples_tests/12.Splines/main.cpp)
target_link_libraries(12.Splines IrrlichtBAW)
set_target_properties(12.Splines PROPERTIES COMPILE_FLAGS "-std=c++14")
set_target_properties(12.Splines PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples_tests/12.Splines")



#add_executable(03.GPU_Mesh ${CMAKE_SOURCE_DIR}/examples_tests/03.GPU_Mesh/main.cpp)
#target_link_libraries(03.GPU_Mesh IrrlichtBAW)