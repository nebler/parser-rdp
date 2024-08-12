use std::env;
use std::path::PathBuf;

fn main() {
    let out_dir = PathBuf::from(env::var("OUT_DIR").unwrap());

    prost_build::Config::new()
        .out_dir(out_dir)
        .compile_protos(&["src/syntax_tree.proto"], &["src/"])
        .unwrap();
}
