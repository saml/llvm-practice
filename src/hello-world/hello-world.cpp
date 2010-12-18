#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Constants.h"
#include "llvm/Function.h"
#include "llvm/DerivedTypes.h"
#include "llvm/Instructions.h"
#include "llvm/BasicBlock.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"

#include <vector>


int main() {
    llvm::LLVMContext & context = llvm::getGlobalContext();
    llvm::Module *module = new llvm::Module("asdf", context);

    //commonly used types
    llvm::IntegerType const* Char = llvm::Type::getInt8Ty(context);
    llvm::IntegerType const* Int = llvm::Type::getInt32Ty(context);
    llvm::Type const* Void = llvm::Type::getVoidTy(context);
    llvm::PointerType const* CharPtr = llvm::PointerType::get(Char, 0);

    //printf takes one char*
    std::vector<const llvm::Type*> printf_arg_types;
    printf_arg_types.push_back(CharPtr);

    //int printf(char*, ...)
    llvm::FunctionType *printf_type = llvm::FunctionType::get(
            Int
            , printf_arg_types
            , true);

    //insert printf
    llvm::Function *printf_func = llvm::cast<llvm::Function>(
            module->getOrInsertFunction("printf", printf_type));

    //prepare for printf arguments
    llvm::Constant *cstr = llvm::ConstantArray::get(context, "hello world!");

    llvm::Type const* tmp = cstr->getType();
    llvm::GlobalVariable *cstr_var = new llvm::GlobalVariable(
            *module,
            tmp, true, llvm::GlobalVariable::InternalLinkage, cstr, "");

    std::vector<llvm::Value*> printf_args;
    printf_args.push_back(cstr_var);

    //main function
    llvm::Function *main_func = llvm::cast<llvm::Function>(
            module->getOrInsertFunction(
                "main_function"
                , Void                              //return type
                , static_cast<llvm::Type*>(0)));    //END_WITH_NULL

    //main function block
    llvm::BasicBlock *block = llvm::BasicBlock::Create(
            context
            , "main_block"
            , main_func);

    //
    llvm::CallInst *printf_call = llvm::CallInst::Create(
            printf_func
            , printf_args.begin()
            , printf_args.end()
            , ""
            , block);

    llvm::ExecutionEngine *engine = llvm::EngineBuilder(module).create();
    std::vector<llvm::GenericValue> void_arg;
    engine->runFunction(main_func, void_arg);
    delete module;
    return 0;
}
