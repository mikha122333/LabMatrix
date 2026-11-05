#include "pch.h"
#include "List_of_test.h"
#ifdef TRIANGLEMATRIX_TESTS
#include "TTriangleMatrix.h"
#include <sstream>
#include <stdexcept>

TEST(ClassTriangleMatrix, can_create_default) {
    TriangleMatrix<double> m;
    EXPECT_EQ(m.get_N(), 0);
}

TEST(ClassTriangleMatrix, can_create_with_N) {
    TriangleMatrix<double> m(3);
    EXPECT_EQ(m.get_N(), 3);
    for (size_t i = 0; i < 3; i++) {
        EXPECT_EQ(m[i].size(), i + 1);
    }
}

TEST(ClassTriangleMatrix, throw_when_create_with_zero_N) {
    EXPECT_ANY_THROW(TriangleMatrix<double> m(0));
}

TEST(ClassTriangleMatrix, can_create_with_data) {
    double** data = new double* [3];
    for (int i = 0; i < 3; i++) {
        data[i] = new double[i + 1];
        for (int j = 0; j <= i; j++) {
            data[i][j] = i * 10 + j;
        }
    }
    TriangleMatrix<double> m(3, data);
    EXPECT_EQ(m.get_N(), 3);
    EXPECT_DOUBLE_EQ(m[0][0], 0);
    EXPECT_DOUBLE_EQ(m[1][0], 10);
    EXPECT_DOUBLE_EQ(m[1][1], 11);
    EXPECT_DOUBLE_EQ(m[2][0], 20);
    EXPECT_DOUBLE_EQ(m[2][1], 21);
    EXPECT_DOUBLE_EQ(m[2][2], 22);

    for (int i = 0; i < 3; i++) delete[] data[i];
    delete[] data;
}

TEST(ClassTriangleMatrix, can_create_with_initializer_list) {
    TriangleMatrix<double> m({ {1}, {2, 3}, {4, 5, 6} });
    EXPECT_EQ(m.get_N(), 3);
    EXPECT_DOUBLE_EQ(m[0][0], 1);
    EXPECT_DOUBLE_EQ(m[1][0], 2);
    EXPECT_DOUBLE_EQ(m[1][1], 3);
    EXPECT_DOUBLE_EQ(m[2][0], 4);
    EXPECT_DOUBLE_EQ(m[2][1], 5);
    EXPECT_DOUBLE_EQ(m[2][2], 6);
}

TEST(ClassTriangleMatrix, throw_when_create_with_wrong_initializer_list) {
    EXPECT_ANY_THROW(TriangleMatrix<double> m({ {1, 2}, {3, 4} }));
}

TEST(ClassTriangleMatrix, can_create_with_copy_constructor) {
    TriangleMatrix<double> m1({ {1}, {2, 3}, {4, 5, 6} });
    TriangleMatrix<double> m2(m1);

    EXPECT_EQ(m2.get_N(), 3);
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j <= i; j++) {
            EXPECT_DOUBLE_EQ(m2[i][j], m1[i][j]);
        }
    }
    m2[2][2] = 999;
    EXPECT_DOUBLE_EQ(m1[2][2], 6);
}

TEST(ClassTriangleMatrix, can_copy_assignment) {
    TriangleMatrix<double> m1({ {1}, {2, 3}, {4, 5, 6} });
    TriangleMatrix<double> m2;
    m2 = m1;

    EXPECT_EQ(m2.get_N(), 3);
    EXPECT_DOUBLE_EQ(m2[0][0], 1);
    EXPECT_DOUBLE_EQ(m2[1][0], 2);
    EXPECT_DOUBLE_EQ(m2[1][1], 3);
    EXPECT_DOUBLE_EQ(m2[2][2], 6);

    m2[0][0] = 100;
    EXPECT_DOUBLE_EQ(m1[0][0], 1);
}

TEST(ClassTriangleMatrix, can_move_assignment) {
    TriangleMatrix<double> m1({ {1}, {2, 3}, {4, 5, 6} });
    TriangleMatrix<double> m2;
    m2 = std::move(m1);

    EXPECT_EQ(m2.get_N(), 3);
    EXPECT_DOUBLE_EQ(m2[0][0], 1);
    EXPECT_DOUBLE_EQ(m2[2][2], 6);

    EXPECT_EQ(m1.get_N(), 0);
}

TEST(ClassTriangleMatrix, can_read_elements_in_lower_triangle) {
    TriangleMatrix<double> m({ {1}, {2, 3}, {4, 5, 6} });
    EXPECT_DOUBLE_EQ(m[0][0], 1);
    EXPECT_DOUBLE_EQ(m[1][0], 2);
    EXPECT_DOUBLE_EQ(m[1][1], 3);
    EXPECT_DOUBLE_EQ(m[2][0], 4);
    EXPECT_DOUBLE_EQ(m[2][1], 5);
    EXPECT_DOUBLE_EQ(m[2][2], 6);
}

