#pragma once

struct BranchAndBoundNode {

    BranchAndBoundNode() : level(-1), profit(0), weight(0), bound(0) {}
    BranchAndBoundNode(int level, int profit, float weight) : level(level), profit(profit), weight(weight), bound(0) {}

    BranchAndBoundNode& operator=(BranchAndBoundNode& anotherNode) {
        this->level = anotherNode.level;
        this->weight = anotherNode.weight;
        this->profit = anotherNode.profit;

        return *this;
    }

    int level;
    int profit;
    float weight;
    int bound;
};