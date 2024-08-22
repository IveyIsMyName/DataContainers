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
	ForwardList(const initializer_list<int>& il) :ForwardList()
	{
		//initializer_list - это контейнер.
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;   //здесь просто вызываем CopyAssignment
		cout << "LCopyConstructor: " << this << endl;
	}
	ForwardList(ForwardList&& other) noexcept :ForwardList()
	{
		*this = std::move(other);
		cout << "LMoveConstructor: " << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	class Iterator
	{
		Element* Current;
	public:
		Iterator(Element* ptr) :Current(ptr){}
		~Iterator() {}

	//			Оператор разыменования
		int& operator*()
		{
			return Current->Data;
		}

	//			Оператор инкремента
		Iterator& operator++()
		{
			Current = Current->pNext;
			return *this;
		}

	//			Операторы проверки на равенство
		bool operator!=(const Iterator& other)const
		{
			return Current != other.Current;
		}
		bool operator==(const Iterator& other)const
		{
			return Current == other.Current;
		}

	};

	class ConstIterator
	{
		Element* current;
	public:
		ConstIterator(Element* ptr) :current(ptr) {}
		~ConstIterator() {}

		//			Оператор разыменования
		const int& operator*()
		{
			return current->Data;
		}

		//			Оператор инкремента
		ConstIterator& operator++()
		{
			current = current->pNext;
			return *this;
		}

		//			Операторы проверки на равенство
		bool operator!=(const ConstIterator& other)const
		{
			return current != other.current;
		}
		bool operator==(const ConstIterator& other)const
		{
			return current == other.current;
		}

	};

	//			Методы Begin и End
	Iterator begin()
	{
		return Iterator(Head);
	}
	Iterator end()
	{
		return Iterator(nullptr);
	}

	//			Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		cout << "LCopyAssignment: " << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other) noexcept
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
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
	void reverse()
	{
		ForwardList buffer;
		while (Head)
		{
			buffer.push_front(Head->Data);
			pop_front();
		}
		this->Head = buffer.Head;
		this->size = buffer.size;
		buffer.Head = nullptr;
	}
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
//#deinfe ASSIGNMENT_CHECK
//#define RANGE_BASED_FOR_ARRAY

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

#ifdef ASSIGNMENT_CHECK
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
#endif // ASSIGNMENT_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	//Range-based for:
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

	ForwardList list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
}