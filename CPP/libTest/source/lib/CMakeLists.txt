
cmake_minimum_required(VERSION 2.6)

include_directories(${libTest_SOURCE_DIR}/interface)


add_subdirectory(${KPS_LANG})


add_library(Greeting${KPS_LANG_UPPERCASED}${KPS_OPTIMIZED_SUFFIX} ${KPS_LIB_FILES})
