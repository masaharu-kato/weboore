#pragma once
#include <type_traits>
#include <functional>

namespace wbr::base {

	template <class _T, class... _Rests>
	class TypeTuple : public TypeTuple<_Rests...> {
	public:
		using Next = TypeTuple<_Rests...>;

		using T = _T && ;	//	�l�̌^
		using CT = const _T&&;
		using This = TypeTuple<_T, _Rests...>&&;	//	���g�̌^
		using CThis = const TypeTuple<_T, _Rests...>&&;
		using CNext = const Next&&;
		template <class A> using Prev = TypeTuple<A, _T, _Rests...>;

	private:
		//	�l
		_T v;

	public:

		//	�l��Ԃ�
		explicit operator _T& () { return v; }
		explicit operator _T && () { return (_T&&)v; }
		explicit operator _T  () const { return v; }
		explicit operator const _T& () const { return v; }
		explicit operator const _T && () const { return (_T&&)v; }


	public:
		TypeTuple() = default;

	//	�ŏ��̒l�Ǝc��̒l�ŏ�����
		TypeTuple(T v, _Rests&&... args) : first((T)v), Rest(args...) {}

	//	�ŏ��̒l��, �c��̒l�̃^�v���ŏ�����
		TypeTuple(T v, Next rest) : first((T)v), Next(rest) {}

	//	�ʂ̌^�^�v�����璊�o���ď�����
		template <class... Types>
		TypeTuple(TypeTuple<Types...>&& tuple)
			: first((T&&)tuple), Rest((TypeTuple<Types...>&&)tuple) {}


	public:
		//	�ŏ��ɕʂ̒l��ǉ��������̂�Ԃ�
		Prev getPushedFront(T v_prev) const {
			return Prev((T)v_prev, (CNext)*this);
		}

		//	�ŏ��̒l�������������̂�Ԃ�
		CNext getPopedFront(T v_prev) const {
			return *this;
		}

		//
		//	��������  forEach  ��������
		//

		//	���g�ƕʂ̃x�N�g���Ƃ�2�x�N�g���Ɋւ��āA�e�����Ɋւ��Ċ֐���K�p�������ʂ̃x�N�g����Ԃ� (const)
		template <class Func> auto forEach(Func func, CThis t) const {

			return Next::forEach(func, (CThis)t).getPushedFront(func((CT)*this, (CT)t));

		}

		//	���g�ƕʂ̃x�N�g���Ƃ�2�x�N�g���Ɋւ��āA�e�����Ɋւ��Ċ֐���K�p�������ʂ̃x�N�g����Ԃ� (not const)
		template <class Func> auto forEach(Func func, CThis t) {

			return Next::forEach(func, (CThis)t).getPushedFront(func((T)*this, (CT)t));

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



		//	���g�ƕʂ̃x�N�g���Ƃ�2�x�N�g���Ɋւ��āA�e�����Ɋւ��Ċ֐���K�p�������ʂ̃x�N�g����Ԃ� (const)
		template <class Func> auto fEach(Func func) const {

			return Next::forEach(func).getPushedFront(func((CT)*this));

		}

		//	���g�ƕʂ̃x�N�g���Ƃ�2�x�N�g���Ɋւ��āA�e�����Ɋւ��Ċ֐���K�p�������ʂ̃x�N�g����Ԃ� (not const)
		template <class Func> auto forEach(Func func) {

			return Next::forEach(func).getPushedFront(func((T)*this));

		}


		//	���g�̊e�����Ɋւ��Ċ֐���K�p���� (const)
		template <class Func> void doEach(Func func) const {

			func((CT)*this);
			if constexpr(N > 1) Next::doEach((CTVoidFunc1)func);

		}

		//	���g�̊e�����Ɋւ��Ċ֐���K�p���� (not const)
		template <class Func> void doEach(Func func) {

			func((T)*this);
			if constexpr(N > 1) Next::doEach((TVoidFunc1)func);

		}





	};

};
