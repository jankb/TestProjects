cmake_minimum_required (VERSION 2.6)

include_directories(${Pipeline_SOURCE_DIR}/Messages)
link_directories(${Pipeline_SOURCE_DIR}/Messages)

add_executable(PipelineApp Pipeline.cpp )

target_link_libraries(PipelineApp LibMessages)



