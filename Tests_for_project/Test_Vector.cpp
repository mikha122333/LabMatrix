#include "pch.h"
#include "List_of_test.h"
#ifdef MEMDATA_TESTS
#include "Memdata.h"
TEST(ClassMemData, can_create_with_default_constructor) {
    MemData<double> m1;
    EXPECT_DOUBLE_EQ(m1.size(), 0);
    EXPECT_EQ(m1.capacity(), MEM_STEP - 1);
}

TEST(ClassMemData, can_create_with_constructor_by_size) {
    MemData<double> m1(2);
    EXPECT_EQ(m1.capacity(), 2 + MEM_STEP - 1);
    EXPECT_EQ(m1.size(), 2);
}

TEST(ClassMemData, can_create_with_constructor_by_initializer_list) {
    MemData<double> m1({ 1,2.2 });
    EXPECT_EQ(m1.capacity(), 2 + MEM_STEP - 1);
    EXPECT_EQ(m1.size(), 2);
}

TEST(ClassMemData, can_create_with_init_constructor) {
    double* a = new double[2];
    a[0] = 55;
    a[1] = 66;
    MemData<double> m1(2,a);
    EXPECT_EQ(m1.capacity(), 2 + MEM_STEP - 1);
    EXPECT_EQ(m1.size(), 2);
    EXPECT_DOUBLE_EQ(m1.data()[0], 55);
}

TEST(ClassMemData, can_create_with_copy_constructor) {
    MemData<double> m1({ 1,2.2 });
    MemData<double> m2(m1);
    EXPECT_EQ(m2.capacity(), 2 + MEM_STEP - 1);
    EXPECT_EQ(m2.size(), 2);
}

TEST(ClassMemData, can_create_with_move_constructor) {
    MemData<double> m1({ 1,2.2 });
    MemData<double> m2(std::move(m1));
    EXPECT_EQ(m2.capacity(), 2 + MEM_STEP - 1);
    EXPECT_EQ(m2.size(), 2);
    EXPECT_EQ(m1.capacity(), 0);
    EXPECT_EQ(m1.size(), 0);
}

TEST(ClassMemData, can_is_empty) {
    MemData<double> m1;
    EXPECT_EQ(m1.is_empty(), 1);
}

TEST(ClassMemData, can_is_full) {
    MemData<double> m1;
    EXPECT_EQ(m1.is_full(), 0);
}

TEST(ClassMemData, can_set_memory_for_empty) {
    MemData<double> m1;
    m1.set_memory(12);
    EXPECT_EQ(m1.size(), 12);
    EXPECT_EQ(m1.capacity(), 12 + MEM_STEP - 1);
}

TEST(ClassMemData, can_set_memory_for_not_empty) {
    MemData<double> m1({ 1,2,3 });
    m1.reset_memory(12);
    EXPECT_EQ(m1.size(), 12);
    EXPECT_EQ(m1.capacity(), 12 + MEM_STEP - 1);
}

TEST(ClassMemData, can_set_memory_without_reallocation) {
    MemData<double> m1({ 1,2,3 });
    m1.reset_memory(12);
    EXPECT_EQ(m1.size(), 12);
    EXPECT_EQ(m1.capacity(), 12 + MEM_STEP - 1);
}

TEST(ClassMemData, can_reset_memory_for_empty) {
    MemData<double> m1;
    m1.clear_memory();
    EXPECT_EQ(m1.size(), 0);
    EXPECT_EQ(m1.capacity(), 0);
}

TEST(ClassMemData, can_reset_memory_for_not_empty_increase) {
    MemData<double> m1({ 1,2 });
    m1.clear_memory();
    EXPECT_EQ(m1.size(), 0);
    EXPECT_EQ(m1.capacity(), 0);
}

TEST(ClassMemData, can_reset_memory_for_not_empty_decrease) {
    MemData<double> m1({ 1,2,3,4,5 });
    m1.reset_memory(3);
    EXPECT_EQ(m1.size(), 3);
    EXPECT_EQ(m1.capacity(), 17);
}

