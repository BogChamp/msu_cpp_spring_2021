#include <cassert>
#include "Allocator.h"

/* Тестирует, корректно ли работает класс, доступна 
ли память по индексу и т.д */
void TEST1() {
    Allocator tmp;
    tmp.makeAllocator(100);
    char* arr = tmp.alloc(20);
    assert(arr != nullptr);
    arr[19] = 'b';
    arr[0] = 'A';
    assert(arr[19] != 'x');
    assert(arr[19] == 'b');
    assert(arr[0] == 'A');
}

/* Тестирует, можно ли использовать все аллоцированное
пространство */
void TEST2() {
    Allocator tmp;
    tmp.makeAllocator(100);
    char* arr1 = tmp.alloc(20);
    char* arr2 = tmp.alloc(80);
    assert(arr1 != nullptr);
    assert(arr2 != nullptr);
    arr1[19] = 'q';
    arr2[0] = 'a';
    assert(arr1[19] != arr2[0]);
}

/*Проверяет, правильно ли работает alloc, не выдает ли
ссылки, по которым недостаточно памяти*/
void TEST3() {
    Allocator tmp;
    tmp.makeAllocator(100);
    char* arr1 = tmp.alloc(20);
    char* arr2 = tmp.alloc(81);
    assert(arr2 == nullptr);
    tmp.reset();
    arr1 = tmp.alloc(100);
    assert(arr1 != nullptr);
    tmp.reset();
    arr1 = tmp.alloc(101);
    assert(arr1 == nullptr);
}

/*Проверка, как работает alloc до makeAllocator*/
void TEST4() {
    Allocator tmp;
    char* arr = tmp.alloc(10);
    assert(arr == nullptr);
}

/*Тестирует, как работает, если брать память побайтово, 
и нельзя ли взять 0 байт*/
void TEST5() {
    Allocator tmp;
    tmp.makeAllocator(5);
    char* arr = tmp.alloc(1);
    assert(arr != nullptr);
    arr = tmp.alloc(1);
    assert(arr != nullptr);
    arr = tmp.alloc(1);
    assert(arr != nullptr);
    arr = tmp.alloc(1);
    assert(arr != nullptr);
    arr = tmp.alloc(1);
    assert(arr != nullptr);
    arr = tmp.alloc(1);
    assert(arr == nullptr);
    tmp.reset();
    arr = tmp.alloc(0);
    assert(arr == nullptr);
}

/*Проверят, как работает makeAllocator с 0 и отрицательными
значениями, как на них работает alloc*/
void TEST6() {
    Allocator tmp1, tmp2, tmp3;
    tmp1.makeAllocator(0);
    tmp2.makeAllocator(1);
    tmp3.makeAllocator(-100);
    char* arr1 = tmp1.alloc(5);
    assert(arr1 == nullptr);
    arr1 = tmp2.alloc(2);
    assert(arr1 == nullptr);
    arr1 = tmp2.alloc(1);
    assert(arr1 != nullptr);
    arr1 = tmp3.alloc(1);
    assert(arr1 == nullptr);
}

/*Проверяет работу makeAllocator при множественном вызове*/
void TEST7() {
    Allocator tmp;
    tmp.makeAllocator(10);
    char* arr = tmp.alloc(5);
    assert(arr != nullptr);
    tmp.makeAllocator(20);
    arr = tmp.alloc(21);
    assert(arr == nullptr);
    tmp.makeAllocator(100);
    arr = tmp.alloc(21);
    assert(arr != nullptr);
    arr[20] = 's';
    assert(arr[20] == 's');
    tmp.makeAllocator(0);
    assert(tmp.alloc(10) == nullptr);
    tmp.makeAllocator(-10);
    assert(tmp.alloc(1) == nullptr);
}

/*Проверяет alloc с отрицательными значениями*/
void TEST8() {
    Allocator tmp;
    tmp.makeAllocator(10);
    assert(tmp.alloc(-10) == nullptr);
    tmp.makeAllocator(-100);
    assert(tmp.alloc(-100) == nullptr);
}

int main(int argc, char** argv) {
    TEST1();
    TEST2();
    TEST3();
    TEST4();
    TEST5();
    TEST6();
    TEST7();
    TEST8();
    return 0;
}
