#include "format.h"

int main() {
	FormatParser f;
	f.SetString("bla {1} {2}{}{3,bla,blup}{4,k=akj,nl,jsl=22}{{5}} }}{{");	

	while (!f.IsAtEnd()) {
		char c=f.Step();
		switch (c) {
				case '{': f.ReadLeftBrace(); break;
				case '}': f.ReadRightBrace(); break;
				case ',': f.ReadComma(); break;
				case '=': f.ReadEqualsSign(); break;
				default : f.Continue(); break;
		}
		std::cout<<c;
	}
	std::cout<<std::endl;
}