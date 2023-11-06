#include "priorityqueue.hpp"

PriorityQueue::PriorityQueue()
{
    Size = -1;
    Items = new Item[1000];
}

PriorityQueue::PriorityQueue(const PriorityQueue& Other) noexcept
{
    Size = Other.Size;
    Items = new Item[Size]; // Allocate memory for the items

    for (int i = 0; i <= Size; i++) {
        Items[i] = Other.Items[i]; // Copy each item from the source
    }
}

PriorityQueue::~PriorityQueue()
{
    delete[] Items;
}

PriorityQueue& PriorityQueue::operator=(const PriorityQueue& Other)
{
    if (this != &Other) {
        if(Size > -1 && Items != nullptr)
        {
            delete[] Items;
            Items = nullptr;
            Size = -1;
        }
        Size = Other.Size;
        Items = new Item[Size]; // Allocate memory for the items

        for (int i = 0; i <= Size; i++) {
            Items[i] = Other.Items[i]; // Copy each item from the source
        }
    }
    return *this;
}

PriorityQueue& PriorityQueue::operator=(PriorityQueue&& Other) noexcept
{
    if (this != &Other) {
        if(Size > -1 && Items != nullptr)
        {
            delete[] Items;
            Items = nullptr;
            Size = -1;
        }
        Size = Other.Size;
        Items = new Item[Size]; // Allocate memory for the items
        for (int i = 0; i <= Size; i++) {
            Items[i] = Other.Items[i]; // Copy each item from the source
        }

        // Set the source object's Items to nullptr and Size to 0
        delete[] Other.Items;
        Other.Items = nullptr;
        Other.Size = -1;
    }
    return *this;
}

PriorityQueue& PriorityQueue::operator+=(const PriorityQueue& Other)
{
    if (this != &Other && Other.Size > -1 && Other.Items)
    {
        // int NewSize = Size + Other.Size+1;
        // for (int i = Size+1; i <= NewSize; ++i)
        // {
        //     Items[i] = Other.Items[i - Size+1];
        // }
        // Size = NewSize;
        for(int i = 0; i <= Other.Size; ++i)
            Enqueue(Other.Items->Value, Other.Items->Priority);
    }
    return *this;
}

PriorityQueue PriorityQueue::operator+(const PriorityQueue& Other) const
{
    PriorityQueue Result = *this; // Create a copy of the current object

    // Append elements from the 'Other' PriorityQueue
    for (int i = 0; i <= Other.Size; ++i) {
        Result.Enqueue(Other.Items[i].Value, Other.Items[i].Priority);
    }

    return Result;
}

void PriorityQueue::Enqueue(const char Value, const int Priority)
{
    if(Items == nullptr)
    {
        Items = new Item[1000];
    }
    Size++;
    Items[Size] = {Value, Priority};
}

void PriorityQueue::Dequeue()
{
    int Index = Top();

    // Shift the element one index before
    // from the position of the element
    // with highest priority is found
    for (int i = Index; i < Size; i++) {
        Items[i] = Items[i + 1];
    }
    // Decrease the size of the
    // priority queue by one
    Size--;
}

int PriorityQueue::Top()
{
    int HighestPriority = INT_MIN;
    int Index = -1;

    // Check for the element with
    // highest priority
    for (int i = 0; i <= Size; i++)
    {
        // If priority is same choose
        // the element with the
        // highest value
        int Value1 = Items[Index].Value, Value2 = Items[i].Value;
        if (HighestPriority == Items[i].Priority && Index > -1 && Value1 < Value2)
        {
            HighestPriority = Items[i].Priority;
            Index = i;
        }
        else if (HighestPriority < Items[i].Priority)
        {
            HighestPriority = Items[i].Priority;
            Index = i;
        }
    }

    // Return position of the element
    return Index;
}

int PriorityQueue::GetSize() noexcept
{
    return Size + 1;
}

char PriorityQueue::GetMin() noexcept
{
    int Min = '{';
    char Result = 0;
    for(int i = 0; i <= Size; ++i)
    {
        int Current = static_cast<int>(Items[i].Value);
        if (Current < Min)
        {
            Result = Items[i].Value;
            Min = Current;
        }
    }
    return Result;
}

char PriorityQueue::GetMax() noexcept
{
    int Max = '@';
    char Result = 0;
    for(int i = 0; i <= Size; ++i)
    {
        int Current = static_cast<int>(Items[i].Value);
        if (Current > Max)
        {
            Max = Current;
            Result = Items[i].Value;
        }
    }
    return Result;
}

int PriorityQueue::Find(char Character)
{
    int Result = -1;
    for(int i = 0; i <= Size; ++i)
    {
        if (Character == Items[i].Value)
        {
            Result = i;
        }
    }
    return Result;
}

void PriorityQueue::Append(const PriorityQueue& Other) noexcept
{
    if(Other.Size > -1 && Other.Items)
    {
        for (int i = 0; i <= Other.Size; ++i)
            Enqueue(Other.Items[i].Value, Other.Items[i].Priority);
    }
}

char PriorityQueue::ValueAt(int Index)
{
    return Items[Index].Value;
}

int PriorityQueue::PriorityAt(int Index)
{
    return Items[Index].Priority;
}

void PriorityQueue::Empty()
{
    delete[] Items;
    Items = nullptr;
    Size = -1;
}
