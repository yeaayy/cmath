#ifndef PARSER_STREAM_HPP
#define PARSER_STREAM_HPP

#include <istream>

namespace Parser {

class stream {
public:
    stream(const char *str);
    stream(std::istream &stream);
    stream(const stream &src);
    ~stream();
	int get();
	void read(void *dst, int len = 1);
	int peek(int n = 0);
	bool eof(int n = 0);
	int tellg();
	void seek(int n = 1);
	void start(int n = 0);
	void end(int n = 0);
	friend bool operator==(const stream &stream1, const stream &stream2);

private:
    stream(int size, char *buffer);
	char *_buffer;
	int _index;
	int _len;
	bool _real;
};


} // namespace Parser

#endif /* PARSER_STREAM_HPP */
