#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab  "\t"

class Element
{
	int Data;
	Element* pPrev;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor;\t" << this << endl;
	}
	friend class List_2;
};

class List_2
{
	Element* Head;
	Element* Tail;
public:
	List_2() :Head(nullptr), Tail(nullptr)
	{
		cout << "Lconstructor:\t" << this << endl;
	}
	~List_2()
	{
		cout << "LDestrucotr:\t" << this << endl;
	}

	// Adding element
	void add(int Data)
	{
		Element* New = new Element(Data); // Создаем новый элемент.
		Head = New;
	}

	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		
		if (Head != nullptr)
		{
			New->pNext = New->pPrev;
		}
	}

	// Methods
	void print()
	{
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << tab << Temp->pPrev << endl;
			Temp = Temp->pNext;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	List_2 list;
	//list.add(1024);
	//list.print();

	int n;
	cout << "Введите размер списка: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
}