#pragma once
#include "../utils/vector.h"

namespace wbr::math {

	template <class _T, int N>
	class Vector : public ::wbr::base::Vector<_T, N> {
	public:
		using CT = const _T&&;
		using Base = ::wbr::base::Vector<_T, N>;
		using _This = Vector<_T, N>;
		using This = _This&&;
		using CThis = const _This&&;
		using _CThis = const _This&;

		using Base::Vector;

		auto operator +(_CThis v) const {
			return Base::forEach(
				[](CT a, CT b){ return a + b; },
				v
			);
		}

	};

}
