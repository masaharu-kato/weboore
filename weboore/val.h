#pragma once
namespace wbr::base {


	class ValEntity {



	};

	class Val {
	private:
		ValEntity* value;

	public:
		Val(ValEntity* value) : value(value) {}

		Val operator + (const Val&) const;
		Val operator - (const Val&) const;
		Val operator * (const Val&) const;
		Val operator / (const Val&) const;
		Val operator % (const Val&) const;
		Val operator & (const Val&) const;
		Val operator | (const Val&) const;
		Val operator ^ (const Val&) const;
		Val operator <<(const Val&) const;
		Val operator >>(const Val&) const;

		Val operator &&(const Val&) const;
		Val operator ||(const Val&) const;
		Val operator < (const Val&) const;
		Val operator > (const Val&) const;
		Val operator <=(const Val&) const;
		Val operator >=(const Val&) const;
		Val operator ==(const Val&) const;
		Val operator !=(const Val&) const;
		Val operator , (const Val&) const;
		Val operator [](const Val&) const;
		Val operator [](const Val&);
		
		Val operator + () const;
		Val operator - () const;
		Val operator * () const;
		Val operator & () const;
		Val operator ~ () const;
		Val operator ! () const;
		
		Val operator ++() const;
		Val operator --() const;
		Val operator ++(int) const;
		Val operator --(int) const;
		
		Val operator += (const Val&);
		Val operator -= (const Val&);
		Val operator *= (const Val&);
		Val operator /= (const Val&);
		Val operator %= (const Val&);
		Val operator &= (const Val&);
		Val operator |= (const Val&);
		Val operator ^= (const Val&);
		Val operator <<=(const Val&);
		Val operator >>=(const Val&);



	};

	template <class T> class TypedVal : public ValEntity {


	};


	template <class T> class Var : public TypedVal<T> {


	};

}
