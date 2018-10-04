cmake_minimum_required (VERSION 2.6)


set( JKB_INCLUDE_FILES Pipe.h Messages.h Serializable.h) 

add_library(LibMessages Serializable.cpp Pipe.cpp Messages.cpp ${JKB_INCLUDE_FILES})

#target_include_directories(LibMessages PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>)

subdirs(test) 
