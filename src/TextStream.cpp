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

  } // namespace io
} // namespace md
