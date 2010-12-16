#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Constants.h"
#include "llvm/Function.h"
#include "llvm/DerivedTypes.h"
#include "llvm/Instructions.h"

#include <vector>

int main() {
    llvm::LLVMContext & context = llvm::getGlobalContext();
    llvm::Module *module = new llvm::Module("asdf", context);
    llvm::Value *cstr = llvm::ConstantArray::get(context, "hello world!");

    llvm::IntegerType const* Char = llvm::Type::getInt8Ty(context);
    llvm::IntegerType const* Int = llvm::Type::getInt32Ty(context);
    std::vector<const llvm::Type*> function_arg_types;
    function_arg_types.push_back(Char);

    llvm::FunctionType *function_type = llvm::FunctionType::get(
            Int
            , function_arg_types
            , true);

    llvm::Constant *function = module->getOrInsertFunction(
            "printf"
            , function_type);
    std::vector<llvm::Value*> function_args;
    function_args.push_back(cstr);
    llvm::CallInst::Create(function
            , function_args.begin(), function_args.end());

    /*
    llvm::Function *function = llvm::Function::Create(
            function_type
            , llvm::Function::ExternalLinkage
            , "printf"
            , module);
    */
    delete module;
    return 0;
}
