
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <map>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>


template <typename T>
std::string typeName(T type)
{
  return "Unknown type";
}


template <>
std::string typeName(int type)
{
  return "int" ;
}

template <>
std::string typeName(std::string type)
{
  return "std::string" ;
}


 class Serializer
 {
 public:
   template <typename T>
   void append(T data)
   { 
     typeName(data);
     std::cout << typeName(data) << " "<< data << std::endl;
   }

   /*
   template <>
   void append(int* data)
   { 
     std::cout << *data << std::endl;
   }
   */
   template <class C>
   void append(std::vector<typename C::value_type> data)
   {
     std::cout << "std::vector - begin"<<std::endl;
     for (typename std::vector<typename C::value_type>::const_iterator cit = data.begin(); cit != data.end(); cit++)
     {
       append<typename C::value_type>(*cit);
     }
     std::cout << "std::vector - end"<<std::endl;
   }

   template <class C>
   void append(std::map<typename C::key_type, typename C::mapped_type> data)
   {
     typedef std::map<typename C::key_type, typename C::mapped_type> thisMap_T;
     std::cout << "std::map - begin"<<std::endl;
     for (typename thisMap_T::const_iterator cit = data.begin(); cit != data.end(); cit++)
     {
       append<typename C::key_type>(cit->first);
       append<typename C::mapped_type>(cit->second);
     }
     std::cout << "std::map - end"<<std::endl;
   }
 };

 typedef std::vector<int> myType_T;
 typedef std::vector<myType_T> combinedType_T;
 typedef std::map<int, std::string> myMap_T;

int main(int argc, char* argv[])
{
  printf("Starting\n");
  Serializer serial;
  myType_T m_myValues;
  m_myValues.push_back(1);
  m_myValues.push_back(2);
  m_myValues.push_back(3);
  int *a = new int(10);
  serial.append(*a);

  int b = 11;
  serial.append(b);

  float dd = 10.11;
  serial.append(dd);

  serial.append<myType_T>(m_myValues);

  combinedType_T m_combined;
  m_combined.push_back(m_myValues);
  m_myValues.push_back(4);
  m_combined.push_back(m_myValues);

  serial.append<combinedType_T>(m_combined);

  myMap_T mapper;
  mapper.insert(std::make_pair<int, std::string>(1, "en"));
  mapper.insert(std::make_pair<int, std::string>(2, "to"));

  serial.append<myMap_T>(mapper);

  printf("Stop\n");

 return 0;
}

