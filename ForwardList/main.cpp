#include <iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;
#define tab "\t"


class Element
{
	int Data;		//значение элемента
	Element* pNext; //указатель на следующий элемент
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other)
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;   //здесь просто вызываем CopyAssignment
		cout << "LCopyConstructor: " << this << endl;
	}
	ForwardList(ForwardList&& other) 
	{
		*this = std::move(other);
		cout << "MoveConstructor: " << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		cout << "CopyAssignment: " << this << endl;
		return *this;
	}

	//					Adding elements:
	void push_front(int Data)
	{
		////1) Создаем новый элемент:
		//Element* New = new Element(Data);

		////2) Включаем новый элемент в список:
		//New->pNext = Head;

		////3) Переводим голову на новый элемент
		//Head = New;
		Head = new Element(Data, Head);
		size++;
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

		////2) Создаем новый элемент
		//Element* New = new Element(Data);

		////3) Включаем новый элемент в список:
		//Temp->pNext = New;
		Temp->pNext = new Element(Data);
	
		size++;
	}

	void pop_front()
	{
		if (Head == nullptr)return;
		Element* Temp = Head;
		Head = Head->pNext;
		delete Temp;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr || Head->pNext == nullptr) return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void insert(int Data, int Index)
	{
		if (Index > size)return;
		if (Index == 0) return push_front(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}
	void erase(int Index)
	{
		if (Index >= size)return;
		if (Index == 0)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		Element* Clear = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Clear;
		size--;
	}
	//				Methods:
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		//Element* Temp = Head;	//Temp - это итератор
		////Итератор - это указатель, при помощи которого можно перебирать
		////элементы структуры данных.
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext; //Переход на следующий элемент
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов списка: " << Element::count << endl;
	}
};

int Element::count = 0;

//#define BASE_CHECK
//#define COUNT_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
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
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();
#endif // BASE_CHECK

	int n;
	cout << "Введите количество элементов: "; cin >> n;
	
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();

	ForwardList list2 = list;		//CopyConstructor
	list2.print();
	
}