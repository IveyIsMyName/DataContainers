﻿#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------\n"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
		friend class Queue;
	}*Head, *Tail;
	size_t size;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) 
		{
			cout << "CBIConstructor:\t" << this << endl;
		}
		~ConstBaseIterator() 
		{
			cout << "CBIDestructor:\t" << this << endl;
		}

		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*()const
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
			cout << "ConstItConstructor:" << this << endl;
		}
		~ConstIterator() 
		{
			cout << "ConstItDestructor:" << this << endl;
		}
		ConstIterator& operator++()	//Prefix increment
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)	//Postfix increment
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp) {}
		~ConstReverseIterator() {}

		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
	};
	class Iterator :public ConstIterator
	{
		
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) 
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp) 
		{
			cout << "RItConstructor:\t" << this << endl;
		}
		~ReverseIterator()
		{
			cout << "RItDestructor:\t" << this << endl;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	const ConstIterator begin()const
	{
		return Head;
	}
	const ConstIterator end()const
	{
		return nullptr;
	}
	const ConstReverseIterator rbegin()const
	{
		return Tail;
	}
	const ConstReverseIterator rend()const
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
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
	//				Constructors:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "Lconstructor:\t" << this << endl;
	}
	List(const initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			push_back(*it);
		}
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "LCopyConstructor:" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//			Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyAssignment:" << this << endl;
		return *this;
	}

	//			Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			/*Element* New = new Element(Data);
			New->pNext = Head;
			Head->pPrev = New;
			Head = New;*/
			Head = Head->pPrev = new Element(Data, Head);
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			/*Element* New = new Element(Data);
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail = New;*/
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		}
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index < 0 || Index > size)return;
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
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		
		size++;
	}
	//			Removing elements:
	void erase(int Index)
	{
		if (Index < 0 || Index >= size)return;
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = size - 1; i > Index; i--)Temp = Temp->pPrev;
		}
		Temp->pPrev->pNext = Temp->pNext;
		if (Temp->pNext != nullptr)Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
	}
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			Head = Head->pNext;
			delete Head->pPrev;
			Head->pPrev = nullptr;
		}
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
		}
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}
	//			Methods:
	void print()const
	{
		cout << delimiter << endl;
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail:\t" << Tail << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << delimiter << endl;
	}
	void reverse_print()const
	{
		cout << delimiter << endl;
		cout << "Tail:\t" << Tail << endl;
		for(Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head:\t" << Tail << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << delimiter << endl;
	}
	friend class Queue;
};
List operator+(const List& left, const List& right)
{
	List result;
	for (List::ConstIterator it = left.begin(); it != left.end(); ++it)result.push_back(*it);
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)result.push_back(*it);
	return result;
}
void Grow(List& list)
{
	for (List::Iterator it = list.begin(); it != list.end(); ++it)
		*it *= 10;
}
class Queue : List			//FIFO
{
public:
	void enqueue(int Data)
	{
		push_back(Data);
	}
	int dequeue()
	{
		int Data = Head->Data;
		pop_front();
		return Data;
	}
	int size_of_queue()const
	{
		return size;
	}
	bool empty()const
	{
		return List::Head == nullptr;
	}
};

//#define BASE_CHECK
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int value;
	int index;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	//list.print();
//list.reverse_print();
/*for (List::ReverseIterator it = list3.rbegin(); it != list3.rend(); ++it)
{
	cout << *it << tab;
}
cout << endl;*/

	List list1 = { 3, 5, 8, 13, 21 };
	List list2 = { 34, 55, 89, 144, 233 };
	List list3 = list1 + list2;
	//for (int i : list1)cout << i << tab; cout << endl;
	//for (int i : list2)cout << i << tab; cout << endl;
	Grow(list3);
	for (int i : list3)cout << i << tab; cout << endl;
#endif // ITERATORS_CHECK

	Queue queue;
	queue.enqueue(3);
	queue.enqueue(5);
	queue.enqueue(8);
	queue.enqueue(13);
	queue.enqueue(21);

	cout << "Size of the queue before: " << queue.size_of_queue() << endl;
	while (!queue.empty())
	{
		cout << queue.dequeue() << endl;
	}
	cout << "Size of the queue after: " << queue.size_of_queue() << endl;
	
}
