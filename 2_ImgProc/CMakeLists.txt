# CMakeList.txt: 1_Read_Img_or_Video 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 将源代码添加到此项目的可执行文件。
add_executable (Morphology_1 "Morphology_1.cpp")
add_executable (Morphology_2 "Morphology_2.cpp")
add_executable (BasicLinearTransforms "BasicLinearTransforms.cpp")
add_executable (Threshold "Threshold.cpp")
add_executable (Threshold_inRange "Threshold_inRange.cpp")
add_executable (Smoothing "Smoothing/Smoothing.cpp")
add_executable (Drawing_1 "basic_drawing/Drawing_1.cpp")
add_executable (Drawing_2 "basic_drawing/Drawing_2.cpp")
add_executable (Morphology_3 "morph_lines_detection/Morphology_3.cpp")
add_executable (periodic_noise_removing_filter "periodic_noise_removing_filter/periodic_noise_removing_filter.cpp")

# TODO: 如有需要，请添加测试并安装目标。
# Link your application with OpenCV libraries
target_link_libraries(Morphology_1 PRIVATE ${OpenCV_LIBS})
target_link_libraries(Morphology_2 PRIVATE ${OpenCV_LIBS})
target_link_libraries(BasicLinearTransforms PRIVATE ${OpenCV_LIBS})
target_link_libraries(Threshold PRIVATE ${OpenCV_LIBS})
target_link_libraries(Threshold_inRange PRIVATE ${OpenCV_LIBS})
target_link_libraries(Smoothing PRIVATE ${OpenCV_LIBS})
target_link_libraries(Drawing_1 PRIVATE ${OpenCV_LIBS})
target_link_libraries(Drawing_2 PRIVATE ${OpenCV_LIBS})
target_link_libraries(Morphology_3 PRIVATE ${OpenCV_LIBS})
target_link_libraries(periodic_noise_removing_filter PRIVATE ${OpenCV_LIBS})