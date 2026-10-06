#include "pch.h"
#include "List_of_test.h"
#ifdef MATHVECTOR_TESTS
#include "TMathVector.h"
#include <sstream>
#include <stdexcept>

TEST(ClassMathVector, can_create_with_default_constructor) {
    MathVector<double> m1;
    EXPECT_EQ(m1.size(), 0);
}

TEST(ClassMathVector, can_create_with_constructor_by_size) {
    MathVector<double> m1(3);
    EXPECT_EQ(m1.size(), 3);
    EXPECT_DOUBLE_EQ(m1[0], 0);
    EXPECT_DOUBLE_EQ(m1[1], 0);
    EXPECT_DOUBLE_EQ(m1[2], 0);
}

TEST(ClassMathVector, can_create_with_constructor_by_initializer_list) {
    MathVector<double> m1({ 1, 2, 3 });
    EXPECT_EQ(m1.size(), 3);
    EXPECT_DOUBLE_EQ(m1[0], 1);
    EXPECT_DOUBLE_EQ(m1[1], 2);
    EXPECT_DOUBLE_EQ(m1[2], 3);
}

TEST(ClassMathVector, can_create_with_init_constructor) {
    double a[3] = { 55, 66, 77 };
    MathVector<double> m1(3, a);
    EXPECT_EQ(m1.size(), 3);
    EXPECT_DOUBLE_EQ(m1[0], 55);
    EXPECT_DOUBLE_EQ(m1[1], 66);
    EXPECT_DOUBLE_EQ(m1[2], 77);
}

TEST(ClassMathVector, can_create_with_copy_constructor) {
    MathVector<double> m1({ 1, 2, 3 });
    MathVector<double> m2(m1);
    EXPECT_EQ(m2.size(), 3);
    for (size_t i = 0; i < m2.size(); i++) {
        EXPECT_DOUBLE_EQ(m2[i], m1[i]);
    }
}

TEST(ClassMathVector, can_assigment) {
    MathVector<double> m1({ 1, 2, 3 });
    MathVector<double> m2;
    m2 = m1;
    EXPECT_EQ(m2.size(), 3);
    for (size_t i = 0; i < m2.size(); i++) {
        EXPECT_DOUBLE_EQ(m2[i], i + 1);
    }
    for (size_t i = 0; i < m1.size(); i++) {
        EXPECT_DOUBLE_EQ(m1[i], i + 1);
    }
}

TEST(ClassMathVector, can_move_assigment) {
    MathVector<double> m1({ 1, 2, 3 });
    MathVector<double> m2;
    m2 = std::move(m1);
    EXPECT_EQ(m2.size(), 3);
    for (size_t i = 0; i < m2.size(); i++) {
        EXPECT_DOUBLE_EQ(m2[i], i + 1);
    }
    EXPECT_EQ(m1.size(), 0);
}

TEST(ClassMathVector, can_add_vectors_with_operator_plus) {
    MathVector<double> a({ 1, 2, 3 });
    MathVector<double> b({ 4, 5, 6 });
    MathVector<double> c = a + b;

    EXPECT_EQ(c.size(), 3);
    EXPECT_DOUBLE_EQ(c[0], 5);
    EXPECT_DOUBLE_EQ(c[1], 7);
    EXPECT_DOUBLE_EQ(c[2], 9);

    EXPECT_DOUBLE_EQ(a[0], 1);
    EXPECT_DOUBLE_EQ(b[0], 4);
}

TEST(ClassMathVector, can_subtract_vectors_with_operator_minus) {
    MathVector<double> a({ 4, 5, 6 });
    MathVector<double> b({ 1, 2, 3 });
    MathVector<double> c = a - b;

    EXPECT_EQ(c.size(), 3);
    EXPECT_DOUBLE_EQ(c[0], 3);
    EXPECT_DOUBLE_EQ(c[1], 3);
    EXPECT_DOUBLE_EQ(c[2], 3);
}

