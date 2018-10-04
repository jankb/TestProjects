cmake_minimum_required (VERSION 2.6)
project (Pipeline)



enable_testing()

if(MSVC)
	add_definitions(/W4)
else()
  find_package( Boost REQUIRED COMPONENTS system filesystem unit_test_framework)
	add_definitions(-Wall)
endif()

subdirs(Messages PipelineApp)


