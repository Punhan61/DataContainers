#pragma once
#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------\n"


///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////                    CLASS_DECLARETION
//////////////////////////////////////////////////////////////////////////////////////////

template<class T>class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List<T>;
	}*Head, * Tail;
	unsigned int size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp);
		~ConstBaseIterator();
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		const T& operator*()const;
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};

	class ConstReversIterator :public ConstBaseIterator
	{
	public:
		ConstReversIterator(Element* Temp);
		~ConstReversIterator();
		ConstReversIterator& operator++();
		ConstReversIterator operator++(int);
		ConstReversIterator& operator--();
		ConstReversIterator operator--(int);
	};

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp) {}
		~Iterator() {}

		T& operator*();
	};

	class ReversIterator :public ConstReversIterator
	{
	public:
		ReversIterator(Element* Temp) :ConstReversIterator(Temp) {}
		~ReversIterator() {}
		T& operator*();
	};
	ConstIterator begin()const;
	ConstIterator end()const;
	Iterator begin();
	Iterator end();

	ConstReversIterator rbegin()const;
	ConstReversIterator rend()const;
	ReversIterator rbegin();
	ReversIterator rend();

	///////////   Constructors  /////////////
	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();

	/////////    Operators:   //////////////
	List<T>& operator=(const List<T>& other);

	///////		Adding Elements:     //////////////
	void push_front(T Data);
	void push_back(T Data);
	void insert(int Index, T Data);

	/////////////	Removing Elements:   ///////////////
	void pop_front();
	void pop_back();
	void erase(int Index);

	//				Methods:
	void print()const;
	void reverse_print()const;
};

template<class T>
List<T> operator+(const List<T>& left, const List<T>& right);
/////////////////////                    CLASS_DECLARETION END
///////////////////////////////////////////////////////////////////////////////////