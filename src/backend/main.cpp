#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

int main()
{
    // Initialize the LLVM infrastructure
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    // Create a new LLVM context
    llvm::LLVMContext context;

    // Create a new module
    std::unique_ptr<llvm::Module> module = std::make_unique<llvm::Module>("my_module", context);

    // Create a function signature: int foo()
    llvm::FunctionType *funcType = llvm::FunctionType::get(llvm::Type::getInt32Ty(context), false);
    llvm::Function *fooFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "foo", module.get());

    // Create a basic block and attach it to the function
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entry", fooFunc);

    // Create an IR builder and set it to insert into the new basic block
    llvm::IRBuilder<> builder(entry);

    // Return a constant integer value 42
    builder.CreateRet(llvm::ConstantInt::get(context, llvm::APInt(32, 42)));

    // Print the generated LLVM IR to stdout
    module->print(llvm::outs(), nullptr);

    return 0;
}
