#include <iostream>


/// @brief adds all even numbers between a and b
/// @param a lesser number
/// @param b greater number
/// @return the sum of all even numbers between a and b
int add_even_between(int a, int b){
    int a1 = a/2;
    int b1 = b/2;
    auto sum = (b1*(b1+1) - a1*(a1+1))*2;
    return sum;
}



int main(){
    int a = 0;
    int b = 0;
    std::cout << "Please enter two numbers: ";
    std::cin >> a >> b;
    std::cout << "The sum of all even numbers between " << a << " and " << b << " is " << add_even_between(a,b) << std::endl;
    return 0;
}