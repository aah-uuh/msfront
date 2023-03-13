#include <exception>
#ifndef LEXER_H
#include <memory>
#include <forward_list>
#include <string>
#include <cstdint>

class Token {
public:
	enum class Type {
		UNKNOWN = 0,

		IDENTIFIER, LPAREN, RPAREN,

		STRING, INTEGER, DOUBLE,

		OP_ADD, OP_SUB, OP_MUL, OP_DIV,

		EOS = -1
	};

private:
	Type type;

public:
	Token() : type(Type::UNKNOWN) {}
	Token(Type type) : type(type) {}

	Type get_type() const {
		return type;
	}
};

namespace Lexer {
	using TokenStream = std::unique_ptr<std::forward_list<Token>>;
	TokenStream tokenize(std::string& script);
}

#endif