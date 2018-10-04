cmake_minimum_required (VERSION 2.6)
project (libTest)

if(DEFINED KPS_LANG)
  MESSAGE(STATUS "Current language : " ${KPS_LANG})
else()
  MESSAGE(FATAL_ERROR "Current language not set, use -DKPS_LANG={no,en}")
endif(DEFINED KPS_LANG)
string(TOUPPER ${KPS_LANG} KPS_LANG_UPPERCASED)

if(MSVC)
        add_definitions(/W4)
else()
        add_definitions(-Wall)
endif()

if (${KPS_OPTIMIZED})
  MESSAGE(STATUS "Bulding OPTIMIZED version, debugging might be _hard_")
  #add_definitions(-ffunction-sections -fdata-sections -Os)
  add_definitions(-Os)
  #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --gc-sections")
  set(KPS_OPTIMIZED_SUFFIX "_O")
endif()

subdirs(App lib)



