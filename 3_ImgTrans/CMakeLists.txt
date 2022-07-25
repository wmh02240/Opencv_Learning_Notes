# CMakeList.txt: 1_Read_Img_or_Video 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 将源代码添加到此项目的可执行文件。
add_executable (CannyDetector_Demo CannyDetector_Demo.cpp)
add_executable (copyMakeBorder_demo copyMakeBorder_demo.cpp )
add_executable (Geometric_Transforms_Demo Geometric_Transforms_Demo.cpp )
add_executable (houghlines houghlines.cpp )
add_executable (HoughLines_Demo HoughLines_Demo.cpp )
add_executable (houghcircles houghcircles.cpp )
add_executable (HoughCircle_Demo HoughCircle_Demo.cpp )
add_executable (filter2D_demo filter2D_demo.cpp )
add_executable (imageSegmentation imageSegmentation.cpp )
add_executable (Laplace_Demo Laplace_Demo.cpp )
add_executable (Remap_Demo Remap_Demo.cpp )
add_executable (Sobel_Demo Sobel_Demo.cpp )

# TODO: 如有需要，请添加测试并安装目标。
# Link your application with OpenCV libraries
target_link_libraries(CannyDetector_Demo PRIVATE ${OpenCV_LIBS})
target_link_libraries(copyMakeBorder_demo PRIVATE ${OpenCV_LIBS})
target_link_libraries(Geometric_Transforms_Demo PRIVATE ${OpenCV_LIBS})
target_link_libraries(houghlines PRIVATE ${OpenCV_LIBS})
target_link_libraries(HoughLines_Demo PRIVATE ${OpenCV_LIBS})
target_link_libraries(houghcircles PRIVATE ${OpenCV_LIBS})
target_link_libraries(HoughCircle_Demo PRIVATE ${OpenCV_LIBS})
target_link_libraries(filter2D_demo PRIVATE ${OpenCV_LIBS})
target_link_libraries(imageSegmentation PRIVATE ${OpenCV_LIBS})
target_link_libraries(Laplace_Demo PRIVATE ${OpenCV_LIBS})
target_link_libraries(Remap_Demo PRIVATE ${OpenCV_LIBS})
target_link_libraries(Sobel_Demo PRIVATE ${OpenCV_LIBS})