//TEST(ClassMemData, can_reset_memory_without_reallocation) {
//    //ADD_FAILURE();
//}//ресет памяти расчитан только на случаи где меняется размер, нет смысла проверки

//TEST(ClassMemData, can_reset_memory_with_shift) {
//    //ADD_FAILURE();
//}//сдвиг реализовывается в вексторе а не мемдате, тот факт что вектор полностью работает, означает что работает и это, т.к. оно там почти везде

TEST(ClassMemData, can_clear_memory_for_empty) {
    MemData<double> m1;
    m1.clear_memory();
    EXPECT_EQ(m1.capacity(), 0);
    EXPECT_EQ(m1.size(), 0);
}

TEST(ClassMemData, can_clear_memory_for_not_empty) {
    MemData<double> m1({ 2,2,2,2,2 });
    m1.clear_memory();
    EXPECT_EQ(m1.capacity(), 0);
    EXPECT_EQ(m1.size(), 0);
}

TEST(ClassMemData, can_assigment) {
    MemData<double> m1({ 2,2,2,2,2 });
    MemData<double> m2;
    m2 = m1;
    EXPECT_EQ(m2.capacity(), 5 + MEM_STEP - 1);
    EXPECT_EQ(m2.size(), 5);
}

TEST(ClassMemData, can_move_assigment) {
    MemData<double> m1({ 2,2,2,2,2 });
    MemData<double> m2;
    m2 = std::move(m1);
    EXPECT_EQ(m2.capacity(), 5 + MEM_STEP - 1);
    EXPECT_EQ(m2.size(), 5);
    EXPECT_EQ(m1.capacity(), 0);
    EXPECT_EQ(m1.size(), 0);
}

#endif
#ifdef VECTOR_TESTS
#include"Vector.h"

TEST(ClassVector, can_create_with_default_constructor) {
    Vector<double> v1;
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.capacity(), MEM_STEP - 1);
}

TEST(ClassVector, can_create_with_constructor_by_size) {
    Vector<double> v1(20);
    EXPECT_DOUBLE_EQ(v1.front(), 0);
    EXPECT_DOUBLE_EQ(v1.back(), 0);
    EXPECT_EQ(v1.size(), 20);
    EXPECT_EQ(v1.capacity(), 20 + MEM_STEP - 1);
}

TEST(ClassVector, can_create_with_constructor_by_initializer_list) {
    Vector<double> v1({ 1,2,3 });
    EXPECT_DOUBLE_EQ(v1.front(), 1);
    EXPECT_DOUBLE_EQ(v1.back(), 3);
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v1.capacity(), 3 + MEM_STEP - 1);
}

