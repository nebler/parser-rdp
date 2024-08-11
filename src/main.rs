mod filereader;
use std::env;
fn main() {
    let args: Vec<String> = env::args().collect();
    let file_name = &args[1];
    filereader::read_file(file_name);

    println!("Hello, world!");
}
