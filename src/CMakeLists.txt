add_definitions(-D_GNU_SOURCE
    -D__STDC_LIMIT_MACROS
    -D__STDC_CONSTANT_MACROS)

set(CMAKE_CXX_FLAGS
    "-Wall -W -Wno-unused-parameter -Wwrite-strings -pedantic -Wno-long-long")

include_directories(${LLVM_INCLUDE})

link_directories(${LLVM_LIB})

add_subdirectory(execution-engine-setup)
add_subdirectory(hello-world)

