#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE Messages
#if !defined( WIN32 )
#define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>
#include "Serializable.h"

BOOST_AUTO_TEST_CASE ( POD_Size ) {
      BOOST_CHECK_EQUAL (sizeof(int), Pipeline::Messages::SerializablePlainOldData<int>::size(42));
      BOOST_CHECK (sizeof(long) != Pipeline::Messages::SerializablePlainOldData<int>::size(42));
}

BOOST_AUTO_TEST_CASE ( POD_Serialize )
{
  BOOST_ERROR("Not implemented");
}

BOOST_AUTO_TEST_CASE ( POD_Deserialize )
{
  BOOST_ERROR("Not implemented");
}
