ExternalProject_Add(zlib
  DOWNLOAD_NO_PROGRESS 1
  URL http://zlib.net/zlib-1.2.11.tar.gz
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/zlib/
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/zlib
)

set(ZLIB_INCLUDE_DIR "${CMAKE_BINARY_DIR}/zlib/include/")
set(ZLIB_LIBRARY "${CMAKE_BINARY_DIR}/zlib/lib/libz.a")

include_directories(SYSTEM ${_INCLUDE_DIR})

set(DMUX_DEPENDENCY_LIBRARIES
    ${DMUX_DEPENDENCY_LIBRARIES}
    ${ZLIB_LIBRARY}
    )