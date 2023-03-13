#include <iostream>
#include <lexer.hpp>
#include <stdexcept>
#include <string>


int main(int argc, char **argv) {
	std::string s;
	Lexer::TokenStream ts;
	std::getline(std::cin, s);
	try {
		ts = Lexer::tokenize(s);
		for (Token& t : *ts) {
			std::cout << (unsigned) t.get_type() << ' ';
		}
		std::cout << '\n';
	} catch (std::runtime_error& e) {
		std::cerr << "\033[31m" << e.what() << "\033[0m\n";
	}
	ts.reset();
	return 0;
}