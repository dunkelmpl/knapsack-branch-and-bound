#include "KnapsackProfitCalc.h"

#include <algorithm>
#include <stdexcept>
#include <queue>

KnapsackProfitCalc::KnapsackProfitCalc(vector<KnapsackItem>& items, int capacity) :
    items(std::move(items)), capacity(capacity)
{
    this->sortItems();
}

KnapsackProfitCalc::~KnapsackProfitCalc()
{
}

void KnapsackProfitCalc::sortItems()
{
    sort(
        this->items.begin(),
        this->items.end(),
        [](KnapsackItem& item1, KnapsackItem& item2) {
            return item1.getRatio() > item2.getRatio();
        }
    );
}

int KnapsackProfitCalc::getNodeBound(BranchAndBoundNode& startLevelNode)
{
    // We don't need considering of items that are heavier than knapsack capacity.
    // And we're not interested in bound if starting level node has weight == knapsack capacity.
    if (startLevelNode.weight >= this->capacity) {
        return 0;
    }

    // This is more like misuse, because that should never happen per algorithm
    if (startLevelNode.level < 0 || startLevelNode.level >= (int)this->items.size()) {
        throw invalid_argument("Internal error: invalid starting level node");
    }

    int profitBound = startLevelNode.profit;

    double currentWeight = startLevelNode.weight;
    int itemIndex = startLevelNode.level + 1;
    while (itemIndex < (int)this->items.size()) {
        double newWeight = currentWeight + this->items[itemIndex].getWeight();

        if (newWeight > this->capacity) {
            break;
        }

        profitBound += this->items[itemIndex].getValue();

        currentWeight = newWeight;
        itemIndex++;
    }

    // Should not all items fit into knapsack
    // break the bound one.
    if (itemIndex < (int)this->items.size()) {
        profitBound += (int)((this->capacity - currentWeight)*this->items[itemIndex].getRatio());
    }

    return profitBound;
}

int KnapsackProfitCalc::getMaxProfit()
{
    queue<BranchAndBoundNode> queue;

    // Dummy node has level = -1, weight = 0, profit = 0
    // We need to for the following loop to make queue.pop()
    BranchAndBoundNode dummyNode;
    queue.push(dummyNode);

    int maxProfit = 0;

    while (!queue.empty()) {
        BranchAndBoundNode node = queue.front();
        queue.pop();

        if (node.level < (int)this->items.size() - 1) {
            // Let's include this node (go "in" branch)
            BranchAndBoundNode nextNode = this->getNextBranchAndBoundNode(node, true);

            // If calculated profit of the next node is greater than maxProfit
            if (nextNode.weight <= this->capacity && nextNode.profit > maxProfit) {
                maxProfit = nextNode.profit;
            }

            // If next node's bound is gerater than current max profit,
            // then we need to consider such a node
            if (nextNode.bound > maxProfit) {
                queue.push(nextNode);
            }

            // Now let's exclude this node (go "out" branch)
            nextNode = this->getNextBranchAndBoundNode(node, false);

            // Again, if next node's bound (for the "out" branch) is gerater than current max profit,
            // then we need to consider such a node and that kind of branch
            if (nextNode.bound > maxProfit) {
                queue.push(nextNode);
            }
        }
    }

    return maxProfit;
}

BranchAndBoundNode KnapsackProfitCalc::getNextBranchAndBoundNode(BranchAndBoundNode& currentNode, bool inBranch)
{
    BranchAndBoundNode nextNode(currentNode);
    nextNode.level++;

    if (inBranch) {
        nextNode.weight += this->items[nextNode.level].getWeight();
        nextNode.profit += this->items[nextNode.level].getValue();
    }

    nextNode.bound = this->getNodeBound(nextNode);

    return nextNode;
}