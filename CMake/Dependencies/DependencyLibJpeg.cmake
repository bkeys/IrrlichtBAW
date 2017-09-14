ExternalProject_Add(libjpeg
  DOWNLOAD_NO_PROGRESS 1
  URL https://github.com/LuaDist/libjpeg/archive/master.zip
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/libjpeg
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/libjpeg -DBUILD_STATIC=ON
)

set(LIBJPEG_INCLUDE_DIR "${CMAKE_BINARY_DIR}/libjpeg/include")
set(LIBJPEG_LIBRARY "${CMAKE_BINARY_DIR}/libjpeg/lib/libjpeg.a")

include_directories(SYSTEM ${LIBJPEG_INCLUDE_DIR})

set(IRRBAW_DEPENDENCY_LIBRARIES
    ${IRRBAW_DEPENDENCY_LIBRARIES}
    ${LIBJPEG_LIBRARY}
    )