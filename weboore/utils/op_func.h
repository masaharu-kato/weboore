#pragma once
namespace wbr::base {

	struct OpFunc {};
	
#define __generateOpFuncSingle(_name_, _lop_, _rop_, _const_)\
	struct OpFunc ## _name_ : public OpFunc {\
		template <class A, class B> static auto calc(_const_ A&& a) {\
			return _lop_ a _rop_;\
		}\
		\
		template <class A, class B> static auto calc(_const_ A& a) {\
			return _lop_ a _rop_;\
		}\
	};


#define __generateOpFuncDouble(_name_, _lop_, _rop_, _const_)\
	struct OpFunc ## _name_ : public OpFunc {\
		template <class A, class B> static auto calc(_const_ A&& a, _const_ B&& b) {\
			return a _lop_ (_const_ B&&)b _rop_;\
		}\
		\
		template <class A, class B> static auto calc(_const_ A& a, _const_ B& b) {\
			return a _lop_ b _rop_;\
		}\
	};

#define __COMMA__ ,
#define __not_const__

#define __generateOpFuncDoubleWithSet(_name_, _op_)\
	__generateOpFuncDouble(_name_, _op_, , const)\
	__generateOpFuncDouble(Set ## _name_, _op_ ## =,,)

	__generateOpFuncDouble(Set, =, ,);

	__generateOpFuncDoubleWithSet(Add		, + );
	__generateOpFuncDoubleWithSet(Sub		, - );
	__generateOpFuncDoubleWithSet(Mul		, * );
	__generateOpFuncDoubleWithSet(Div		, / );
	__generateOpFuncDoubleWithSet(Mod		, % );
	__generateOpFuncDoubleWithSet(BitAnd	, & );
	__generateOpFuncDoubleWithSet(BitOR		, | );
	__generateOpFuncDoubleWithSet(BitXOR	, ^ );
	__generateOpFuncDoubleWithSet(LShift	, <<);
	__generateOpFuncDoubleWithSet(RShift	, >>);

	__generateOpFuncDouble(BoolAnd	, &&,   , const);
	__generateOpFuncDouble(BoolOR	, ||,   , const);
	__generateOpFuncDouble(Less		, < ,   , const);
	__generateOpFuncDouble(More		, > ,   , const);
	__generateOpFuncDouble(LessEq	, <=,   , const);
	__generateOpFuncDouble(MoreEq	, >=,   , const);
	__generateOpFuncDouble(Equal	, ==,   , const);
	__generateOpFuncDouble(NotEq	, !=,   , const);
	__generateOpFuncDouble(Comma	, __COMMA__,   , const);
	__generateOpFuncDouble(CSuffix	, [ , ] , const);
	__generateOpFuncDouble(Suffix	, [ , ] , __not_const__);
	
	__generateOpFuncSingle(Plus		, + ,   , const);
	__generateOpFuncSingle(Minus	, - ,   , const);
	__generateOpFuncSingle(Deref	, * ,   , const);
	__generateOpFuncSingle(Ref		, & ,   , const);
	__generateOpFuncSingle(BitFlip	, ~ ,   , const);
	__generateOpFuncSingle(BoolNot	, ! ,   , const);
	
	__generateOpFuncSingle(RInc		,   , ++, __not_const__);
	__generateOpFuncSingle(RDec		,   , --, __not_const__);
	__generateOpFuncSingle(LInc		, ++,   , __not_const__);
	__generateOpFuncSingle(LDec		, --,   , __not_const__);



}