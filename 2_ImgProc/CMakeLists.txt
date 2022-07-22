# CMakeList.txt: 1_Read_Img_or_Video 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 将源代码添加到此项目的可执行文件。
add_executable (2_ImgProc_1 "Morphology_1.cpp")
add_executable (2_ImgProc_2 "Morphology_2.cpp")
add_executable (2_ImgProc_3 "BasicLinearTransforms.cpp")
add_executable (2_ImgProc_4 "Threshold.cpp")
add_executable (2_ImgProc_5 "Threshold_inRange.cpp")

# TODO: 如有需要，请添加测试并安装目标。
# Link your application with OpenCV libraries
target_link_libraries(2_ImgProc_1 PRIVATE ${OpenCV_LIBS})
target_link_libraries(2_ImgProc_2 PRIVATE ${OpenCV_LIBS})
target_link_libraries(2_ImgProc_3 PRIVATE ${OpenCV_LIBS})
target_link_libraries(2_ImgProc_4 PRIVATE ${OpenCV_LIBS})
target_link_libraries(2_ImgProc_5 PRIVATE ${OpenCV_LIBS})