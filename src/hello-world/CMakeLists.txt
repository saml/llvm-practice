project(hello-world)
add_executable(${PROJECT_NAME} hello-world.cpp)
target_link_libraries(${PROJECT_NAME}
pthread
ffi
dl
m

LLVMX86Disassembler
LLVMX86AsmParser
LLVMX86CodeGen
LLVMX86Desc
LLVMSelectionDAG
LLVMAsmPrinter
LLVMMCParser
LLVMX86AsmPrinter
LLVMX86Utils
LLVMX86Info
LLVMJIT
LLVMExecutionEngine
LLVMCodeGen
LLVMScalarOpts
LLVMInstCombine
LLVMTransformUtils
LLVMipa
LLVMAnalysis
LLVMTarget
LLVMMC
LLVMCore
LLVMSupport
)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
