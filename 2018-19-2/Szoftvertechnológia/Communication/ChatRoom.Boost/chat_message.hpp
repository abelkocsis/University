// Copyright goes to Christopher M. Kohlhoff
// for the original version of this sample program.

#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>

class chat_message
{
public:
  static const int HEADER_LENGTH = 4;
  static const int MAX_BODY_LENGTH = 5000;

  chat_message()
    : _body_length(0)
  {
  }

  const char* data() const
  {
    return _data;
  }

  char* data()
  {
    return _data;
  }

  std::size_t length() const
  {
    return HEADER_LENGTH + _body_length;
  }

  const char* body() const
  {
    return _data + HEADER_LENGTH;
  }

  char* body()
  {
    return _data + HEADER_LENGTH;
  }

  std::size_t body_length() const
  {
    return _body_length;
  }

  void body_length(std::size_t new_length)
  {
    _body_length = new_length;
    if (_body_length > MAX_BODY_LENGTH)
      _body_length = MAX_BODY_LENGTH;
  }

  bool decode_header()
  {
    char header[HEADER_LENGTH + 1] = "";
    std::strncat(header, _data, HEADER_LENGTH);
    _body_length = std::atoi(header);
    if (_body_length > MAX_BODY_LENGTH)
    {
      _body_length = 0;
      return false;
    }
    return true;
  }

  void encode_header()
  {
    char header[HEADER_LENGTH + 1] = "";
    std::sprintf(header, "%4d", static_cast<int>(_body_length));
    std::memcpy(_data, header, HEADER_LENGTH);
  }

private:
  char _data[HEADER_LENGTH + MAX_BODY_LENGTH];
  std::size_t _body_length;
};

#endif // CHAT_MESSAGE_HPP
