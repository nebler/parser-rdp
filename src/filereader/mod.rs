use std::fs;
pub fn read_file(file_path: &str) -> String {
    println!("Reading file! {}", file_path);
    return fs::read_to_string(file_path).expect("You should have been able to read that");
}
