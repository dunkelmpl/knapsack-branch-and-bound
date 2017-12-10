#pragma once

#include "KnapsackItem.h"
#include "BranchAndBoundNode.h"

#include <vector>

using namespace std;

class KnapsackProfitCalc
{
public:
    KnapsackProfitCalc(vector<KnapsackItem>& items, int capacity);
    virtual ~KnapsackProfitCalc();

public:
    int getMaxProfit();

protected:
    void sortItems();
    int getNodeBound(BranchAndBoundNode& startLevelNode);

private:
    BranchAndBoundNode getNextBranchAndBoundNode(BranchAndBoundNode& currentNode, bool inBranch);

private:
    vector<KnapsackItem>& items;
    int capacity;
};

