#include <iostream>
#include <algorithm>

int main() {
    double a{};
    double b{};
    double c{};
    double v0{};
    double v1{};
    double v2{};

    std::cin >> a >> b >> c >> v0 >> v1 >> v2;

    double p1 = (a + b) / v0 + (a + b) / v1; 
    double p2 = a / v0 + c / v1 + b / v2;
    double p3 = b / v0 + c / v1 + a / v2;
    double p4 = b / v0 + c / v1 + c / v2 + b / v2;
    double p5 = a / v0 + c / v1 + c / v2 + a / v2;
    double p6 = b / v0 + c / v0 + c / v1 + b / v2;
    double p7 = a / v0 + c / v0 + c / v1 + a / v2;
    double p8 = a / v0 + c / v0 + c / v1 + a / v1 + b / v0 + c / v0 + c / v1 + b / v1;
    double p9 = a / v0 + c / v0 + c / v1 + a / v1 + a / v0 + a / v1;
    double p10 = b / v0 + c / v0 + c / v1 + b / v1 + b / v0 + b / v1;



    std::cout << std::min({p1, p2, p3, p4, p5, p6, p7, p8, p9, p10});

	return 0;
}
