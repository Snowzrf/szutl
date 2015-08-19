

#ifndef SZUTL_BINARY_DATA_LOADER_H_
#define SZUTL_BINARY_DATA_LOADER_H_

// In-house headers

// Third-party headers:
#include <fstream>
#include <iostream>
#include <cstdint>

namespace szutl {


/// @brief Load in binary data from a file and allow retrieval; 
/// when it goes out of scope, it automatically cleans itself 
class BinaryDataLoader {
  public:
    // Ctor
    BinaryDataLoader(); 

    // Dtor
    ~BinaryDataLoader();

    bool LoadData(const std::string &img_file_path); 

    char *data() {
      return data_;
    }

    std::uint32_t file_size() const {
      return file_size_;
    }

  private:
    // Ptr to loaded data
    char *data_; 

    // File size
    std::uint32_t file_size_;

}; // class BinaryDataLoader

} // namespace szutl

#endif
