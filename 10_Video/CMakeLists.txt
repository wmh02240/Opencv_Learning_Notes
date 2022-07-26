# CMakeList.txt: 1_Read_Img_or_Video 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 将源代码添加到此项目的可执行文件。
add_executable (bg_sub "bg_sub.cpp")
add_executable (camshift "meanshift/camshift.cpp")
add_executable (meanshift "meanshift/meanshift.cpp")
add_executable (optical_flow "optical_flow/optical_flow.cpp")
add_executable (optical_flow_dense "optical_flow/optical_flow_dense.cpp")


# TODO: 如有需要，请添加测试并安装目标。
# Link your application with OpenCV libraries
target_link_libraries(bg_sub PRIVATE ${OpenCV_LIBS})
target_link_libraries(camshift PRIVATE ${OpenCV_LIBS})
target_link_libraries(meanshift PRIVATE ${OpenCV_LIBS})
target_link_libraries(optical_flow PRIVATE ${OpenCV_LIBS})
target_link_libraries(optical_flow_dense PRIVATE ${OpenCV_LIBS})