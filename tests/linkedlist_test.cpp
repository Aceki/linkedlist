#define BOOST_TEST_MODULE linkedlist_test

#include <stdexcept>

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include "linkedlist.h"

using testTypes = boost::mpl::list<char, bool, int, long>;

BOOST_AUTO_TEST_CASE_TEMPLATE(DefaultConstructor_CreatesEmptyList, T, testTypes)
{
    LinkedList<T> list;
    BOOST_TEST(list.isEmpty());
}

BOOST_AUTO_TEST_CASE(ConstructorWithInitializerList_WorksCorrectly)
{
    LinkedList<int> list = { 1, 3 };
    BOOST_TEST(list.first()->value() == 1);
    BOOST_TEST(list.last()->value() == 3);
}

BOOST_AUTO_TEST_CASE(CopyConstructor_WorksCorrectly)
{
    LinkedList<int> list0 = { 1, 2 };
    LinkedList<int> list1 = list0;
    BOOST_TEST(list1.first() != list0.first());
    BOOST_TEST(list1.first()->value() == 1);
    BOOST_TEST(list1.last() != list0.last());
    BOOST_TEST(list1.last()->value() == 2);
}

BOOST_AUTO_TEST_CASE(AddFirst_WorksCorrectly)
{
    LinkedList<int> list;
    list.addFirst(0);
    BOOST_TEST(list.first()->value() == 0);
    BOOST_TEST(list.length() == 1);
    list.addFirst(1);
    BOOST_TEST(list.first()->value() == 1);
    BOOST_TEST(list.length() == 2);
    BOOST_TEST(list.first()->next()->value() == 0);
}

BOOST_AUTO_TEST_CASE(AddLast_WorksCorrectly)
{
    LinkedList<int> list;
    list.addLast(0);
    BOOST_TEST(list.first()->value() == 0);
    BOOST_TEST(list.length() == 1);
    list.addLast(1);
    BOOST_TEST(list.first()->value() == 0);
    BOOST_TEST(list.length() == 2);
    BOOST_TEST(list.first()->next()->value() == 1);
}

