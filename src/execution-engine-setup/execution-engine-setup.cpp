//this shows how to create ExecutionEngine.

#include "llvm/Support/TargetSelect.h"
//#include "llvm/ExecutionEngine/JIT.h"
//either JIT.h or Interpreter.h (or both) *has to* be included.
//otherwise, though it compiles and links fine,
//ExecutionEngine cannot be created.

//I'm going to use LLVMInterpreter.
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"

#include <cstdio>
#include <string>

int main() {
    llvm::LLVMContext & context = llvm::getGlobalContext();
    llvm::Module *module = new llvm::Module("asdf", context);

    llvm::EngineBuilder engine_builder = llvm::EngineBuilder(module);
    std::string err_str;
    engine_builder.setErrorStr(&err_str);//err_str will contain error messages.
    llvm::ExecutionEngine *engine = engine_builder.create();

    if (!engine) {
        fprintf(stderr, "err: %s\n", err_str.c_str());
        exit(1);
    }
    printf("success\n");
    return 0;
}
//g++ `llvm-config --cxxflags` execution-engine-setup.cpp `llvm-config --ldflags --libs jit native`
