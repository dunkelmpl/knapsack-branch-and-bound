#pragma once
class KnapsackItem
{
public:
    KnapsackItem(float weight, int value);
    virtual ~KnapsackItem();

public:
    inline double getRatio() { return ratio; }
    inline float getWeight() { return weight; }
    inline int getValue() { return value; }

public:
    void setWeight(float weight);
    void setValue(int value);

protected:
    void calcRatio();

private:
    float weight;
    int value;
    double ratio;
};

