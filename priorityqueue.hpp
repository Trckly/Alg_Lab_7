// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <climits>

class PriorityQueue
{
public:
    PriorityQueue();
    PriorityQueue(const PriorityQueue& Other) noexcept;
    ~PriorityQueue();
    PriorityQueue& operator=(const PriorityQueue& Other);
    PriorityQueue& operator=(PriorityQueue&& Other) noexcept;
    PriorityQueue& operator+=(const PriorityQueue& Other);
    PriorityQueue operator+(const PriorityQueue& Other) const;

    enum EPriorityTypes
    {
        Lowest,
        Low,
        BelowNormal,
        Normal,
        AboveNormal,
        High,
        Highest
    };

    // Function to insert a new element
    // into priority queue
    void Enqueue(char Value, int Priority);

    // Function to remove the element with
    // the highest priority
    void Dequeue();

    // Function to check the top element
    int Top();

    int GetSize() noexcept;

    char GetMax() noexcept;

    char GetMin() noexcept;

    int Find(char Character);

    void Append(const PriorityQueue& Other) noexcept;

    char ValueAt(int Index);

    int PriorityAt(int Index);

    void Empty();

protected:
    struct Item
    {
        char Value;
        int Priority;
    };

    Item* Items;
    int Size;
};
