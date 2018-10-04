#include "bubblesort.h"
#include <iostream>
#include <climits>

BubbleSort::BubbleSort(dataType items)
{
  std::cout << "Data type has size of : " << sizeof(dataType) << std::endl;
  std::cout << "Bits  : " << CHAR_BIT << std::endl;
  for (dataType i = 0; i < items ; i ++)
  {
    m_items.push_back(items-i);
  }
}

void BubbleSort::sort()
{
  bool swap = true;

  while (swap==true)
  {
    swap = false;
    for (dataType i = 0;  i < m_items.size()-1; i++)
    {
      if (m_items[i] > m_items[i+1])
      {
        dataType tmp = m_items[i];
        m_items[i] = m_items[i+1];
        m_items[i+1] = tmp;
        swap = true;
      }
    }
  }
}

void BubbleSort::print()
{
  std::vector<dataType>::iterator it = m_items.begin();
  while (it != m_items.end())
  {
    std::cout << (*it) << ",";
    it++;
  }
  std::cout << std::endl;
}


