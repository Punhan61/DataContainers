#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------\n"

class Tree
{
	class Element
	{
		int Data;    // значения элемента
		Element* pLeft, *pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pright = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "Econstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "Edestructor:\t" << this << endl;
		}
		friend class Tree;
	} *Root;
public:
	Element* getRoot()const
	{
		return Root;
	}

	Tree() :Root(nullptr)
	{
		cout << "Tconstructor:\t" << this << endl;
	}
	~Tree()
	{
		cout << "Tdestructor:\t" << this << endl;
	}

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите количество элементов: " << endl; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << endl;
}