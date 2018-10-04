#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <vector>

class BubbleSort
{
public:
  typedef unsigned long dataType;

  BubbleSort(dataType items);

  void sort();

  void print();

private:
  std::vector<dataType> m_items;
};

#endif // BUBBLESORT_H
