#include <iostream>
using namespace std;
#define tab "\t"

class Element
{
	int Data;		//значение элемента
	Element* pNext; //указатель на следующий элемент
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		Head = nullptr;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//					Adding elements:
	void push_front(int Data)
	{
		//1) Создаем новый элемент:
		Element* New = new Element(Data);

		//2) Включаем новый элемент в список:
		New->pNext = Head;

		//3) Переводим голову на новый элемент
		Head = New;
	}

	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		
		//1) Доходим до конца списка:
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}

		//2) Создаем новый элемент
		Element* New = new Element(Data);

		//3) Включаем новый элемент в список:
		Temp->pNext = New;
	}

	void pop_front()
	{
		Element* Temp = Head;
		Head = Head->pNext;
		delete Temp;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}
	void insert(int Data, int Index)
	{
		if (Index == 0) return push_front(Data);
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}
	void erase(int Index)
	{
		if (Index == 0)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		Element* Clear = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Clear;
	}
	//				Methods:
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		Element* Temp = Head;	//Temp - это итератор
		//Итератор - это указатель, при помощи которого можно перебирать
		//элементы структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; //Переход на следующий элемент
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");

	int n;
	int index;
	cout << "Введите количество элементов: "; cin >> n;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	//Element element(5);
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.pop_front();
	//list.pop_back();
	list.insert(321, index);
	list.print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
}