TEST(ClassVector, can_create_with_init_constructor) {
    double* s = new double[3];
    s[0] = 55;
    s[1] = 66;
    s[2] = 77;
    Vector<double> v1(3,s);
    EXPECT_DOUBLE_EQ(v1.front(), 55);
    EXPECT_DOUBLE_EQ(v1.back(), 77);
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v1.capacity(), 3 + MEM_STEP - 1);
    delete[]s;
}
TEST(ClassVector, can_create_with_copy_constructor) {
    Vector<double> v2(20);
    Vector<double> v1(v2);
    EXPECT_DOUBLE_EQ(v1.front(), 0);
    EXPECT_DOUBLE_EQ(v1.back(), 0);
    EXPECT_EQ(v1.size(), 20);
    EXPECT_EQ(v1.capacity(), 20 + MEM_STEP - 1);
}
TEST(ClassVector, can_create_with_move_constructor) {
    Vector<double> v2(20);
    Vector<double> v1(std::move(v2));
    EXPECT_DOUBLE_EQ(v1.front(), 0);
    EXPECT_DOUBLE_EQ(v1.back(), 0);
    EXPECT_EQ(v1.size(), 20);
    EXPECT_EQ(v1.capacity(), 20 + MEM_STEP - 1);
    EXPECT_EQ(v2.size(), 0);
    EXPECT_EQ(v2.capacity(), 0);
}
TEST(ClassVector, can_is_empty) {
    Vector<double> v1;
    EXPECT_EQ(v1.is_empty(), 1);
}
TEST(ClassVector, can_is_full) {
    Vector<double> v1;
    EXPECT_EQ(v1.is_full(), 0);
}
TEST(ClassVector, can_get_front_and_can_get_back) {
    Vector<double> v1({ 1,2,3 });
    EXPECT_DOUBLE_EQ(v1.front(), 1);
    EXPECT_DOUBLE_EQ(v1.back(), 3);
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v1.capacity(), 3 + MEM_STEP - 1);
}
TEST(ClassVector, can_set_front_and_can_set_back) {
    Vector<double> v1({ 1,2,3 });
    v1.back() = 4;
    v1.front() = 3;
    EXPECT_DOUBLE_EQ(v1.front(), 3);
    EXPECT_DOUBLE_EQ(v1.back(), 4);
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v1.capacity(), 3 + MEM_STEP - 1);
}
TEST(ClassVector, throw_when_try_get_front_in_empty_vector_and_throw_when_try_get_back_in_empty_vector) {
    Vector<double> v1;
    EXPECT_ANY_THROW(v1.front());
    EXPECT_ANY_THROW(v1.back());
}
TEST(ClassVector, throw_when_try_set_front_in_empty_vector_and_throw_when_try_set_back_in_empty_vector) {
    Vector<double> v1;
    EXPECT_ANY_THROW(v1.front() = 1);
    EXPECT_ANY_THROW(v1.back() = 22);
}
TEST(ClassVector, can_output_with_operator_cout) {
    Vector<double> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    std::stringstream out;
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }", out.str());
}
TEST(ClassVector, can_input_with_operator_cin) {
    Vector<double> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    std::stringstream in("9 1 2 3 4 5 6 7 8 9");
    in >> vec;

    EXPECT_EQ(9, vec.size());
    EXPECT_EQ(14, vec.capacity());
    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1);
    }
}

