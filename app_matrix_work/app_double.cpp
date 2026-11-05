#include "app_double.h"
TriangleMatrix<double> app_double::get_tri_mat(size_t N)const noexcept {
	TriangleMatrix<double> res(N);
	for (int i = 0; i < N; i++) {
		for (int i2 = 0; i2 <= i; i2++) {
			std::cout << res;
			std::cout << "\n which number should be in [" << i << "][" << i2 << "]\n[line][pillar]\n";
			std::cin >> res[i][i2];
			system("cls");
		}
	}
	return res;
}
Matrix<double> app_double::get_mat(size_t N,size_t M)const noexcept {
	Matrix<double> res(N,M);
	for (int i = 0; i < N; i++) {
		for (int i2 = 0; i2 <M; i2++) {
			std::cout << res;
			std::cout << "\n which number should be in [" << i << "][" << i2 << "]\n[line][pillar]\n";
			std::cin >> res[i][i2];
			system("cls");
		}
	}
	return res;
}
void app_double::start() {
	int user_input,N,M,operation,N_2,M_2;
	TriangleMatrix<double> tmp1, tmp2,restri;
	Matrix<double> m1, m2,resm;
	char op;
	do {
		system("cls");
		std::cout << "with wich matrix you want to work?\n1.standart\n2.triangle\n";
		std::cin >> user_input;
	} while (user_input > 2 || user_input < 1);
	do {
		system("cls");
		std::cout << "input size of matrix,(number of lines";
		if (user_input == 1)
			std::cout << ", number of pillars";
		std::cout << ")\n";
		if (user_input == 2) {
			std::cin >> N;
			M = N;
		}
		else
			std::cin >> N>> M;
	} while (N<=0||M<=0);
	do {
		system("cls");
		std::cout << "choose operation:\n1.+\n2.*\n3.-\n";
		std::cin >> operation;
	} while (operation < 1 || operation>3);
	system("cls");
	if (user_input == 1) {
		m1 = get_mat(N, M);
		if (operation == 2) {
			do {
				system("cls");
				std::cout << "input size of matrix,(number of lines,pillars) for new matrix\n";
				std::cin >> N_2 >> M_2;
			} while (N_2 != M || M_2 <= 0);
		}
		else {
			N_2 = N;
			M_2 = M;
		}
		system("cls");
		m2 = get_mat(N_2, M_2);
	}
	else {
		tmp1 = get_tri_mat(N);
		tmp2 = get_tri_mat(N);
	}
	switch (operation) {
	case 1:
		if(user_input==2)
			restri = tmp1 + tmp2;
		else
			resm = m1 + m2; op = '+'; break;
	case 2:if (user_input == 2)
		restri = tmp1 * tmp2;
		else
		resm = m1 * m2; op = '*'; break;
	case 3:
		if (user_input == 2)
			restri = tmp1 - tmp2;
		else
			resm = m1 - m2; op = '-'; break;
	}
	if (user_input == 1) {
		std::cout << m1 << op << "\n" << m2 << "=\n" << resm;
	}
	else {
		std::cout << tmp1 << op << "\n" << tmp2 << "=\n" << restri;
	}
}