#include "Dice.h"
Dice::Dice(){}
int Dice::roll()
{
	
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> ud(1, 6);
    return ud(gen);
}