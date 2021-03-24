#include "Allocator.h"
#include <gtest/gtest.h>


TEST(ALLOCTOR, alloc) {
    Allocator tmp;
    tmp.makeAllocator(100);
    char* arr = tmp.alloc(20);
    ASSERT_NE(arr, nullptr);
    arr[19] = 'b';
    arr[0] = 'A';
    ASSERT_NE(arr[19], 0);
    ASSERT_EQ(arr[19], 'b');
    ASSERT_EQ(arr[0], 'A');
}

TEST(ALLOCTOR, alloc1) {
    Allocator tmp;
    tmp.makeAllocator(100);
    char* arr1 = tmp.alloc(20);
    char* arr2 = tmp.alloc(80);
    ASSERT_NE(arr1, nullptr);
    ASSERT_NE(arr2, nullptr);
    arr1[19] = 'q';
    arr2[0] = 'a';
    ASSERT_NE(arr1[19], arr2[0]);
}


TEST(ALLOCTOR, alloc2) {
    Allocator tmp;
    tmp.makeAllocator(100);
    char* arr1 = tmp.alloc(20);
    char* arr2 = tmp.alloc(81);
    ASSERT_EQ(arr2, nullptr);
    tmp.reset();
    arr1 = tmp.alloc(100);
    ASSERT_NE(arr1, nullptr);
    tmp.reset();
    arr1 = tmp.alloc(101);
    ASSERT_EQ(arr1, nullptr);
}

TEST(ALLOCATOR, alloc3) {
    Allocator tmp;
    char* arr = tmp.alloc(10);
    ASSERT_EQ(arr, nullptr);
}

TEST(ALLOCATOR, alloc4) {
    Allocator tmp;
    tmp.makeAllocator(5);
    char* arr = tmp.alloc(1);
    ASSERT_NE(arr, nullptr);
    arr = tmp.alloc(1);
    ASSERT_NE(arr, nullptr);
    arr = tmp.alloc(1);
    ASSERT_NE(arr, nullptr);
    arr = tmp.alloc(1);
    ASSERT_NE(arr, nullptr);
    arr = tmp.alloc(1);
    ASSERT_NE(arr, nullptr);
    arr = tmp.alloc(1);
    ASSERT_EQ(arr, nullptr);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
