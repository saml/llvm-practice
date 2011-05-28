cmake_minimum_required(VERSION 2.8)
project(llvm-practice)

#set these to your liking from command line:
#cmake -DLLVM_HOME=/path/to/llvm -G 'Unix Makefiles' ..
#set(CMAKE_INSTALL_PREFIX $ENV{HOME}/opt)

if(NOT LLVM_INCLUDE)
    set(LLVM_INCLUDE "/usr/include") #where llvm/*.h files are located.
endif()
if(NOT LLVM_LIB)
    set(LLVM_LIB "/usr/lib/llvm")    #where libLLVM*.so files are located.
endif()

add_subdirectory(src)
