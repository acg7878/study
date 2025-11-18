#include <fstream>
#include <iostream>
#include <random>
#include <string>

void create_dummy_file(const std::string& filename, long long num_count) {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Could not create file " << filename << std::endl;
    return;
  }
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<long long> dis(1, 999999999999);

  std::cout << "Generating " << num_count << " numbers for '" << filename
            << "'..." << std::endl;
  for (long long i = 0; i < num_count; ++i) {
    file << dis(gen) << "\n";
  }
  std::cout << "Dummy file '" << filename << "' with " << num_count
            << " numbers created successfully." << std::endl;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <filename> <number_of_entries>"
              << std::endl;
    return 1;
  }

  std::string filename = argv[1];
  long long num_count = 0;
  try {
    num_count = std::stoll(argv[2]);
  } catch (const std::exception& e) {
    std::cerr << "Error: Invalid number of entries provided. Please enter a "
                 "valid number."
              << std::endl;
    return 1;
  }

  if (num_count <= 0) {
    std::cerr << "Error: Number of entries must be a positive integer."
              << std::endl;
    return 1;
  }

  create_dummy_file(filename, num_count);

  return 0;
}
