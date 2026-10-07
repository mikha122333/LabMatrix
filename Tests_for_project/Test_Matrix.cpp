#include"pch.h"
#include"List_of_test.h"
#ifdef MATRIX_TEST
#include "TMatrix.h"
#include <sstream>
#include <stdexcept>


TEST(ClassMatrix, can_create_with_default_constructor) {
    Matrix<double> m;
    EXPECT_EQ(m.get_N(), 0);
    EXPECT_EQ(m.get_M(), 0);
    EXPECT_EQ(m.size(), 0);
}

TEST(ClassMatrix, can_create_with_size_constructor) {
    Matrix<double> m(2, 3);
    EXPECT_EQ(m.get_N(), 2);
    EXPECT_EQ(m.get_M(), 3);
    EXPECT_EQ(m.size(), 2);
    for (size_t i = 0; i < m.get_N(); i++) {
        EXPECT_EQ(m[i].size(), 3);
        for (size_t j = 0; j < m.get_M(); j++) {
            EXPECT_DOUBLE_EQ(m[i][j], 0.0);
        }
    }
}

TEST(ClassMatrix, throw_when_create_with_zero_N) {
    EXPECT_ANY_THROW(Matrix<double> m(0, 3));
}

TEST(ClassMatrix, throw_when_create_with_zero_M) {
    EXPECT_ANY_THROW(Matrix<double> m(3, 0));
}

TEST(ClassMatrix, can_create_with_data_constructor) {
    double** data = new double* [2];
    for (int i = 0; i < 2; i++) {
        data[i] = new double[3];
        for (int j = 0; j < 3; j++) {
            data[i][j] = i * 3 + j + 1;
        }
    }
    Matrix<double> m(2, 3, data);
    EXPECT_EQ(m.get_N(), 2);
    EXPECT_EQ(m.get_M(), 3);
    EXPECT_DOUBLE_EQ(m[0][0], 1);
    EXPECT_DOUBLE_EQ(m[0][1], 2);
    EXPECT_DOUBLE_EQ(m[0][2], 3);
    EXPECT_DOUBLE_EQ(m[1][0], 4);
    EXPECT_DOUBLE_EQ(m[1][1], 5);
    EXPECT_DOUBLE_EQ(m[1][2], 6);

    for (int i = 0; i < 2; i++) delete[] data[i];
    delete[] data;
}

TEST(ClassMatrix, can_create_with_initializer_list) {
    Matrix<double> m({ {1, 2, 3}, {4, 5, 6} });
    EXPECT_EQ(m.get_N(), 2);
    EXPECT_EQ(m.get_M(), 3);
    EXPECT_EQ(m.size(), 2);
    EXPECT_DOUBLE_EQ(m[0][0], 1);
    EXPECT_DOUBLE_EQ(m[0][2], 3);
    EXPECT_DOUBLE_EQ(m[1][0], 4);
    EXPECT_DOUBLE_EQ(m[1][2], 6);
}

TEST(ClassMatrix, can_create_with_copy_constructor) {
    Matrix<double> m1({ {1, 2, 3}, {4, 5, 6} });
    Matrix<double> m2(m1);
    EXPECT_EQ(m2.get_N(), 2);
    EXPECT_EQ(m2.get_M(), 3);
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 3; j++) {
            EXPECT_DOUBLE_EQ(m2[i][j], m1[i][j]);
        }
    }
    m2[0][0] = 999;
    EXPECT_DOUBLE_EQ(m1[0][0], 1);
}

TEST(ClassMatrix, can_copy_assignment) {
    Matrix<double> m1({ {1, 2}, {3, 4} });
    Matrix<double> m2;
    m2 = m1;
    EXPECT_EQ(m2.get_N(), 2);
    EXPECT_EQ(m2.get_M(), 2);
    EXPECT_DOUBLE_EQ(m2[0][0], 1);
    EXPECT_DOUBLE_EQ(m2[0][1], 2);
    EXPECT_DOUBLE_EQ(m2[1][0], 3);
    EXPECT_DOUBLE_EQ(m2[1][1], 4);

    EXPECT_DOUBLE_EQ(m1[0][0], 1);
    m2[0][0] = 100;
    EXPECT_DOUBLE_EQ(m1[0][0], 1);
}

