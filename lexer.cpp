#include <cctype>
#include <forward_list>
#include <lexer.hpp>
#include <stdexcept>


Lexer::TokenStream Lexer::tokenize(std::string& script) {
	script.append("\1\1\1");
	using Type = Token::Type;
	Lexer::TokenStream ret{new std::forward_list<Token>};

	size_t i = 0;
	while (i < script.length()-3) {
		if (std::isspace(script[i])) {
			while (std::isspace(script[++i]));
			continue;
		}

		Type t = Type::UNKNOWN;
		
		if (std::isalpha(script[i])) {
			t = Type::IDENTIFIER;
			do {i++;} while (std::isalpha(script[i]) || std::isdigit(script[i]));
			continue;
		}

		if (std::isdigit(script[i])) {
			t = Type::INTEGER;
			do { i++; } while (std::isdigit(script[i]));
			if (script[i] == '.' && std::isdigit(script[i+1])) {
				t = Type::DOUBLE;
				i += 1;
				do { i++; } while (std::isdigit(script[i]));
			}
			ret->emplace_front(t);
			continue;
		}

		switch (script[i]) {
			case '(': { t = Type::LPAREN; break; }
			case ')': { t = Type::RPAREN; break; }
			case '\'': {
				t = Type::STRING;
				do { i++; } while (i < script.length()-3 && script[i] != '\'');
				if (script[i] != '\'')
					throw std::runtime_error("Unterminated string.");
				break;
			}
			case '+': { t = Type::OP_ADD; break; }
			case '-': { t = Type::OP_SUB; break; }
			case '*': { t = Type::OP_MUL; break; }
			case '/': { t = Type::OP_DIV; break; }
		}
		i++;
		ret->emplace_front(t);
	}
	ret->emplace_front(Type::EOS);

	return ret;
}