cmake_minimum_required(VERSION 3.8)

add_executable(findContours_demo findContours_demo.cpp)
add_executable(hull_demo hull_demo.cpp)
add_executable(moments_demo moments_demo.cpp)
add_executable(pointPolygonTest_demo pointPolygonTest_demo.cpp)
add_executable(generalContours_demo1 generalContours_demo1.cpp)
add_executable(generalContours_demo2 generalContours_demo2.cpp)


target_link_libraries(findContours_demo PRIVATE ${OpenCV_LIBS})
target_link_libraries(hull_demo PRIVATE ${OpenCV_LIBS})
target_link_libraries(moments_demo PRIVATE ${OpenCV_LIBS})
target_link_libraries(pointPolygonTest_demo PRIVATE ${OpenCV_LIBS})
target_link_libraries(generalContours_demo1 PRIVATE ${OpenCV_LIBS})
target_link_libraries(generalContours_demo2 PRIVATE ${OpenCV_LIBS})