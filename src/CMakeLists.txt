add_definitions(-D_GNU_SOURCE
    -D__STDC_LIMIT_MACROS
    -D__STDC_CONSTANT_MACROS)

include_directories(${LLVM_INCLUDE})

link_directories(${LLVM_LIB})

add_subdirectory(hello-world)

