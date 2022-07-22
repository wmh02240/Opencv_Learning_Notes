# CMakeList.txt: 1_Read_Img_or_Video 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 将源代码添加到此项目的可执行文件。
# add_executable (1_Introduction "display_image.cpp" "documentation.cpp" "introduction_windows_vs.cpp" )
add_executable (MatchTemplate_Demo "MatchTemplate_Demo.cpp")


# TODO: 如有需要，请添加测试并安装目标。
# Link your application with OpenCV libraries
target_link_libraries(MatchTemplate_Demo PRIVATE ${OpenCV_LIBS})