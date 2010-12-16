project(hello-world)
add_executable(${PROJECT_NAME} hello-world.cpp)
target_link_libraries(${PROJECT_NAME}
    pthread
    ffi
    dl
    m
    LLVMCore
    LLVMSupport
    LLVMSystem)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
