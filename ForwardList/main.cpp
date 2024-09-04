#include "ForwardList.cpp"

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

	ForwardList<int> list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)cout << i << tab;cout << endl;

	ForwardList<double> d_list = { 2.5, 3.6, 4.7, 5.8 };
	for (double i : d_list)cout << i << tab; cout << endl;

	ForwardList<std::string> s_list = { "Homework ", "is ", "done!" };
	for (std::string i : s_list)cout << i << tab;
}