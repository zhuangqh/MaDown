#pragma once

#include <string>

namespace md {
  namespace IO {

    class StringStream {
    public:
      explicit StringStream(const std::string &str);

      StringStream(const StringStream&) = delete;
      void operator = (const StringStream&) = delete;

      void set_string(const std::string &input);

      int get_char() {
        if (pos_ < str_.size())
          return static_cast<unsigned char>(str_[pos_++]);
        else
          return EOF;
      }

    private:
      std::string str_;
      std::size_t pos_;
    };

    class FileStream {
    public:
      explicit FileStream(const std::string &path);
      ~FileStream();

      FileStream(const FileStream&) = delete;
      void operator = (const FileStream&) = delete;

      bool IsOpen() const {
        return stream_ != nullptr;
      }

      int get_char() {
        return fgetc(stream_);
      }

    private:
      FILE *stream_;
    };

    bool read_str_from_file(const std::string &path, std::string &res);

    bool write_str_to_file(const std::string &path, const std::string &str);

  } // namespace io
} // namespace md
