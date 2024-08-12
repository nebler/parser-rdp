use prost::Message;
use std::fs::File;
use std::io::Write;
mod syntax_tree; // Include the syntax module
fn main() -> Result<(), Box<dyn std::error::Error>> {
    // Create a sample node
    let node = syntax_tree::AstNode {
        r#type: syntax_tree::ast_node::NodeType::Function as i32,
        name: "main".to_string(),
        children: vec![],
        value: "".to_string(),
    };

    // Create the syntax tree
    let tree = syntax_tree::SyntaxTree { root: Some(node) };

    // Serialize the syntax tree to a vector of bytes
    let encoded = tree.encode_to_vec();

    // Write the serialized data to a binary file
    let mut file = File::create("syntax_tree.bin")?;
    file.write_all(&encoded)?;

    Ok(())
}
