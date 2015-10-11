#include "alistint.h"
#include "gtest/gtest.h"

class ArrayListTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body is empty.

	ArrayListTest() {
		// You can do set-up work for each test here.
	}

	virtual ~ArrayListTest() {
		// You can do clean-up work that doesn't throw exceptions here.		
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
		list.insert(0,1);
		list.insert(1,2);
		list.insert(2,3);
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case.
	AListInt list;
};
	
TEST_F(ArrayListTest, CopyConstructor) {
	AListInt list2(list);
	
	for (int i = 0 ; i < 3; i++) {
		EXPECT_EQ(list2.get(i), i + 1);
	}
}	

TEST_F(ArrayListTest, AssignmentOperator) {
	AListInt list2;
	list2.insert(0,4);
	list2.insert(1,5);
	list2.insert(2,6);
	
	list2 = list;
	
	for (int i = 0 ; i < 3; i++) {
		EXPECT_EQ(list2.get(i), i + 1);
	}
}

TEST_F(ArrayListTest, Size) {
	EXPECT_EQ(list.size(), 3);
}

TEST_F(ArrayListTest, EmptyFalse) {
	EXPECT_EQ(list.empty(), false);
}

TEST_F(ArrayListTest, EmptyTrue) {
	list.remove(0);
	list.remove(0);
	list.remove(0);
	EXPECT_EQ(list.empty(), true);
}

TEST_F(ArrayListTest, InsertMany) {
	for (int i = 3; i <6; i++) {
		list.insert(i, i+1);
	}
	
	for (int i = 0 ; i < 6; i++) {
		EXPECT_EQ(list.get(i), i + 1);
	}
}

TEST_F(ArrayListTest, InsertBad) {
	list.insert(50, 5);
	
	for (int i = 0 ; i < 3; i++) {
		EXPECT_EQ(list.get(i), i + 1);
	}
}

TEST_F(ArrayListTest, Remove) {
	list.remove(0);
	list.remove(0);
	
	EXPECT_EQ(list.get(0), 3);
}

TEST_F(ArrayListTest, RemoveBad) {
	list.remove(50);
	
	for (int i = 0 ; i < 3; i++) {
		EXPECT_EQ(list.get(i), i + 1);
	}
}

TEST_F(ArrayListTest, Set) {
	for (int i = 0; i < 3; i++) {
		list.set(i, i-1);
	}
	for (int i = 0 ; i < 3; i++) {
		EXPECT_EQ(list.get(i), i-1);
	}
}

TEST_F(ArrayListTest, SetBad) {
	list.set(50, 6);
	for (int i = 0 ; i < 3; i++) {
		EXPECT_EQ(list.get(i), i + 1);
	}
}
	
TEST_F(ArrayListTest, GetNominal) {
	for (int i = 0 ; i < 3; i++) {
		EXPECT_EQ(list.get(i), i + 1);
	}
}

TEST_F(ArrayListTest, GetNotNominal) {
	EXPECT_EQ(list.get(4), 1);
}

TEST_F(ArrayListTest, PlusSign) {
	AListInt list2, list3;
	list2.insert(0,4);
	list2.insert(1,5);
	list2.insert(2,6);
	
	list3 = list + list2;
	
	for (int i = 0 ; i < list3.size(); i++) {
		EXPECT_EQ(list3.get(i), i + 1);
	}
}

TEST_F(ArrayListTest, Bracket) {
	for (int i = 0 ; i < 3; i++) {
		EXPECT_EQ(list.get(i), list[i]);
	}
}