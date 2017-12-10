#include "KnapsackItem.h"
#include <stdexcept>

using namespace std;

KnapsackItem::KnapsackItem(float weight, int value) :
    weight(weight), value(value)
{
    this->calcRatio();
}

KnapsackItem::~KnapsackItem()
{
}

void KnapsackItem::setWeight(float weight)
{
    this->weight = weight;

    this->calcRatio();
}

void KnapsackItem::setValue(int value)
{
    this->value = value;

    this->calcRatio();
}


void KnapsackItem::calcRatio()
{
    if (weight == 0) {
        throw invalid_argument("Item weight cannot be null");
    }
    
    this->ratio = (double)value / weight;
}