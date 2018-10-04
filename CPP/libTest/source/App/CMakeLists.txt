cmake_minimum_required (VERSION 2.6)

include_directories(${libTest_SOURCE_DIR}/interface)
link_directories(${libTest_SOURCE_DIR}/lib)


add_executable(libTestApp${KPS_OPTIMIZED_SUFFIX} main.cpp)

target_link_libraries(libTestApp${KPS_OPTIMIZED_SUFFIX} Greeting${KPS_LANG_UPPERCASED}${KPS_OPTIMIZED_SUFFIX})



