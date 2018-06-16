#pragma once
#include <type_traits>
#include <functional>

namespace wbr::base {

	template <class _T, class... _Rests>
	class TypeTuple : public TypeTuple<_Rests...> {
	public:
		using Next = TypeTuple<_Rests...>;

		using T = _T && ;	//	値の型
		using CT = const _T&&;
		using This = TypeTuple<_T, _Rests...>&&;	//	自身の型
		using CThis = const TypeTuple<_T, _Rests...>&&;
		using CNext = const Next&&;
		template <class A> using Prev = TypeTuple<A, _T, _Rests...>;

	private:
		//	値
		_T v;

	public:

		//	値を返す
		explicit operator _T& () { return v; }
		explicit operator _T && () { return (_T&&)v; }
		explicit operator _T  () const { return v; }
		explicit operator const _T& () const { return v; }
		explicit operator const _T && () const { return (_T&&)v; }


	public:
		TypeTuple() = default;

	//	最初の値と残りの値で初期化
		TypeTuple(T v, _Rests&&... args) : first((T)v), Rest(args...) {}

	//	最初の値と, 残りの値のタプルで初期化
		TypeTuple(T v, Next rest) : first((T)v), Next(rest) {}

	//	別の型タプルから抽出して初期化
		template <class... Types>
		TypeTuple(TypeTuple<Types...>&& tuple)
			: first((T&&)tuple), Rest((TypeTuple<Types...>&&)tuple) {}


	public:
		//	最初に別の値を追加したものを返す
		Prev getPushedFront(T v_prev) const {
			return Prev((T)v_prev, (CNext)*this);
		}

		//	最初の値を消去したものを返す
		CNext getPopedFront(T v_prev) const {
			return *this;
		}

		//
		//	□□□□  forEach  □□□□
		//

		//	自身と別のベクトルとの2ベクトルに関して、各次元に関して関数を適用した結果のベクトルを返す (const)
		template <class Func> auto forEach(Func func, CThis t) const {

			return Next::forEach(func, (CThis)t).getPushedFront(func((CT)*this, (CT)t));

		}

		//	自身と別のベクトルとの2ベクトルに関して、各次元に関して関数を適用した結果のベクトルを返す (not const)
		template <class Func> auto forEach(Func func, CThis t) {

			return Next::forEach(func, (CThis)t).getPushedFront(func((T)*this, (CT)t));

		}


		//
		//	□□□□  doEach  □□□□
		//
		//	2つのベクトルに関して、各次元に関して関数を適用する (const)
		template <class Func> void doEach(Func func, CThis t) const {

			func((CT)*this, (CT)t);
			if constexpr(N > 1) Next::doEach(func, (CThis)t);

		}

		//	2つのベクトルに関して、各次元に関して関数を適用する (not const)
		template <class Func> void doEach(Func func, CThis t) {

			func((T)*this, (CT)t);
			if constexpr(N > 1) Next::doEach(func, (CThis)t);

		}


		//
		//	■■■■　単項関数　■■■■
		//
		//	型Retを返す, T型の単項関数



		//	自身と別のベクトルとの2ベクトルに関して、各次元に関して関数を適用した結果のベクトルを返す (const)
		template <class Func> auto fEach(Func func) const {

			return Next::forEach(func).getPushedFront(func((CT)*this));

		}

		//	自身と別のベクトルとの2ベクトルに関して、各次元に関して関数を適用した結果のベクトルを返す (not const)
		template <class Func> auto forEach(Func func) {

			return Next::forEach(func).getPushedFront(func((T)*this));

		}


		//	自身の各次元に関して関数を適用する (const)
		template <class Func> void doEach(Func func) const {

			func((CT)*this);
			if constexpr(N > 1) Next::doEach((CTVoidFunc1)func);

		}

		//	自身の各次元に関して関数を適用する (not const)
		template <class Func> void doEach(Func func) {

			func((T)*this);
			if constexpr(N > 1) Next::doEach((TVoidFunc1)func);

		}





	};

};
