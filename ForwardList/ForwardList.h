#pragma once
#include <iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;
#define tab "\t"

template<typename T> class ForwardList;
template<typename T> class Iterator;
template<typename T> class ConstIterator;

template <typename T>class Element
{
	T Data;		//значение элемента
	Element<T>* pNext; //указатель на следующий элемент
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr);
	
	~Element();
	
	friend class ForwardList<T>;
	friend class Iterator<T>;
	friend class ConstIterator<T>;
};

template<typename T> int Element<T>::count = 0;

template <typename T>class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp);
	~Iterator();

	//			Оператор разыменования
	T& operator*();

	//			Оператор инкремента
	Iterator& operator++();

	//			Операторы проверки на равенство
	bool operator!=(const Iterator& other)const;
	bool operator==(const Iterator& other)const;
};

template <typename T>class ConstIterator
{
	Element<T>* Temp;
public:
	ConstIterator(Element<T>* ptr);
	~ConstIterator();

	//			Оператор разыменования
	const T& operator*();

	//			Оператор инкремента
	ConstIterator& operator++();

	//			Операторы проверки на равенство
	bool operator!=(const ConstIterator& other)const;
	bool operator==(const ConstIterator& other)const;
};

template <typename T>class ForwardList
{
	Element<T>* Head;
	unsigned int size;
public:
	//			Методы Begin и End
	Iterator<T> begin();
	Iterator<T> end();
	ConstIterator<T> begin()const;
	ConstIterator<T> end()const;
	ForwardList();
	~ForwardList();
	ForwardList(const initializer_list<T>& il);
	ForwardList(const ForwardList<T>& other);
	ForwardList(ForwardList<T>&& other) noexcept;

	//			Operators:
	ForwardList<T>& operator=(const ForwardList<T>& other);
	ForwardList<T>& operator=(ForwardList<T>&& other) noexcept;

	//					Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void pop_front();
	void pop_back();
	void insert(T Data, int Index);
	void erase(int Index);
	//				Methods:
	void reverse();
	void print()const;
};