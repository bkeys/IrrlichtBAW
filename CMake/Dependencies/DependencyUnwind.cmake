ExternalProject_Add(unwind
  DOWNLOAD_NO_PROGRESS 1
  URL https://github.com/llvm-mirror/libunwind/archive/master.zip
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/unwind
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/unwind -DLIBUNWIND_ENABLE_SHARED=OFF -DLLVM_CONFIG=${CMAKE_BINARY_DIR}/unwind/src/unwind/
)

set(UNWIND_INCLUDE_DIR "${CMAKE_BINARY_DIR}/")
set(UNWIND_LIBRARY "${CMAKE_BINARY_DIR}/")

include_directories(SYSTEM ${UNWIND_INCLUDE_DIR})

set(IRRBAW_DEPENDENCY_LIBRARIES
    ${IRRBAW_DEPENDENCY_LIBRARIES}
    ${UNWIND_LIBRARY}
    )