TEST(ClassTriangleMatrix, can_modify_elements_in_lower_triangle) {
    TriangleMatrix<double> m({ {1}, {2, 3}, {4, 5, 6} });
    m[2][1] = 55;
    EXPECT_DOUBLE_EQ(m[2][1], 55);
    EXPECT_DOUBLE_EQ(m[2][0], 4);
    EXPECT_DOUBLE_EQ(m[2][2], 6);
}

TEST(ClassTriangleMatrix, throws_when_accessing_upper_triangle) {
    TriangleMatrix<double> m({ {1}, {2, 3}, {4, 5, 6} });
    EXPECT_ANY_THROW(m[0][1]);
    EXPECT_ANY_THROW(m[0][2]);
    EXPECT_ANY_THROW(m[1][2]);
}

TEST(ClassTriangleMatrix, can_multiply_two_lower_triangular_2x2) {
    TriangleMatrix<double> a({ {1}, {2, 3} });
    TriangleMatrix<double> b({ {5}, {6, 7} });
    TriangleMatrix<double> c = a * b;

    EXPECT_EQ(c.get_N(), 2);
    EXPECT_DOUBLE_EQ(c[0][0], 5);
    EXPECT_DOUBLE_EQ(c[1][0], 28);
    EXPECT_DOUBLE_EQ(c[1][1], 21);
}

TEST(ClassTriangleMatrix, can_multiply_two_lower_triangular_3x3) {
    TriangleMatrix<double> a({ {1}, {2, 3}, {4, 5, 6} });
    TriangleMatrix<double> b({ {1}, {2, 3}, {4, 5, 6} });
    TriangleMatrix<double> c = a * b;

    EXPECT_EQ(c.get_N(), 3);
    EXPECT_DOUBLE_EQ(c[0][0], 1);
    EXPECT_DOUBLE_EQ(c[1][0], 8);
    EXPECT_DOUBLE_EQ(c[1][1], 9);
    EXPECT_DOUBLE_EQ(c[2][0], 38);
    EXPECT_DOUBLE_EQ(c[2][1], 45);
    EXPECT_DOUBLE_EQ(c[2][2], 36);
}

TEST(ClassTriangleMatrix, multiply_assign_lower_triangular) {
    TriangleMatrix<double> a({ {1}, {2, 3}, {4, 5, 6} });
    TriangleMatrix<double> b({ {1}, {2, 3}, {4, 5, 6} });
    a *= b;

    EXPECT_EQ(a.get_N(), 3);
    EXPECT_DOUBLE_EQ(a[0][0], 1);
    EXPECT_DOUBLE_EQ(a[1][0], 8);
    EXPECT_DOUBLE_EQ(a[1][1], 9);
    EXPECT_DOUBLE_EQ(a[2][0], 38);
    EXPECT_DOUBLE_EQ(a[2][1], 45);
    EXPECT_DOUBLE_EQ(a[2][2], 36);

    EXPECT_DOUBLE_EQ(b[2][2], 6);
}

TEST(ClassTriangleMatrix, multiply_by_identity_lower_triangular) {
    TriangleMatrix<double> a({ {1}, {2, 3}, {4, 5, 6} });
    TriangleMatrix<double> e({ {1}, {0, 1}, {0, 0, 1} });
    TriangleMatrix<double> c = a * e;

    EXPECT_DOUBLE_EQ(c[0][0], 1);
    EXPECT_DOUBLE_EQ(c[1][0], 2);
    EXPECT_DOUBLE_EQ(c[1][1], 3);
    EXPECT_DOUBLE_EQ(c[2][0], 4);
    EXPECT_DOUBLE_EQ(c[2][1], 5);
    EXPECT_DOUBLE_EQ(c[2][2], 6);
}

TEST(ClassTriangleMatrix, throw_when_multiply_incompatible_sizes) {
    TriangleMatrix<double> a({ {1}, {2, 3} });
    TriangleMatrix<double> b({ {1}, {2, 3}, {4, 5, 6} });
    EXPECT_ANY_THROW(a * b);
    EXPECT_ANY_THROW(a *= b);
}


TEST(ClassTriangleMatrix, can_output_with_operator_cout) {
    TriangleMatrix<double> m({ {1}, {2, 3}, {4, 5, 6} });
    std::stringstream out;
    out << m;
    EXPECT_EQ("{1, 0, 0}\n{2, 3, 0}\n{4, 5, 6}\n", out.str());
}

#endif