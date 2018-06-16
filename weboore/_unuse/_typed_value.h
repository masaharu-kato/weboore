#pragma once
namespace wbr::base {

	template <class _T> class TypedValue {
	protected:
		
	//	’l
		_T v;

	public:
		
	//	’l‚ð•Ô‚·
		explicit operator       _T& ()       { return v; }
		explicit operator       _T&&()       { return (_T&&)v; }
		explicit operator       _T  () const { return v; }
		explicit operator const _T& () const { return v; }
		explicit operator const _T&&() const { return (_T&&)v; }

	};

}