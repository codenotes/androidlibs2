if (console_bridge_CONFIG_INCLUDED)
  return()
endif()
set(console_bridge_CONFIG_INCLUDED TRUE)

set(console_bridge_INCLUDE_DIRS "F:/PROJECTS/infusion/ros-android/ros/install_isolated/include")

foreach(lib console_bridge)
  set(onelib "${lib}-NOTFOUND")
  find_library(onelib ${lib}
    PATHS "F:/PROJECTS/infusion/ros-android/ros/install_isolated/lib"
    NO_DEFAULT_PATH
    )
  if(NOT onelib)
    message(FATAL_ERROR "Library '${lib}' in package console_bridge is not installed properly")
  endif()
  list(APPEND console_bridge_LIBRARIES ${onelib})
endforeach()

foreach(dep )
  if(NOT ${dep}_FOUND)
    find_package(${dep})
  endif()
  list(APPEND console_bridge_INCLUDE_DIRS ${${dep}_INCLUDE_DIRS})
  list(APPEND console_bridge_LIBRARIES ${${dep}_LIBRARIES})
endforeach()