TEST(ClassVector, can_push_front) {
    Vector<double> v1({ 1,2 });
    v1.push_front(0);
    EXPECT_EQ(v1.capacity(), 2 + MEM_STEP - 1);
    EXPECT_EQ(v1.size(), 3);
    EXPECT_DOUBLE_EQ(v1.front(), 0);
}
TEST(ClassVector, can_push_front_in_empty_vector) {
    Vector<double> v1;
    v1.push_front(1);
    EXPECT_EQ(v1.capacity(), MEM_STEP - 1);
    EXPECT_EQ(v1.size(), 1);
    EXPECT_DOUBLE_EQ(v1.front(), 1);
    EXPECT_DOUBLE_EQ(v1.back(), 1);
}
TEST(ClassVector, can_push_front_with_reallocation) {
    Vector<double> v1;
    v1.push_front(1);
    EXPECT_EQ(v1.capacity(), MEM_STEP - 1);
    EXPECT_EQ(v1.size(), 1);
    EXPECT_DOUBLE_EQ(v1.front(), 1);
    EXPECT_DOUBLE_EQ(v1.back(), 1);
}
TEST(ClassVector, can_push_back) {
    Vector<double> v1({ 1,2 });
    v1.push_back(0);
    EXPECT_EQ(v1.capacity(), 2 + MEM_STEP - 1);
    EXPECT_EQ(v1.size(), 3);
    EXPECT_DOUBLE_EQ(v1.back(), 0);
}
TEST(ClassVector, can_push_back_in_empty_vector) {
    Vector<double> v1;
    v1.push_back(0);
    EXPECT_EQ(v1.capacity(), MEM_STEP - 1);
    EXPECT_EQ(v1.size(), 1);
    EXPECT_DOUBLE_EQ(v1.back(), 0);
}
TEST(ClassVector, can_push_back_with_reallocation) {
    Vector<double> v1;
    v1.push_back(0);
    EXPECT_EQ(v1.capacity(), MEM_STEP - 1);
    EXPECT_EQ(v1.size(), 1);
    EXPECT_DOUBLE_EQ(v1.back(), 0);
}
TEST(ClassVector, can_insert) {
    Vector<double> v1({ 1,2,3,4 });
    v1.insert(33, 2);
    EXPECT_DOUBLE_EQ(v1[2], 33);
}
TEST(ClassVector, can_insert_with_reallocation) {
    Vector<double> v1({ 1,2,3,4 });
    v1.insert(33, 2);
    EXPECT_DOUBLE_EQ(v1[2], 33);
}
TEST(ClassVector, can_insert_to_front) {
    Vector<double> v1({ 1,2,3,4 });
    v1.insert(33, 0);
    EXPECT_DOUBLE_EQ(v1.front(), 33);
}
TEST(ClassVector, throw_when_try_insert_with_wrong_position) {
    Vector<double> v1({ 1,2 });
    EXPECT_ANY_THROW(v1.insert(228, 33));
}
TEST(ClassVector, can_pop_front) {
    Vector<double> v1({ 1,2,3 });
    v1.pop_front();
    EXPECT_DOUBLE_EQ(v1[0], 2);
}
TEST(ClassVector, can_pop_front_with_reallocation) {
    Vector<double> v1({ 1,2,3,4,5,6,7 });
    v1.pop_front();
    v1.pop_front();
    v1.pop_front();
    v1.pop_front();
    EXPECT_DOUBLE_EQ(v1[0], 5);
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v1.capacity(), 21);
}
TEST(ClassVector, throw_when_try_pop_front_from_empty_vector) {
    Vector<double> v1;
    EXPECT_ANY_THROW(v1.pop_front());
}
TEST(ClassVector, can_pop_back) {
    Vector<double> v1({ 1,2,3 });
    v1.pop_back();
    EXPECT_DOUBLE_EQ(v1[1], 2);
}
TEST(ClassVector, can_pop_back_with_reallocation) {
    Vector<double> v1({ 1,2,3,4,5,6,7 });
    v1.pop_back();
    v1.pop_back();
    v1.pop_back();
    v1.pop_back();
    EXPECT_DOUBLE_EQ(v1.back(), 3);
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v1.capacity(), 21);
}
TEST(ClassVector, throw_when_try_pop_back_from_empty_vector) {
    Vector<double> v1;
    EXPECT_ANY_THROW(v1.pop_back());
}
TEST(ClassVector, can_correctly_recalc_back_in_area_of_zero) {
    Vector<double> vec;
    for (size_t i = 0; i < 15; i++) {
        vec.push_back(i + 1);
    }
    vec.pop_front();
    vec.push_back(16);
    EXPECT_EQ(15, vec.size());
    EXPECT_EQ(28, vec.capacity());
    EXPECT_DOUBLE_EQ(16.0, vec.back());
    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 2);
    }
    vec.pop_back();
    EXPECT_EQ(14, vec.size());
    EXPECT_EQ(28, vec.capacity());
    EXPECT_DOUBLE_EQ(15.0, vec.back());
    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 2);
    }
}

TEST(ClassVector, can_correctly_recalc_front_in_area_of_zero) {
    Vector<double> v1;
    EXPECT_ANY_THROW(v1.pop_back());
}
TEST(ClassVector, can_erase) {
    Vector<double> v1({ 1,2,3,4,5 });
    v1.erase(1);
    EXPECT_DOUBLE_EQ(v1[1], 3);
}
TEST(ClassVector, can_erase_front) {
    Vector<double> v1({ 1,2,3,4 });
    v1.erase(0);
    EXPECT_DOUBLE_EQ(v1.front(), 2);
}
TEST(ClassVector, can_erase_back) {
    Vector<double> v1({ 1,2,3,4 });
    v1.erase(2);
    EXPECT_EQ(v1.back(), 4);
}
TEST(ClassVector, can_erase_with_reallocation) {
    Vector<double> v1({ 1,2,3,4 });
    v1.erase(2);
    EXPECT_EQ(v1.back(), 4);
}
TEST(ClassVector, throw_when_try_erase_from_empty_vector) {
    Vector<double> v1;
    EXPECT_ANY_THROW(v1.erase(20));
}

