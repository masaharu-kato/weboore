#include <functional>
#include <iostream>

#pragma once
namespace wbr::base {

//	�k���^
	class Null {};

//	�x�N�g���^(T:�l�̌^, N:������)
	template <class _T, int N> class Vector : public Vector<_T, N-1> {
	public:
		using T = _T&&;	//	�l�̌^
		using This = Vector<_T, N>&&;	//	���g�̌^
		using Prev = Vector<_T, N+1>;
		using Next = Vector<_T, N-1>;	//	�ȍ~�̎����̃x�N�g���̌^

		using CT = const _T&&;
		using CThis = const Vector<_T, N>&&;
		using CNext = const Next&&;
		 
	//
	//	���������@�ŏ��̎����̒l�@��������
	//
	//	�ŏ��̎����̒l
		_T v;
		
	//	�ŏ��̎����̒l��Ԃ�
		explicit operator       _T& ()       { return v; }
		explicit operator       _T&&()       { return (_T&&)v; }
		explicit operator       _T  () const { return v; }
		explicit operator const _T& () const { return v; }
		explicit operator const _T&&() const { return (_T&&)v; }

	//
	//	���������@�R���X�g���N�^�@��������
	//
	//	��������������
		Vector() = default;


	//	�ŏ��̎����̒l�ƁA�ȍ~�̎����̃x�N�g���ŏ���������
		Vector(T v, Next next) : v((T)v), Next(next) {
		//	std::cout << "Vector(T, CNext)\n";
		}

	//	�e�����̒l�ŏ��������� (���[�u)
		template <class... Types> Vector(T v, Types&&... args) : v((T)v), Next(args...) {
		//	std::cout << "Vector(T, Types&&...)\n";
		}
		
	//	�e�����̒l�ŏ��������� (�Q�Ɠn��)
		template <class... Types> Vector(const _T& v, Types&&... args) : v((T)v), Next(args...) {
		//	std::cout << "Vector(const _T&, Types&&...)\n";
		}

	//	��̓����l�ł��ׂĂ̎���������������
	//	template <class... Types> explicit Vector(T v) : v((T)v), Next((T)v) {}
		
	//
	//	��������  �񍀊֐�  ��������
	//
	//	�^Ret��Ԃ�, T�^�̓񍀊֐�
	/*
		template <class Ret>
		using CTFunc2 = std::function<Ret(CT, CT)>;

		template <class Ret>
		using  TFunc2 = const std::function<Ret( T,  T)>&&;
		
		using CTVoidFunc2 = const std::function<void(CT, CT)>&&;

		using  TVoidFunc2 = const std::function<void( T,  T)>&&;


		using CTTFunc2 = const std::function<_T(CT, CT)>&&;

	//	���g�ƕʂ̃x�N�g���Ƃ�2�x�N�g���Ɋւ��āA�e�����Ɋւ��Ċ֐���K�p�������ʂ̃x�N�g����Ԃ� (const)
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
	//	��������  forEach  ��������
	//
		
	//	���g�ƕʂ̃x�N�g���Ƃ�2�x�N�g���Ɋւ��āA�e�����Ɋւ��Ċ֐���K�p�������ʂ̃x�N�g����Ԃ� (const)
		template <class Func> auto forEach(Func func, CThis t) const {
			
			return makeVector(
				func((CT)*this, (CT)t),
				Next::forEach(func, (CThis)t)
			);

		}

	//	���g�ƕʂ̃x�N�g���Ƃ�2�x�N�g���Ɋւ��āA�e�����Ɋւ��Ċ֐���K�p�������ʂ̃x�N�g����Ԃ� (not const)
		template <class Func> auto forEach(Func func, CThis t) {
			
			return makeVector(
				func((T)*this, (CT)t),
				Next::forEach(func, (CThis)t)
			);

		}

		
	//
	//	��������  doEach  ��������
	//
	//	2�̃x�N�g���Ɋւ��āA�e�����Ɋւ��Ċ֐���K�p���� (const)
		template <class Func> void doEach(Func func, CThis t) const {

			func((CT)*this, (CT)t);
			if constexpr(N > 1) Next::doEach(func, (CThis)t);

		}

	//	2�̃x�N�g���Ɋւ��āA�e�����Ɋւ��Ċ֐���K�p���� (not const)
		template <class Func> void doEach(Func func, CThis t) {

			func((T)*this, (CT)t);
			if constexpr(N > 1) Next::doEach(func, (CThis)t);

		}

		
	//
	//	���������@�P���֐��@��������
	//
	//	�^Ret��Ԃ�, T�^�̒P���֐�
		template <class Ret>
		using CTFunc1 = const std::function<Ret(CT)>&&;

		template <class Ret>
		using  TFunc1 = const std::function<Ret( T)>&&;
		
		using CTVoidFunc1 = const std::function<void(CT)>&&;

		using  TVoidFunc1 = const std::function<void( T)>&&;

	/*
	//	���g�̊e�����Ɋւ��Ċ֐���K�p�������ʂ̃x�N�g����Ԃ� (const)
		template <class Ret>
		Vector<Ret, N> forEach(CTFunc1<Ret> func) const {

			if constexpr(N == 1) return func((CT)*this);
			return {
				func((CT)*this),
				Next::forEach((CTFunc1<Ret>)func)
			};

		}

	//	���g�̊e�����Ɋւ��Ċ֐���K�p�������ʂ̃x�N�g����Ԃ� (not const)
		template <class Ret>
		Vector<Ret, N> forEach(TFunc1<Ret> func) {

			if constexpr(N == 1) return func((T)*this);
			return {
				func((T)*this),
				Next::forEach((TFunc1<Ret>)func)
			};

		}
	*/

		
	//	���g�̊e�����Ɋւ��Ċ֐���K�p���� (const)
		void doEach(CTVoidFunc1 func) const {

			func((CT)*this);
			if constexpr(N > 1) Next::doEach((CTVoidFunc1)func);

		}

	//	���g�̊e�����Ɋւ��Ċ֐���K�p���� (not const)
		void doEach(TVoidFunc1 func) {

			func((T)*this);
			if constexpr(N > 1) Next::doEach((TVoidFunc1)func);

		}
	

	};



	template <class _T> class Vector<_T, 0> {
	public:
		using T = _T&&;	//	�l�̌^

	//
	//	���������@�R���X�g���N�^�@��������
	//
	//	�ʏ펞
		Vector() = default;

	//	�e�����̒l�ŏ���������ˏ������ł��Ȃ������l������̂ŐÓI�G���[
		template <class... Types> Vector(Types&&... args) {
			static_assert(false, "Invalid initializer list.");
		}

	//	��̓����l�ł��ׂĂ̎��������������Ă������ꍇ�ˉ������Ȃ�
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
