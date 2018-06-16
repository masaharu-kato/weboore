#include <iostream>
#include "utils/op_func.h"
using namespace wbr::base;

/*
template <class VT> void vector_out(const VT& v) {
	std::cout << "(";
	v.doEach([&](typename VT::CT v){std::cout << v << ", "; } );
	std::cout << ")\n";
}
*/

int main(void) {

	while(true) {
		int x, y;
		std::cin >> x >> y;

		std::cout << "Add:" << OpFuncAdd::calc(x, y) << "\n";
		std::cout << "Sub:" << OpFuncSub::calc(x, y) << "\n";
		std::cout << "Mul:" << OpFuncMul::calc(x, y) << "\n";
		std::cout << "Div:" << OpFuncDiv::calc(x, y) << "\n";
	}

/*
	Vector<int, 3> vec1(15, 63, 59);
	Vector<int, 3> vec2(21, 33, 29);

//	vec1.doEach([&](Vector::T v){std::cin >> v; });
//	vec2.doEach([&](Vector::T v){std::cin >> v; });

	auto vec3 = vec1 + vec2;

	auto vec4 = vec1.forEach([](decltype(vec1)::CT v) { return v * v; });
	
	vector_out(vec1);
	vector_out(vec2);
	vector_out(vec3);
	vector_out(vec4);
*/

	system("pause");
	return 0;
}