TEST(ClassVector, throw_when_try_erase_with_wrong_position) {
    Vector<double> v1({ 1,2,3 });
    EXPECT_ANY_THROW(v1.erase(20));
}
TEST(ClassVector, combination_push_pop_insert_erase) {
    Vector<double> vec({ 3, 44, 5, 7, 8 });

    std::stringstream out;
    out << vec;
    EXPECT_EQ("{ 3, 44, 5, 7, 8 }", out.str());
    out.str("");

    vec.pop_front();
    out << vec;
    EXPECT_EQ("{ 44, 5, 7, 8 }", out.str());
    out.str("");

    for (size_t i = 0; i < 4; i++) {
        vec.push_front(3 - i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8 }", out.str());
    out.str("");

    vec.pop_back();
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7 }", out.str());
    out.str("");

    for (size_t i = 0; i < 4; i++) {
        vec.push_back(8 + i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.erase(0);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.erase(3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.insert(6, 4);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    for (size_t i = 0; i < 5; i++) {
        vec.push_back(12 + i);
    }
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    out.str("");

    vec.insert(4, 3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    out.str("");

    EXPECT_EQ(16, vec.size());
    EXPECT_EQ(19, vec.capacity());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1);
    }
}

TEST(ClassVector, can_assigment) {
    Vector<double> vec_1;
    Vector<double> vec_2;
    for (size_t i = 0; i < 4; i++) {
        vec_1.push_back(5 + i);
    }
    for (size_t i = 0; i < 4; i++) {
        vec_1.push_front(4 - i);
    }
    vec_2 = vec_1;
    EXPECT_EQ(8, vec_1.size());
    EXPECT_EQ(14, vec_1.capacity());
    EXPECT_EQ(8, vec_2.size());
    EXPECT_EQ(14, vec_2.capacity());
    for (size_t i = 0; i < vec_2.size(); i++) {
        EXPECT_EQ(vec_2[i], i + 1);
    }
    for (size_t i = 0; i < vec_2.size(); i++) {
        EXPECT_EQ(vec_1[i], i + 1);
    }
}

TEST(ClassVector, can_move_assigment) {
    Vector<double> vec_1;
    Vector<double> vec_2;
    for (size_t i = 0; i < 4; i++) {
        vec_1.push_back(5 + i);
    }
    for (size_t i = 0; i < 4; i++) {
        vec_1.push_front(4 - i);
    }
    vec_2 = std::move(vec_1);
    EXPECT_EQ(0, vec_1.size());
    EXPECT_EQ(0, vec_1.capacity());
    EXPECT_EQ(8, vec_2.size());
    EXPECT_EQ(14, vec_2.capacity());
    for (size_t i = 0; i < vec_2.size(); i++) {
        EXPECT_EQ(vec_2[i], i + 1);
    }
}
TEST(ClassVector, can_add_front_some) {
    double* d = new double[4];
    for (int i = 0; i < 4; i++) {
        d[i] = i + 1;
    }
    Vector<double> v1(4,d);
    for (int i = 0; i < 4; i++) {
        d[i] = d[i] + 1;
    }
    v1.push_front_some(d, 4);
    EXPECT_EQ(v1.size(), 8);
    EXPECT_EQ(v1.back(), 4);
    EXPECT_EQ(v1.front(), 2);
    delete[]d;
}
TEST(ClassVector, can_add_back_some) {
    double* d = new double[4];
    for (int i = 0; i < 4; i++) {
        d[i] = i + 1;
    }
    Vector<double> v1(4,d);
    for (int i = 0; i < 4; i++) {
        d[i] = d[i] + 1 + i;
    }
    v1.push_back_some(d, 4);
    EXPECT_EQ(v1.size(), 8);
    EXPECT_EQ(v1.back(), 8);
    EXPECT_EQ(v1.front(), 1);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(v1[i], i + 1);
    }
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(v1[i + 4], (i + 1) * 2);
    }
    delete[]d;
}
TEST(ClassVector, can_insert_some) {
    double* d = new double[3];
    for (int i = 0; i < 3; i++) {
        d[i] = i + 1;
    }
    Vector<double> v1(3,d);
    for (int i = 0; i < 3; i++) {
        d[i] = d[i] + 1 + i;
    }
    v1.insert_some(d, 3, 1);
    EXPECT_EQ(v1.size(), 6);
    EXPECT_EQ(v1.front(), 1);
    EXPECT_EQ(v1.back(), 3);
    for (int i = 1; i < 4; i++) {
        EXPECT_EQ(v1[i], i * 2);
    }
    delete[]d;
}
TEST(ClassVector, can_insert_some_wrong) {
    double* d = new double[3];
    for (int i = 0; i < 3; i++) {
        d[i] = 1;
    }
    Vector<double> v1;
    EXPECT_ANY_THROW(v1.insert_some(d, 3, 5));
    delete[]d;
}
TEST(ClassVector, can_erase_some) {
    Vector<double> v1({ 1,2,3,4,5,6 });
    v1.erase_some(2, 2);
    EXPECT_EQ(v1.size(), 4);
    EXPECT_EQ(v1.front(), 1);
    EXPECT_EQ(v1.back(), 6);
}
TEST(ClassVector, can_shake) {
    Vector<double> v1({ 1,2,3,4,5,6 });
    shake<double>(v1);
    EXPECT_EQ(v1.size(), 6);
    for (int i = 0; i < 6; i++) {
        // EXPECT_EQ(v1[i], i);
    }
    sort_g<double>(v1);
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(v1[i], 6 - i);
    }
}
#endif
#ifdef VECTOR_CAPACITY_TEST
#include "Vector.h"
TEST(vec_cap, is_size_equal_capacity) {
    Vector<int> v1({ 1,2,3 });
    v1.shrink_to_fit();
    EXPECT_EQ(v1.capacity(), v1.size());
    EXPECT_EQ(v1.capacity(), 3);
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(v1[i], i + 1);
    }
}
TEST(vec_cap, is_size_equal_capacity_after_add) {
    Vector<int> v1({ 1,2 });
    v1.push_back(3);
    v1.shrink_to_fit();
    EXPECT_EQ(v1.capacity(), v1.size());
    EXPECT_EQ(v1.capacity(), 3);
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(v1[i], i + 1);
    }
}
TEST(vec_cap, is_size_equal_capacity_after_pop) {
    Vector<int> v1({ 1,2,3,4 });
    v1.pop_back();
    v1.shrink_to_fit();
    EXPECT_EQ(v1.capacity(), v1.size());
    EXPECT_EQ(v1.capacity(), 3);
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(v1[i], i + 1);
    }
}
TEST(vec_cap, is_size_equal_capacity_after_using_circle_container) {
    Vector<int> v1({ 1});
    for (int i = 0; i < 5; i++) {
        v1.push_back(i + 2);
        v1.pop_front();
    }
    for (int i = 0; i < 13;i++) {
        v1.push_back(7 + i);
    }
    v1.shrink_to_fit();
    EXPECT_EQ(v1.capacity(), v1.size());
    EXPECT_EQ(v1.capacity(), 14);
    for (int i = 0; i < 14; i++) {
        EXPECT_EQ(v1[i], i + 6);
    }
}
#endif