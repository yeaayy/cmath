#include "parser/stream.hpp"

#include <cstdlib>
#include <cstring>
#include <sstream>

namespace Parser {

stream::stream(const char *_buffer)
    : stream(strlen(_buffer), strdup(_buffer))
{
    _real = false;
}

stream::stream(std::istream &stream)
    : _index(0)
    , _real(true)
{
    stream.seekg(0, std::ios::end);
    std::streampos length;
    if(stream) {
        length = stream.tellg();
        stream.seekg(0,std::ios::beg);
        _buffer = (char*) malloc(length + (std::streampos) 1);
        stream.read(_buffer, length);
    } else {
        std::stringstream str;
        stream.clear();
        str << stream.rdbuf();
        length = str.tellp();
        _buffer = (char*) malloc(length + (std::streampos) 1);
        str.read(_buffer, length);
    }
    _buffer[length] = '\0';
    _len = length;
}

stream::stream(int size, char *_buffer)
	: _buffer((char*) _buffer)
    , _index(0)
    , _len(size)
    , _real(true)
{}

stream::stream(const stream &src)
    : _buffer(src._buffer)
    , _index(src._index)
    , _len(src._len)
    , _real(false)
{}

stream::~stream() {
    if(_real) {
        free(_buffer);
    }
}

int stream::get()
{
	return eof() ? -1 : _buffer[_index++];
}

void stream::read(void *dst, int len)
{
	memcpy(dst, &_buffer[_index], len);
    _index += len;
}

int stream::peek(int n)
{
	return eof(n) ? -1 : _buffer[_index + n];
}

bool stream::eof(int n)
{
	return (_index + n) >= _len;
}

int stream::tellg()
{
	return _index;
}

void stream::seek(int n)
{
	_index += n;
}

void stream::start(int n)
{
	_index = n;
}

void stream::end(int n)
{
	_index = _len + n;
}

bool operator==(const stream &stream1, const stream &stream2) {
    return stream1._buffer == stream2._buffer;
}

} // namespace Parser
