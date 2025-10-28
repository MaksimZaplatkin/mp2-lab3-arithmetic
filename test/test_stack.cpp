// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_stack)
{
	ASSERT_NO_THROW(Stack <int> a);
}

TEST(Stack, can_create_stack_with_positive_lenght)
{
	ASSERT_NO_THROW(Stack <int> a(5));
}

TEST(Stack, can_not_create_stack_with_negativ_length)
{
	ASSERT_ANY_THROW(Stack <int> a(-10));
}

TEST(Stack, can_copy_stack)
{
	Stack <int> a(8);
	a.Push(4);
	a.Push(6);
	ASSERT_NO_THROW(Stack <int> b(a));
}

TEST(Stack, can_add_element)
{
	Stack <int> a(10);
	int b = 1;
	ASSERT_NO_THROW(a.Push(b));
}

TEST(Stack, can_add_element_to_full_stack)
{
	Stack <int> a(1);
	a.Push(3);
	int b = 1;
	ASSERT_NO_THROW(a.Push(b));
}

TEST(Stack, stacks_is_empty)
{
	Stack<int> a(10);
	EXPECT_TRUE(a.Is_Empty());
}


TEST(Stack, can_pop_element)
{
	Stack<int> a(10);
	int b = 3;
	a.Push(b);
	EXPECT_EQ(b, a.Pop());
}

TEST(Stack, can_top_element)
{

	Stack<int> a(10);
	int b = 1;
	int c;
	a.Push(b);
	c = a.Top();
	EXPECT_EQ(b, a.Pop());
}

TEST(Stack, can_not_pop_from_empty_stack)
{
	Stack<int> a(10);
	int b;
	ASSERT_ANY_THROW(b = a.Pop());
}

TEST(Stack, can_not_top_from_empty_stack)
{
	Stack<int> a(10);
	int b;
	ASSERT_ANY_THROW(b = a.Top());
}

TEST(Stack, can_know_number_of_elements)
{
	Stack<int> a(3);
	int b;
	for (int i = 0; i < 3; i++)
	{
		b = 3 * i + 1;
		a.Push(b);
	}
	EXPECT_EQ(3, a.How_Many_Elem());
}

TEST(Stack, can_clear_stack)
{
	Stack<int> a(3);
	int b;
	for (int i = 0; i < 3; i++)
	{
		b = 3 * i + 1;
		a.Push(b);
	}
	a.Clear();
	EXPECT_EQ(0, a.How_Many_Elem());
}

