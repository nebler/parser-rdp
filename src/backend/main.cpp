#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <iostream>
#include <fstream>
#include "syntax_tree.pb.h"
int main()
{
    // Initialize the LLVM infrastructure
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    // Read the serialized data from the file
    // Open the binary file written by the Rust code
    std::ifstream input("syntax_tree.bin", std::ios::in | std::ios::binary);
    if (!input)
    {
        std::cerr << "Failed to open syntax_tree.bin" << std::endl;
        return -1;
    }

    // Deserialize the data
    syntax_tree::SyntaxTree tree;
    if (!tree.ParseFromIstream(&input))
    {
        std::cerr << "Failed to parse syntax tree from file" << std::endl;
        return -1;
    }

    // Access the deserialized data
    if (tree.has_root())
    {
        const syntax_tree::ASTNode &node = tree.root();
        std::cout << "Root node name: " << node.name() << std::endl;
        // Further processing...
    }

    return 0;
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
