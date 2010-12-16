cmake_minimum_required(VERSION 2.8)
project(llvm-practice)

#set these to your liking from command line:
#cmake -DLLVM_HOME=/path/to/llvm -G 'Unix Makefiles' ..
#set(CMAKE_INSTALL_PREFIX $ENV{HOME}/opt)
#set(LLVM_HOME /usr/lib/llvm-2.8)
set(LLVM_INCLUDE "${LLVM_HOME}/include")
set(LLVM_LIB "${LLVM_HOME}/lib")

add_subdirectory(src)
