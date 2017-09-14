ExternalProject_Add(bzip2
  DOWNLOAD_NO_PROGRESS 1
  URL https://github.com/bkeys/bzip2/archive/master.zip
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/bzip2
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/bzip2
)

set(BZIP2_INCLUDE_DIR "${CMAKE_BINARY_DIR}/bzip2")
set(BZIP2_LIBRARY "${CMAKE_BINARY_DIR}/bzip2/lib/libbz2.a")

include_directories(SYSTEM ${BZIP2_INCLUDE_DIR})

set(IRRBAW_DEPENDENCY_LIBRARIES
    ${IRRBAW_DEPENDENCY_LIBRARIES}
    ${BZIP2_LIBRARY}
    )