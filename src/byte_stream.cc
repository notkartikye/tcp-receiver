#include "byte_stream.hh"
#include <deque>
#include <algorithm>

using namespace std;

ByteStream::ByteStream(const size_t capa)
{
  capacity_ = capa; // Initialize capacity
  input_ended_ = false;
  bytes_written_ = 0;
  bytes_read_ = 0;
  buffer_.clear(); // Initialize empty buffer
}

size_t ByteStream::write(const string &data)
{
  // If input has ended, no more bytes can be written
  if (input_ended_)
  {
    return 0;
  }

  // Calculate available space in the buffer
  size_t available_space = capacity_ - buffer_.size();
  
  // If the buffer is already full, no more bytes can be written
  if (available_space == 0)
  {
    return 0;
  }

  // Total number of bytes to be written
  size_t bytes_to_write = std::min(data.size(), available_space);

  // Copy bytes from 'data' to the buffer
  buffer_.insert(buffer_.end(), data.begin(), data.begin() + bytes_to_write);
  bytes_written_ += bytes_to_write;

  return bytes_to_write;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const
{
  // Total bytes that can be peeked (minimum of len and buffer size)
  size_t peek_size = std::min(len, buffer_.size());
  
  // Copy the peeked bytes from the buffer into a new string
  std::string peeked_bytes(buffer_.begin(), buffer_.begin() + peek_size);
  
  return peeked_bytes;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len)
{
  // If len is greater than buffer size, throw an error and clear the buffer
  if (len > buffer_.size())
  {
    set_error();
    buffer_.clear();
    bytes_read_ += buffer_.size();  // Update bytes read
  }
  else
  {
    // Remove len bytes from the output side of the buffer
    buffer_.erase(buffer_.begin(), buffer_.begin() + len);
    bytes_read_ += len;  // Update bytes read
  }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len)
{
  // If requested length is greater than the buffer size
  if (len > buffer_.size())
  {
    // Throw error and return an empty string
    set_error();
    return "";
  }

  // Copy the read bytes from the buffer into a new string
  std::string read_bytes(buffer_.begin(), buffer_.begin() + len);

  // Remove len bytes from the output side of the buffer
  buffer_.erase(buffer_.begin(), buffer_.begin() + len);
  bytes_read_ += len;  // Update bytes read

  return read_bytes;
}

void ByteStream::end_input() { input_ended_ = true;}

bool ByteStream::input_ended() const { return input_ended_;}

size_t ByteStream::buffer_size() const { return buffer_.size();}

bool ByteStream::buffer_empty() const { return buffer_.empty();}

bool ByteStream::eof() const { return buffer_.empty() && input_ended_;}

size_t ByteStream::bytes_written() const { return bytes_written_;}

size_t ByteStream::bytes_read() const { return bytes_read_;}

size_t ByteStream::remaining_capacity() const { return capacity_ - buffer_.size();}
