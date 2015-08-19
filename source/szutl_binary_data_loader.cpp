
#include <szutl_binary_data_loader.h>

namespace szutl {

BinaryDataLoader::BinaryDataLoader() :
    data_(nullptr),
    file_size_(0) {
}

BinaryDataLoader::~BinaryDataLoader() {
  if(data_ != nullptr) {
    delete data_;

    data_ = nullptr;
  } 
}

bool BinaryDataLoader::LoadData(const std::string &img_file_path) {
  // Attempt to open the file
  try {
    // Filesize
    std::streampos file_size_ = 0;

    // File input stream
    std::ifstream ifs;

    // Binary mode
    ifs.open(img_file_path, std::ios::binary);

    if (ifs.is_open() == false) {
      std::cerr << "LoadOCLRawImg: Exception opening/reading/closing file " <<
        img_file_path << ".\n";

      throw;
    }

    // Read beginning of file get pos
    file_size_ = ifs.tellg();

    // Move to end of file
    ifs.seekg(0, std::ios::end);

    // Read file size
    file_size_ = ifs.tellg() - file_size_;

    std::cout << "Size of file " << img_file_path <<
      ": " << file_size_ << " bytes.\n";

    // Allocate space in main memory for the data
    file_size_ = static_cast<std::uint32_t>(file_size_);
    data_ = new char[file_size_];

    // Move g ptr back at the beginning
    ifs.seekg(0, std::ifstream::beg);

    // Read the data in main memory
    ifs.read(data_, file_size_);

    // Close the file
    ifs.close();
  } 
  catch (std::ifstream::failure e) {
    // Cleanup
    if(data_ != nullptr) {
      delete[] data_;
      data_ = nullptr;
    }

    std::cerr << "LoadOCLRawImg: Exception opening/reading/closing file " <<
      img_file_path << ".\n";

    return false;
  }

  return true;
} 


} // namespace szutl
