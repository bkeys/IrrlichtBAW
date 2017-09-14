ExternalProject_Add(libpng
  DOWNLOAD_NO_PROGRESS 1
  URL http://prdownloads.sourceforge.net/libpng/libpng-1.6.32.tar.xz?download
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/libpng
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/libpng
)

set(LIBPNG_INCLUDE_DIR "${CMAKE_BINARY_DIR}/libpng/include/")
set(LIBPNG_LIBRARY "${CMAKE_BINARY_DIR}/libpng/src/libpng-build/libpng.a")

include_directories(SYSTEM ${LIBPNG_INCLUDE_DIR})

set(DMUX_DEPENDENCY_LIBRARIES
    ${DMUX_DEPENDENCY_LIBRARIES}
    ${LIBPNG_LIBRARY}
    )