TEST(ClassMathVector, can_plus_equal) {
    MathVector<double> a({ 1, 2, 3 });
    MathVector<double> b({ 4, 5, 6 });
    a += b;

    EXPECT_EQ(a.size(), 3);
    EXPECT_DOUBLE_EQ(a[0], 5);
    EXPECT_DOUBLE_EQ(a[1], 7);
    EXPECT_DOUBLE_EQ(a[2], 9);

    EXPECT_DOUBLE_EQ(b[0], 4);
    EXPECT_DOUBLE_EQ(b[1], 5);
    EXPECT_DOUBLE_EQ(b[2], 6);
}

TEST(ClassMathVector, can_minus_equal) {
    MathVector<double> a({ 4, 5, 6 });
    MathVector<double> b({ 1, 2, 3 });
    a -= b;

    EXPECT_EQ(a.size(), 3);
    EXPECT_DOUBLE_EQ(a[0], 3);
    EXPECT_DOUBLE_EQ(a[1], 3);
    EXPECT_DOUBLE_EQ(a[2], 3);
}

TEST(ClassMathVector, throw_when_add_vectors_with_different_sizes) {
    MathVector<double> a({ 1, 2 });
    MathVector<double> b({ 1, 2, 3 });

    EXPECT_ANY_THROW(a += b);
    EXPECT_ANY_THROW(a + b);
}

TEST(ClassMathVector, throw_when_subtract_vectors_with_different_sizes) {
    MathVector<double> a({ 1, 2 });
    MathVector<double> b({ 1, 2, 3 });

    EXPECT_ANY_THROW(a -= b);
    EXPECT_ANY_THROW(a - b);
}

TEST(ClassMathVector, can_multiply_by_scalar_with_operator_multiply) {
    MathVector<double> a({ 1, 2, 3 });
    MathVector<double> b = a * 2.5;

    EXPECT_EQ(b.size(), 3);
    EXPECT_DOUBLE_EQ(b[0], 2.5);
    EXPECT_DOUBLE_EQ(b[1], 5.0);
    EXPECT_DOUBLE_EQ(b[2], 7.5);

    EXPECT_DOUBLE_EQ(a[0], 1);
    EXPECT_DOUBLE_EQ(a[1], 2);
    EXPECT_DOUBLE_EQ(a[2], 3);
}

TEST(ClassMathVector, can_multiply_assign_by_scalar) {
    MathVector<double> a({ 1, 2, 3 });
    a *= 2.0;

    EXPECT_EQ(a.size(), 3);
    EXPECT_DOUBLE_EQ(a[0], 2);
    EXPECT_DOUBLE_EQ(a[1], 4);
    EXPECT_DOUBLE_EQ(a[2], 6);
}

TEST(ClassMathVector, can_dot_product) {
    MathVector<double> a({ 1, 2, 3 });
    MathVector<double> b({ 4, 5, 6 });

    double res = a * b;
    EXPECT_DOUBLE_EQ(res, 32.0);
}

TEST(ClassMathVector, throw_when_dot_product_with_different_sizes) {
    MathVector<double> a({ 1, 2 });
    MathVector<double> b({ 1, 2, 3 });

    EXPECT_ANY_THROW(a * b);
}

TEST(ClassMathVector, can_output_with_operator_cout) {
    MathVector<double> m({ 1, 2, 3 });
    std::stringstream out;
    out << m;
    EXPECT_EQ("{1, 2, 3}", out.str());
}

TEST(ClassMathVector, can_output_empty_vector) {
    MathVector<double> m;
    std::stringstream out;
    out << m;
    EXPECT_EQ("{}", out.str());
}

TEST(ClassMathVector, can_input_with_operator_cin) {
    MathVector<double> m;
    std::stringstream in("9 1 2 3 4 5 6 7 8 9");
    in >> m;

    EXPECT_EQ(m.size(), 9);
    for (size_t i = 0; i < m.size(); i++) {
        EXPECT_DOUBLE_EQ(m[i], i + 1);
    }
}

#endif