add_executable(dynamic_reconfigure-ref_server EXCLUDE_FROM_ALL ref_server.cpp)
add_dependencies(dynamic_reconfigure-ref_server ${PROJECT_NAME}_gencfg ${PROJECT_NAME}_generate_messages_cpp ${PROJECT_NAME}_generate_messages_py)
target_link_libraries(dynamic_reconfigure-ref_server pthread dynamic_reconfigure_config_init_mutex ${catkin_LIBRARIES})

add_dependencies(tests dynamic_reconfigure-ref_server)

if(CATKIN_ENABLE_TESTING)
add_rostest(test_python_simple_client.launch)
endif()