TEST(ClassMatrix, can_move_assignment) {
    Matrix<double> m1({ {1, 2}, {3, 4} });
    Matrix<double> m2;
    m2 = std::move(m1);

    EXPECT_EQ(m2.get_N(), 2);
    EXPECT_EQ(m2.get_M(), 2);
    EXPECT_DOUBLE_EQ(m2[0][0], 1);
    EXPECT_DOUBLE_EQ(m2[1][1], 4);

    EXPECT_EQ(m1.get_N(), 0);
    EXPECT_EQ(m1.get_M(), 0);
    EXPECT_EQ(m1.size(), 0);
}

TEST(ClassMatrix, can_multiply_square_matrices) {
    Matrix<double> a({ {1, 2}, {3, 4} });
    Matrix<double> b({ {5, 6}, {7, 8} });
    Matrix<double> c = a * b;

    EXPECT_EQ(c.get_N(), 2);
    EXPECT_EQ(c.get_M(), 2);
    EXPECT_DOUBLE_EQ(c[0][0], 19);
    EXPECT_DOUBLE_EQ(c[0][1], 22);
    EXPECT_DOUBLE_EQ(c[1][0], 43);
    EXPECT_DOUBLE_EQ(c[1][1], 50);

    EXPECT_DOUBLE_EQ(a[0][0], 1);
    EXPECT_DOUBLE_EQ(b[0][0], 5);
}

TEST(ClassMatrix, can_multiply_rectangular_matrices) {
    Matrix<double> a({ {1, 2, 3}, {4, 5, 6} });       
    Matrix<double> b({ {7, 8}, {9, 10}, {11, 12} });  
    Matrix<double> c = a * b;                         

    EXPECT_EQ(c.get_N(), 2);
    EXPECT_EQ(c.get_M(), 2);
    EXPECT_DOUBLE_EQ(c[0][0], 58);    
    EXPECT_DOUBLE_EQ(c[0][1], 64);    
    EXPECT_DOUBLE_EQ(c[1][0], 139);   
    EXPECT_DOUBLE_EQ(c[1][1], 154);   
}

TEST(ClassMatrix, can_multiply_assign_square) {
    Matrix<double> a({ {1, 2}, {3, 4} });
    Matrix<double> b({ {5, 6}, {7, 8} });
    a *= b;

    EXPECT_EQ(a.get_N(), 2);
    EXPECT_EQ(a.get_M(), 2);
    EXPECT_DOUBLE_EQ(a[0][0], 19);
    EXPECT_DOUBLE_EQ(a[0][1], 22);
    EXPECT_DOUBLE_EQ(a[1][0], 43);
    EXPECT_DOUBLE_EQ(a[1][1], 50);

    EXPECT_DOUBLE_EQ(b[0][0], 5);
}

TEST(ClassMatrix, can_multiply_assign_rectangular) {
    Matrix<double> a({ {1, 2, 3}, {4, 5, 6} });      
    Matrix<double> b({ {7, 8}, {9, 10}, {11, 12} }); 
    a *= b;                                          

    EXPECT_EQ(a.get_N(), 2);
    EXPECT_EQ(a.get_M(), 2);
    EXPECT_DOUBLE_EQ(a[0][0], 58);
    EXPECT_DOUBLE_EQ(a[0][1], 64);
    EXPECT_DOUBLE_EQ(a[1][0], 139);
    EXPECT_DOUBLE_EQ(a[1][1], 154);
}

TEST(ClassMatrix, multiply_by_identity) {
    Matrix<double> a({ {1, 2, 3}, {4, 5, 6} });
    Matrix<double> e({ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} });
    Matrix<double> c = a * e;

    EXPECT_EQ(c.get_N(), 2);
    EXPECT_EQ(c.get_M(), 3);
    EXPECT_DOUBLE_EQ(c[0][0], 1);
    EXPECT_DOUBLE_EQ(c[0][1], 2);
    EXPECT_DOUBLE_EQ(c[0][2], 3);
    EXPECT_DOUBLE_EQ(c[1][0], 4);
    EXPECT_DOUBLE_EQ(c[1][1], 5);
    EXPECT_DOUBLE_EQ(c[1][2], 6);
}

