#include <functional>
#include <iostream>

#pragma once
namespace wbr::base {

//	ヌル型
	class Null {};

//	ベクトル型(T:値の型, N:次元数)
	template <class _T, int N> class Vector : public Vector<_T, N-1> {
	public:
		using T = _T&&;	//	値の型
		using This = Vector<_T, N>&&;	//	自身の型
		using Prev = Vector<_T, N+1>;
		using Next = Vector<_T, N-1>;	//	以降の次元のベクトルの型

		using CT = const _T&&;
		using CThis = const Vector<_T, N>&&;
		using CNext = const Next&&;
		 
	//
	//	■■■■　最初の次元の値　■■■■
	//
	//	最初の次元の値
		_T v;
		
	//	最初の次元の値を返す
		explicit operator       _T& ()       { return v; }
		explicit operator       _T&&()       { return (_T&&)v; }
		explicit operator       _T  () const { return v; }
		explicit operator const _T& () const { return v; }
		explicit operator const _T&&() const { return (_T&&)v; }

	//
	//	■■■■　コンストラクタ　■■■■
	//
	//	何も引数が無い
		Vector() = default;


	//	最初の次元の値と、以降の次元のベクトルで初期化する
		Vector(T v, Next next) : v((T)v), Next(next) {
		//	std::cout << "Vector(T, CNext)\n";
		}

	//	各次元の値で初期化する (ムーブ)
		template <class... Types> Vector(T v, Types&&... args) : v((T)v), Next(args...) {
		//	std::cout << "Vector(T, Types&&...)\n";
		}
		
	//	各次元の値で初期化する (参照渡し)
		template <class... Types> Vector(const _T& v, Types&&... args) : v((T)v), Next(args...) {
		//	std::cout << "Vector(const _T&, Types&&...)\n";
		}

	//	一つの同じ値ですべての次元を初期化する
	//	template <class... Types> explicit Vector(T v) : v((T)v), Next((T)v) {}
		
	//
	//	■■■■  二項関数  ■■■■
	//
	//	型Retを返す, T型の二項関数
	/*
		template <class Ret>
		using CTFunc2 = std::function<Ret(CT, CT)>;

		template <class Ret>
		using  TFunc2 = const std::function<Ret( T,  T)>&&;
		
		using CTVoidFunc2 = const std::function<void(CT, CT)>&&;

		using  TVoidFunc2 = const std::function<void( T,  T)>&&;


		using CTTFunc2 = const std::function<_T(CT, CT)>&&;

	//	自身と別のベクトルとの2ベクトルに関して、各次元に関して関数を適用した結果のベクトルを返す (const)
		Vector<_T, N> forEach(CTTFunc2 func, CThis t) const {
			

			if constexpr(N == 1){
				return func((CT)*this, (CT)t);
			}else{
				return {
					func((CT)*this, (CT)t),
					Next::forEach((CTTFunc2)func, (CThis)t)
				};
			}

		}
	*/

	private:
		template <class A, class B> static auto makeVector(A&& a, B&& b) {
			return B::Prev((A&&)a, (B&&)b);
		}

		template <class A> static auto makeVector(A&& a, Null) {
			return Vector<A, 1>((A&&)a);
		}


	public:
	//
	//	□□□□  forEach  □□□□
	//
		
	//	自身と別のベクトルとの2ベクトルに関して、各次元に関して関数を適用した結果のベクトルを返す (const)
		template <class Func> auto forEach(Func func, CThis t) const {
			
			return makeVector(
				func((CT)*this, (CT)t),
				Next::forEach(func, (CThis)t)
			);

		}

	//	自身と別のベクトルとの2ベクトルに関して、各次元に関して関数を適用した結果のベクトルを返す (not const)
		template <class Func> auto forEach(Func func, CThis t) {
			
			return makeVector(
				func((T)*this, (CT)t),
				Next::forEach(func, (CThis)t)
			);

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
		template <class Ret>
		using CTFunc1 = const std::function<Ret(CT)>&&;

		template <class Ret>
		using  TFunc1 = const std::function<Ret( T)>&&;
		
		using CTVoidFunc1 = const std::function<void(CT)>&&;

		using  TVoidFunc1 = const std::function<void( T)>&&;

	/*
	//	自身の各次元に関して関数を適用した結果のベクトルを返す (const)
		template <class Ret>
		Vector<Ret, N> forEach(CTFunc1<Ret> func) const {

			if constexpr(N == 1) return func((CT)*this);
			return {
				func((CT)*this),
				Next::forEach((CTFunc1<Ret>)func)
			};

		}

	//	自身の各次元に関して関数を適用した結果のベクトルを返す (not const)
		template <class Ret>
		Vector<Ret, N> forEach(TFunc1<Ret> func) {

			if constexpr(N == 1) return func((T)*this);
			return {
				func((T)*this),
				Next::forEach((TFunc1<Ret>)func)
			};

		}
	*/

		
	//	自身の各次元に関して関数を適用する (const)
		void doEach(CTVoidFunc1 func) const {

			func((CT)*this);
			if constexpr(N > 1) Next::doEach((CTVoidFunc1)func);

		}

	//	自身の各次元に関して関数を適用する (not const)
		void doEach(TVoidFunc1 func) {

			func((T)*this);
			if constexpr(N > 1) Next::doEach((TVoidFunc1)func);

		}
	

	};



	template <class _T> class Vector<_T, 0> {
	public:
		using T = _T&&;	//	値の型

	//
	//	■■■■　コンストラクタ　■■■■
	//
	//	通常時
		Vector() = default;

	//	各次元の値で初期化する⇒初期化できなかった値があるので静的エラー
		template <class... Types> Vector(Types&&... args) {
			static_assert(false, "Invalid initializer list.");
		}

	//	一つの同じ値ですべての次元を初期化していった場合⇒何もしない
	//	template <class... Types> explicit Vector(T v) {}



		template <class... Types> Null forEach(Types&&...) const { return {}; }
		template <class... Types> Null forEach(Types&&...)       { return {}; }

	};





	template <class T, class... Types> auto make_vector(const T& v, Types&&... args) {
		return Vector<T, sizeof...(args)+1>(v, args...);
	}
	
/*
	template <class T, class... Types> auto make_vector(T&& v, Types&&... args) {
		return Vector<T, sizeof...(args)+1>((T&&)v, args...);
	}
*/

}
