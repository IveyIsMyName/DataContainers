#include"ForwardList.h"

template<typename T>Element<T>::Element(T Data, Element<T>* pNext) :Data(Data), pNext(pNext)
{
	count++;
	cout << "EConstructor:\t" << this << endl;
}
template<typename T>Element<T>::~Element()
{
	count--;
	cout << "EDestructor:\t" << this << endl;
}

template<typename T>Iterator<T>::Iterator(Element<T>* Temp) :Temp(Temp) {}
template<typename T>Iterator<T>::~Iterator() {}

template<typename T>T& Iterator<T>::operator*()
{
	return Temp->Data;
}
template<typename T>Iterator<T>& Iterator<T>::operator++()
{
	Temp = Temp->pNext;
	return *this;
}
template<typename T>bool Iterator<T>::operator!=(const Iterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T>bool Iterator<T>::operator==(const Iterator& other)const
{
	return this->Temp == other.Temp;
}

template<typename T>ConstIterator<T>::ConstIterator(Element<T>* ptr) :Temp(ptr) {}
template<typename T>ConstIterator<T>::~ConstIterator() {}

template<typename T>const T& ConstIterator<T>::operator*()
{
	return Temp->Data;
}
template<typename T>ConstIterator<T>& ConstIterator<T>::operator++()
{
	Temp = Temp->pNext;
	return *this;
}
template<typename T>bool ConstIterator<T>::operator!=(const ConstIterator& other)const
{
	return Temp != other.Temp;
}
template<typename T>bool ConstIterator<T>::operator==(const ConstIterator& other)const
{
	return Temp == other.Temp;
}

//			Методы Begin и End
template<typename T>Iterator<T> ForwardList<T>::begin()
{
	return Head;
}
template<typename T>Iterator<T> ForwardList<T>::end()
{
	return nullptr;
}
template<typename T>ConstIterator<T> ForwardList<T>::begin()const
{
	return Head;
}
template<typename T>ConstIterator<T> ForwardList<T>::end()const
{
	return nullptr;
}
template<typename T>ForwardList<T>::ForwardList()
{
	Head = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>ForwardList<T>::~ForwardList()
{
	while (Head)pop_front();
	cout << "LDestructor:\t" << this << endl;
}
template<typename T>ForwardList<T>::ForwardList(const initializer_list<T>& il) :ForwardList()
{
	//initializer_list - это контейнер.
	cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template<typename T>ForwardList<T>::ForwardList(const ForwardList<T>& other) :ForwardList()
{
	/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);*/
	*this = other;   //здесь просто вызываем CopyAssignment
	cout << "LCopyConstructor: " << this << endl;
}
template<typename T>ForwardList<T>::ForwardList(ForwardList<T>&& other) noexcept :ForwardList()
{
	*this = std::move(other);
	cout << "LMoveConstructor: " << this << endl;
}
template<typename T>ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_front(Temp->Data);
	reverse();
	cout << "LCopyAssignment: " << this << endl;
	return *this;
}
template<typename T>ForwardList<T>& ForwardList<T>::operator=(ForwardList<T>&& other) noexcept
{
	if (this == &other)return *this;
	while (Head)pop_front();
	this->Head = other.Head;
	this->size = other.size;
	other.Head = nullptr;
	other.size = 0;
	return *this;
}
template<typename T>void ForwardList<T>::push_front(T Data)
{
	////1) Создаем новый элемент:
	//Element* New = new Element(Data);

	////2) Включаем новый элемент в список:
	//New->pNext = Head;

	////3) Переводим голову на новый элемент
	//Head = New;
	Head = new Element<T>(Data, Head);
	size++;
}
template<typename T>void ForwardList<T>::push_back(T Data)
{
	if (Head == nullptr) return push_front(Data);

	//1) Доходим до конца списка:
	Element<T>* Temp = Head;
	while (Temp->pNext)
	{
		Temp = Temp->pNext;
	}

	////2) Создаем новый элемент
	//Element* New = new Element(Data);

	////3) Включаем новый элемент в список:
	//Temp->pNext = New;
	Temp->pNext = new Element<T>(Data);

	size++;
}
template<typename T>void ForwardList<T>::pop_front()
{
	if (Head == nullptr)return;
	Element<T>* Temp = Head;
	Head = Head->pNext;
	delete Temp;
	size--;
}
template<typename T>void ForwardList<T>::pop_back()
{
	if (Head == nullptr || Head->pNext == nullptr) return pop_front();
	Element<T>* Temp = Head;
	while (Temp->pNext->pNext)
	{
		Temp = Temp->pNext;
	}
	delete Temp->pNext;
	Temp->pNext = nullptr;
	size--;
}
template<typename T>void ForwardList<T>::insert(T Data, int Index)
{
	if (Index > size)return;
	if (Index == 0) return push_front(Data);
	Element<T>* Temp = Head;
	for (int i = 0; i < Index - 1; i++)
	{
		Temp = Temp->pNext;
	}
	Temp->pNext = new Element<T>(Data, Temp->pNext);
	size++;
}
template<typename T>void ForwardList<T>::erase(int Index)
{
	if (Index >= size)return;
	if (Index == 0)return pop_front();
	Element<T>* Temp = Head;
	for (int i = 0; i < Index - 1; i++)
	{
		Temp = Temp->pNext;
	}
	Element<T>* Clear = Temp->pNext;
	Temp->pNext = Temp->pNext->pNext;
	delete Clear;
	size--;
}
template<typename T>void ForwardList<T>::reverse()
{
	ForwardList<T> buffer;
	while (Head)
	{
		buffer.push_front(Head->Data);
		pop_front();
	}
	this->Head = buffer.Head;
	this->size = buffer.size;
	buffer.Head = nullptr;
}
template<typename T>void ForwardList<T>::print()const
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
	for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
	cout << "Общее количество элементов списка: " << Element<T>::count << endl;
}