TEST(ClassMatrix, throw_when_multiply_incompatible_sizes) {
    Matrix<double> a({ {1, 2}, {3, 4} });   
    Matrix<double> b({ {1, 2, 3} });        
    EXPECT_ANY_THROW(a * b);
}

TEST(ClassMatrix, throw_when_multiply_assign_incompatible_sizes) {
    Matrix<double> a({ {1, 2}, {3, 4} });   
    Matrix<double> b({ {1, 2, 3} });        
    EXPECT_ANY_THROW(a *= b);
}


TEST(ClassMatrix, inherited_size_equals_N) {
    Matrix<double> m({ {1, 2, 3}, {4, 5, 6} });
    EXPECT_EQ(m.size(), 2);
    EXPECT_EQ(m.size(), m.get_N());
}

TEST(ClassMatrix, inherited_operator_index_returns_row) {
    Matrix<double> m({ {1, 2, 3}, {4, 5, 6} });
    EXPECT_EQ(m[0].size(), 3);
    EXPECT_EQ(m[1].size(), 3);
    EXPECT_EQ(m[0].size(), m.get_M());
    EXPECT_EQ(m[1].size(), m.get_M());
}

TEST(ClassMatrix, inherited_operator_index_reads_elements) {
    Matrix<double> m({ {1, 2}, {3, 4} });
    EXPECT_DOUBLE_EQ(m[0][0], 1);
    EXPECT_DOUBLE_EQ(m[0][1], 2);
    EXPECT_DOUBLE_EQ(m[1][0], 3);
    EXPECT_DOUBLE_EQ(m[1][1], 4);
}

TEST(ClassMatrix, inherited_operator_index_can_modify) {
    Matrix<double> m({ {1, 2}, {3, 4} });
    m[1][0] = 33;
    EXPECT_DOUBLE_EQ(m[1][0], 33);
    EXPECT_DOUBLE_EQ(m[0][0], 1);
}

TEST(ClassMatrix, inherited_row_addition) {
    Matrix<double> m({ {1, 2}, {3, 4} });
    MathVector<double> row = m[0] + m[1];
    EXPECT_EQ(row.size(), 2);
    EXPECT_DOUBLE_EQ(row[0], 4);
    EXPECT_DOUBLE_EQ(row[1], 6);
}

TEST(ClassMatrix, inherited_row_subtraction) {
    Matrix<double> m({ {5, 6}, {1, 2} });
    MathVector<double> row = m[0] - m[1];
    EXPECT_DOUBLE_EQ(row[0], 4);
    EXPECT_DOUBLE_EQ(row[1], 4);
}

TEST(ClassMatrix, inherited_row_dot_product) {
    Matrix<double> m({ {1, 2, 3}, {4, 5, 6} });
    double dot = m[0] * m[1];   
    EXPECT_DOUBLE_EQ(dot, 32.0);
}

TEST(ClassMatrix, inherited_row_scalar_multiply) {
    Matrix<double> m({ {1, 2}, {3, 4} });
    MathVector<double> row = m[0] * 2.0;
    EXPECT_DOUBLE_EQ(row[0], 2);
    EXPECT_DOUBLE_EQ(row[1], 4);
    EXPECT_DOUBLE_EQ(m[0][0], 1);
    EXPECT_DOUBLE_EQ(m[0][1], 2);
}

TEST(ClassMatrix, inherited_row_output) {
    Matrix<double> m({ {1, 2}, {3, 4} });
    std::stringstream out;
    out << m[0];
    EXPECT_EQ("{1, 2}", out.str());
}

TEST(ClassMatrix, can_output_with_operator_cout) {
    Matrix<double> m({ {1, 2}, {3, 4} });
    std::stringstream out;
    out << m;
    EXPECT_EQ("{1, 2}\n{3, 4}\n", out.str());
}

#endif 
