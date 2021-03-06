//printing hello world!

#include "llvm/Support/TargetSelect.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Constants.h"
#include "llvm/Function.h"
#include "llvm/DerivedTypes.h"
#include "llvm/Instructions.h"
#include "llvm/BasicBlock.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ExecutionEngine/JIT.h"

#include <vector>
#include <cstdio>
#include <string>


int main() {
    llvm::InitializeNativeTarget();
    llvm::LLVMContext & context = llvm::getGlobalContext();
    llvm::Module *module = new llvm::Module("asdf", context);

    //create ExecutionEngine
    llvm::EngineBuilder engine_builder = llvm::EngineBuilder(module);
    std::string err_str;
    engine_builder.setErrorStr(&err_str);
    llvm::ExecutionEngine *engine = engine_builder.create();
    if (!engine) {
        fprintf(stderr, "err: %s\n", err_str.c_str());
        exit(1);
    }

    //commonly used types
    llvm::IntegerType* Char = llvm::Type::getInt8Ty(context);
    llvm::IntegerType* Int = llvm::Type::getInt32Ty(context);
    llvm::Type* CharPtr = llvm::PointerType::get(Char, 0);

    //printf takes one char*
    llvm::ArrayRef<llvm::Type*> printf_arg_types = llvm::makeArrayRef(CharPtr);

    //int printf(char*, ...)
    llvm::FunctionType *printf_type = llvm::FunctionType::get(
            Int
            , printf_arg_types
            , true);

    //declare printf
    llvm::Function *printf_func = llvm::cast<llvm::Function>(
            module->getOrInsertFunction("printf", printf_type));


    //declare main function
    llvm::Function *main_func = llvm::cast<llvm::Function>(
            module->getOrInsertFunction(
                "main"
                , Int                               //return type
                , static_cast<llvm::Type*>(0)));    //END_WITH_NULL

    //main function block
    llvm::BasicBlock *block = llvm::BasicBlock::Create(
            context
            , "main_block"
            , main_func);


    //argument to printf: "hello world!"
    //c-strings should be GlobalVariable (?)
    llvm::Constant *cstr = llvm::ConstantArray::get(context, "hello world!\n");
    llvm::GlobalVariable *cstr_var = new llvm::GlobalVariable(
            *module
            , cstr->getType()
            , true
            , llvm::GlobalVariable::InternalLinkage
            , cstr
            , "");

    //from http://comments.gmane.org/gmane.comp.compilers.llvm.devel/4115
    llvm::Constant *get_element_ptr_params[] = {
            llvm::Constant::getNullValue(Int)
            , llvm::Constant::getNullValue(Int)
    };
    llvm::Value *arg = llvm::ConstantExpr::getGetElementPtr(
            cstr_var
            , get_element_ptr_params
            , llvm::array_lengthof(get_element_ptr_params));
    llvm::ArrayRef<llvm::Value*> printf_args = llvm::makeArrayRef(arg);

    //printf("hello world!\n");
    llvm::CallInst::Create(
            printf_func
            , printf_args
            , ""
            , block);

    //return 0;
    llvm::ReturnInst::Create(
            context
            , llvm::ConstantInt::get(Int, 0, true)
            , block);

    std::vector<llvm::GenericValue> void_arg;
    engine->runFunction(main_func, void_arg);
    delete module;
    return 0;
}