BOOST_AUTO_TEST_CASE(AddBefore_WorksCorrectly)
{
    LinkedList<int> list;
    BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(AddBefore_ThrowsLogicError_WhenListIsEmpty)
{
    LinkedList<int> list = { 0 };
    auto node = list.first();
    list.clear();
    BOOST_CHECK_THROW(list.addBefore(node, 22), std::logic_error);
}

BOOST_AUTO_TEST_CASE(AddBefore_ThrowsLogicError_WhenNodePointerEqualsNullptr)
{
    LinkedList<int> list;
    BOOST_CHECK_THROW(list.addBefore(nullptr, 22), std::logic_error);
}

BOOST_AUTO_TEST_CASE(AddBefore_ThrowsLogicError_WhenListDoesNotContainNode)
{
    LinkedList<int> list0 = { 1, 2 };
    LinkedList<int> list1 = { 0 };
    BOOST_CHECK_THROW(list0.addBefore(list1.first(), 22), std::logic_error);
}

BOOST_AUTO_TEST_CASE(AddBefore_WorksCorrectly_IfNextNodeInBeginning)
{
    LinkedList<int> list = { 1, 3 };
    list.addBefore(list.find(3), 2);
    // expect { 1, 2, 3 }
    BOOST_TEST(list.length() == 3);
    BOOST_TEST(list.first()->value(), 1);
    BOOST_TEST(list.first()->next()->value(), 2);
    BOOST_TEST(list.last()->value(), 3);
}

BOOST_AUTO_TEST_CASE(AddBefore_WorksCorrectly_IfNextNodeInMiddle)
{
    LinkedList<int> list = { 1, 2, 1 };
    list.addBefore(list.findLast(1), 3);
    // expect { 1, 2, 3, 1 }
    BOOST_TEST(list.length() == 4);
    BOOST_TEST(list.first()->value(), 1);
    BOOST_TEST(list.first()->next()->value(), 2);
    BOOST_TEST(list.first()->next()->next()->value(), 3);
    BOOST_TEST(list.last()->value(), 1);
}

BOOST_AUTO_TEST_CASE(AddBefore_WorksCorrectly_IfNextNodeInEnd)
{
    LinkedList<int> list = { 1, 3 };
    list.addBefore(list.find(3), 2);
    // expect { 1, 2, 3 }
    BOOST_TEST(list.length() == 3);
    BOOST_TEST(list.first()->value() == 1);
    BOOST_TEST(list.first()->next()->value() == 2);
    BOOST_TEST(list.last()->value() == 3);
}

BOOST_AUTO_TEST_CASE(AddAfter_WorksCorrectly_IfPreviousNodeInBeginning)
{
    LinkedList<int> list = { 1, 3 };
    list.addAfter(list.find(1), 2);
    // expect { 1, 2, 3 }
    BOOST_TEST(list.length() == 3);
    BOOST_TEST(list.first()->value(), 1);
    BOOST_TEST(list.first()->next()->value(), 2);
    BOOST_TEST(list.last()->value(), 3);
}

BOOST_AUTO_TEST_CASE(AddAfter_WorksCorrectly_IfPreviousNodeInMiddle)
{
    LinkedList<int> list = { 1, 2, 1 };
    list.addAfter(list.find(2), 3);
    // expect { 1, 2, 3, 1 }
    BOOST_TEST(list.length() == 4);
    BOOST_TEST(list.first()->value(), 1);
    BOOST_TEST(list.first()->next()->value(), 2);
    BOOST_TEST(list.first()->next()->next()->value(), 3);
    BOOST_TEST(list.last()->value(), 1);
}

BOOST_AUTO_TEST_CASE(AddAfter_WorksCorrectly_IfPreviousNodeInEnd)
{
    LinkedList<int> list = { 1, 2 };
    list.addAfter(list.find(2), 3);
    // expect { 1, 2, 3 }
    BOOST_TEST(list.length() == 3);
    BOOST_TEST(list.first()->value() == 1);
    BOOST_TEST(list.first()->next()->value() == 2);
    BOOST_TEST(list.last()->value() == 3);
}

BOOST_AUTO_TEST_CASE(AddAfter_ThrowsLogicError_WhenListIsEmpty)
{
    LinkedList<int> list = { 0 };
    auto node = list.first();
    list.clear();
    BOOST_CHECK_THROW(list.addAfter(node, 22), std::logic_error);
}

BOOST_AUTO_TEST_CASE(AddAfter_ThrowsLogicError_WhenNodePointerEqualsNullptr)
{
    LinkedList<int> list;
    BOOST_CHECK_THROW(list.addAfter(nullptr, 22), std::logic_error);
}

BOOST_AUTO_TEST_CASE(AddAfter_ThrowsLogicError_WhenListDoesNotContainNode)
{
    LinkedList<int> list0 = { 1, 2 };
    LinkedList<int> list1 = { 0 };
    BOOST_CHECK_THROW(list0.addAfter(list1.first(), 22), std::logic_error);
}

BOOST_AUTO_TEST_CASE(RemoveFirst_WorksCorrectly_WhenLengthEqualsOne)
{
    LinkedList<int> list = { 0 };
    list.removeFirst();
    BOOST_TEST(list.isEmpty());
    BOOST_TEST(list.first() == nullptr);
    BOOST_TEST(list.last() == nullptr);
}

BOOST_AUTO_TEST_CASE(RemoveFirst_WorksCorrectly_WithManyElements)
{
    LinkedList<int> list = { 1, 2, 3 };
    list.removeFirst();
    BOOST_TEST(list.first()->value() == 2);
    BOOST_TEST(list.last()->value() == 3);
    list.removeFirst();
    BOOST_TEST(list.first() == list.last());
    BOOST_TEST(list.last()->next() == nullptr);
}

BOOST_AUTO_TEST_CASE(RemoveFirst_ThrowsLogicError_WhenListIsEmpty)
{
    LinkedList<int> list;
    BOOST_CHECK_THROW(list.removeFirst(), std::logic_error);
}

BOOST_AUTO_TEST_CASE(RemoveLast_WorksCorrectly_WhenLengthEqualsOne)
{
    LinkedList<int> list = { 0 };
    list.removeLast();
    BOOST_TEST(list.isEmpty());
    BOOST_TEST(list.first() == nullptr);
    BOOST_TEST(list.last() == nullptr);
}

BOOST_AUTO_TEST_CASE(RemoveLast_WorksCorrectly_WithManyElements)
{
    LinkedList<int> list = { 1, 2, 3 };
    list.removeLast();
    BOOST_TEST(list.first()->value() == 1);
    BOOST_TEST(list.last()->value() == 2);
    BOOST_TEST(list.last()->next() == nullptr);
    list.removeFirst();
    BOOST_TEST(list.first() == list.last());
    BOOST_TEST(list.last()->next() == nullptr);
}

BOOST_AUTO_TEST_CASE(RemoveLast_ThrowsLogicError_WhenListIsEmpty)
{
    LinkedList<int> list;
    BOOST_CHECK_THROW(list.removeLast(), std::logic_error);
}

BOOST_AUTO_TEST_CASE(Find_ReturnsFirstMatchNode)
{
    LinkedList<int> list = { 1, 2, 1, 3, 2 };
    BOOST_TEST(list.find(1) == list.first());
    BOOST_TEST(list.find(2) == list.first()->next());
}

BOOST_AUTO_TEST_CASE(Find_ReturnsNullptr_WhenListDoesNotContainValue)
{
    LinkedList<int> list = { 1, 2, 3 };
    BOOST_TEST(list.find(-1) == nullptr);
    BOOST_TEST(list.find(0) == nullptr);
    BOOST_TEST(list.find(4) == nullptr);
    BOOST_TEST(list.find(5) == nullptr);
}

BOOST_AUTO_TEST_CASE(FindLast_ReturnsLastMatchNode)
{
    LinkedList<int> list = { 1, 2, 1, 3, 2 };
    BOOST_TEST(list.findLast(1) == list.first()->next()->next());
    BOOST_TEST(list.findLast(2) == list.last());
}

BOOST_AUTO_TEST_CASE(FindLast_ReturnsNullptr_WhenListDoesNotContainValue)
{
    LinkedList<int> list = { 1, 2, 3 };
    BOOST_TEST(list.findLast(-1) == nullptr);
    BOOST_TEST(list.findLast(0) == nullptr);
    BOOST_TEST(list.findLast(4) == nullptr);
    BOOST_TEST(list.findLast(5) == nullptr);
}

BOOST_AUTO_TEST_CASE(Contains_ReturnsTrue_WhenListContainsValue)
{
    LinkedList<int> list = { 1, 2, 2, 3, 4 };
    BOOST_TEST(list.contains(1) == true);
    BOOST_TEST(list.contains(2) == true);
    BOOST_TEST(list.contains(3) == true);
    BOOST_TEST(list.contains(4) == true);
}

BOOST_AUTO_TEST_CASE(Contains_ReturnsFalse_WhenListDoesNotContainValue)
{
    LinkedList<int> list = { 1, 2, 2, 3, 4 };
    BOOST_TEST(list.contains(-1) == false);
    BOOST_TEST(list.contains(5) == false);
}

BOOST_AUTO_TEST_CASE(Clear_WorksCorrectly)
{
    LinkedList<int> list0 = { 1, 2, 3 };
    list0.clear();
    BOOST_TEST(list0.length() == 0);
    BOOST_TEST(list0.first() == nullptr);
    BOOST_TEST(list0.last() == nullptr);
    LinkedList<int> list1;
    list1.clear();
    BOOST_TEST(list1.length() == 0);
    BOOST_TEST(list1.first() == nullptr);
    BOOST_TEST(list1.last() == nullptr);
}

BOOST_AUTO_TEST_CASE(AssignOperator_WorksCorrectly)
{
    LinkedList<int> list0 = { 1, 2 };
    LinkedList<int> list1 = { 3, 4 };
    list0 = list1;
    BOOST_TEST(list0.length() == 2);
    BOOST_TEST(list0.first()->value() == 3);
    BOOST_TEST(list0.first() != list1.first());
    BOOST_TEST(list0.last()->value() == 4);
    BOOST_TEST(list0.last() != list1.last());
}
