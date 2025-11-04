// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, +
// - просмотр верхнего элемента (без удаления)+
// - проверка на пустоту, +
// - получение количества элементов в стеке+
// - очистка стека+
// при вставке в полный стек должна перевыделяться память
template <typename T>
class Stack
{
	int filled;
	int size;
	T* mem;
public:
	Stack();
	Stack(int s = 100);
	Stack(const Stack<T>&);
	~Stack();
	bool Is_Empty()
	{
		if (filled == 0)
		{
			return true;
		}
		return false;
	}
	int How_Many_Elem()
	{
		return filled;
	}
	void Clear()
	{
		if (!Is_Empty())
		{
			filled = 0;
			delete[]mem;
			mem = new T[size];
		}
	}
	T Top();
	void Pop();
	void Push(T el);
};

template <typename T>
Stack<T>::Stack(int s)
{
	filled = 0;
	size = s;
	mem = new T[size];
}



template <typename T>
Stack<T>::Stack(const Stack<T>& OtS)
{
	filled = OtS.filled;
	size = OtS.size;
	mem = new T[size];
	for (int i = 0; i < filled; i++)
	{
		mem[i] = OtS.mem[i];
	}
}

template <typename T>
Stack<T>::~Stack()
{
	delete[]mem;
}

template <typename T>
T Stack<T>::Top()
{
	if (Is_Empty())
	{
		throw std::logic_error("Empty_Stack_Top_Element");
	}
	return mem[filled - 1];
}

template <typename T>
void Stack<T>::Pop()
{
	if (Is_Empty())
	{
		throw std::logic_error("Empty_Stack_Top_Element");
	}
	filled -= 1;
}

template <typename T>
void Stack<T>::Push(T el)
{
	if (filled == size)
	{
		T* tmp = new T[size * 2];
		for (int i = 0; i < filled; i++)
			tmp[i] = mem[i];
		delete[] mem;
		size = size * 2;
		mem = new T[size];
		for (int i = 0; i < filled; i++)
			mem[i] = tmp[i];
	}
	mem[filled] = el;
	filled++;
}