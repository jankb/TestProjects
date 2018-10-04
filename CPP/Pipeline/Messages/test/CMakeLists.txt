cmake_minimum_required (VERSION 2.6)



include_directories(${Pipeline_SOURCE_DIR}/Messages)

if (CMAKE_HOST_WIN32)
    include_directories("//ukgo-home-p01/jankb/TestProjects/boost")
endif()

add_executable(mTest test.cpp )

target_link_libraries(mTest 
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	)


add_test( MessageTest mTest )


 
