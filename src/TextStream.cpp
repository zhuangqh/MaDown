#include <fstream>
#include <sstream>
#include "TextStream.h"

namespace md {
  namespace IO {

    StringStream::StringStream(const std::string &str)
    : str_(str), pos_(0) {}

    void StringStream::set_string(const std::string &input) {
      str_ = input;
      pos_ = 0;
    }

    FileStream::FileStream(const std::string &path) : stream_(nullptr) {
#ifdef _MSC_VER
      fopen_s(&stream_, path.c_str(), "rb");
#else
      stream_ = fopen(path.c_str(), "rb");
#endif // _MSC_VER
    }

    FileStream::~FileStream() {
      if (stream_) {
        fclose(stream_);
      }
    }

    bool read_str_from_file(const std::string &path, std::string &res) {
      std::ifstream fs(path);

      if (fs.good()) {
        std::stringstream sstr;
        sstr << fs.rdbuf();
        res = sstr.str();
        fs.close();
        return true;
      } else {
        return false;
      }
    }

    bool write_str_to_file(const std::string &path, const std::string &str) {
      std::ofstream fs(path);

      if (fs.good()) {
        fs << str;
        fs.close();
        return true;
      } else {
        return false;
      }
    }

  } // namespace io
} // namespace md
