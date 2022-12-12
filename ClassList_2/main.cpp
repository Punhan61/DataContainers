#include<iostream>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------\n"

template<class T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List<T>;
	}*Head, * Tail;
	unsigned int size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "CBIConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstBaseIterator()
		{
#ifdef DEBUG
			cout << "CBIDestructor:\t" << this << endl;
#endif // DEBUG
		}
		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const T& operator*()const
		{
			return Temp->Data;
		}
	};

public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
		}
		ConstIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
	};

	class ConstReversIterator :public ConstBaseIterator
	{
	public:
		ConstReversIterator(Element* Temp) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstReversIterator()
		{
#ifdef DEBUG
			cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG
		}

		ConstReversIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReversIterator& operator++(int)
		{
			ConstReversIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
		ConstReversIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstReversIterator& operator--(int)
		{
			ConstReversIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
	};
	class Iterator :public ConstIterator
	{
	public:
	     Iterator(Element* Temp):ConstIterator(Temp){}
		~Iterator(){}
		
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	class ReversIterator :public ConstReversIterator
	{
	public:
		ReversIterator(Element* Temp) :ConstReversIterator(Temp) {}
		~ReversIterator() {}

		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	ConstIterator begin()const
	{
		return Head;
	}
	ConstIterator end()const
	{
		return nullptr;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ConstReversIterator rbegin()const
	{
		return Tail;
	}
	ConstReversIterator rend()const
	{
		return nullptr;
	}
	ReversIterator rbegin()
	{
		return Tail;
	}
	ReversIterator rend()
	{
		return nullptr;
	}

	///////////   Constructors  /////////////
	
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<T>& il) :List()
	{
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List<T>& other) :List()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;
		cout << "CopyConstructor:" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	/////////    Operators:   //////////////

	List<T>& operator=(const List<T>& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	///////		Adding Elements:     //////////////

	void push_front(T Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(int Index, T Data)
	{
		if (Index > size)
		{
			cout << "Error: Out of range" << endl;
			return;
		}
		if (Index == 0)return push_front(Data);
		if (Index == size)return push_back(Data);
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		/*Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;*/

		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);

		size++;

	}

	/////////////	Removing Elements:   ///////////////

	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}

	void erase(int Index)
	{
		if (Index > size)
		{
			cout << "Error: Out of range" << endl;
			return;
		}
		if (Index == 0)return pop_front();
		if (Index == size)return pop_back();
		Element* Temp = Head;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
	}

	//				Methods:
	void print()const
	{
		cout << "Голова списка: " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Хвост списка: " << Tail << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		cout << "Хвост списка: " << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Голова списка: " << Head << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	
};
template<class T>
List<T> operator+(const List<T>& left,const List<T>& right)
{
	List<T> cat = left;
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		cat.push_back(*it);
		//*it *= 100;
	}
	return cat;
}
template<class T>
void FillRand(List<T>& list)
{
	for (typename List<T>::Iterator it = list.begin(); it != list.end(); it++)
	{
		*it = rand();
	}
}

//#define BASE_CHECK
//#define CONSTRUCTORS_CHECK
//#define ITERATORS_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	list.reverse_print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.reverse_print();

#endif // BASE_CHECK

#ifdef CONSTRUCTORS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	list.print();
	list.reverse_print();
	cout << delimiter << endl;

	//List list2 = list;		//CopyConstructor
	List list2;
	list2 = list;			//CopyAssignment
	list2.print();
	list2.reverse_print();
#endif // CONSTRUCTORS_CHECK

#ifdef ITERATORS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (List::ConstReversIterator rit = list.rbegin(); rit != list.rend(); rit++)
	{
		cout << *rit << tab;
	}
	cout << endl;

	List list2 = { 34, 55, 89 };
	List list3 = list + list2;
	for (int i : list)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
#endif // ITERATORS_CHECK

	List<int> i_list = { 3,5,8,13,21 };
	i_list.print();
	i_list.reverse_print();

	List<int> i_list_2 = { 34,55,89 };
	List<int> I_list_3 = i_list + i_list_2;
	for (int i : I_list_3)cout << i << tab; cout << endl;

	List<double> d_list_1 = { 2.7,3.14,5.3,8.9 };
	d_list_1.print();
	d_list_1.reverse_print();

	List<double> d_list_2 = { 25.4,88.97,98.2 };
	List<double> d_list_3 = d_list_1 + d_list_2;
	for (double i : d_list_3)cout << i << tab; cout << endl;

	List<std::string>s_list_1 = { "Хорошо","живет","на","свете","Винни-Пух" };
	List<std::string>s_list_2 = { "Вот","и","сказочки","конец"};
	List<std::string>s_list_3 = s_list_1 + s_list_2;
	for (std::string i : s_list_3)cout << i << tab; cout << endl;
	for (List<std::string>::ReversIterator it = s_list_3.rbegin(); it != s_list_3.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
}