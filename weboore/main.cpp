#include <iostream>
#include "vector.h"
using namespace wbr;

using Vector = base::Vector<int, 3>;

void vector_out(const Vector& v) {
	std::cout << "(";
	v.doEach([&](Vector::CT v){std::cout << v << ", "; } );
	std::cout << ")\n";
}

int main(void) {

	const Vector vec1(10, 20, 30);
	const Vector vec2(5, 6, 7);

//	vec1.doEach([&](Vector::T v){std::cin >> v; });
//	vec2.doEach([&](Vector::T v){std::cin >> v; });

	Vector vec3 = vec1.forEach(
		[](Vector::CT v1, Vector::CT v2){
		//	std::cout << v1 << " + " << v2 << "\n";
		//	v1 += v2;
			return v1 + 10;
		},
		(const Vector&&)vec2
	);
	
	vector_out(vec1);
	vector_out(vec3);

	system("pause");
	return 0;
}
