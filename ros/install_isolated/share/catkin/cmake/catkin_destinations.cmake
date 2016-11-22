#
# Set several path suffixes for install destinations.
#
# :outvar CATKIN_PACKAGE_BIN_DESTINATION:
#   See :cmake:data:`CATKIN_PACKAGE_BIN_DESTINATION`.
# :outvar CATKIN_PACKAGE_ETC_DESTINATION:
#   See :cmake:data:`CATKIN_PACKAGE_ETC_DESTINATION`.
# :outvar CATKIN_PACKAGE_INCLUDE_DESTINATION:
#   See :cmake:data:`CATKIN_PACKAGE_INCLUDE_DESTINATION`.
# :outvar CATKIN_PACKAGE_LIB_DESTINATION:
#   See :cmake:data:`CATKIN_PACKAGE_LIB_DESTINATION`.
# :outvar CATKIN_PACKAGE_PYTHON_DESTINATION:
#   See :cmake:data:`CATKIN_PACKAGE_PYTHON_DESTINATION`.
# :outvar CATKIN_PACKAGE_SHARE_DESTINATION:
#   See :cmake:data:`CATKIN_PACKAGE_SHARE_DESTINATION`.
#
# :outvar CATKIN_GLOBAL_BIN_DESTINATION:
#   See :cmake:data:`CATKIN_GLOBAL_BIN_DESTINATION`.
# :outvar CATKIN_GLOBAL_ETC_DESTINATION:
#   See :cmake:data:`CATKIN_GLOBAL_ETC_DESTINATION`.
# :outvar CATKIN_GLOBAL_INCLUDE_DESTINATION:
#   See :cmake:data:`CATKIN_GLOBAL_INCLUDE_DESTINATION`.
# :outvar CATKIN_GLOBAL_LIB_DESTINATION:
#   See :cmake:data:`CATKIN_GLOBAL_LIB_DESTINATION`.
# :outvar CATKIN_GLOBAL_LIBEXEC_DESTINATION:
#   See :cmake:data:`CATKIN_GLOBAL_LIBEXEC_DESTINATION`.
# :outvar CATKIN_GLOBAL_PYTHON_DESTINATION:
#   See :cmake:data:`CATKIN_GLOBAL_PYTHON_DESTINATION`.
# :outvar CATKIN_GLOBAL_SHARE_DESTINATION:
#   See :cmake:data:`CATKIN_GLOBAL_SHARE_DESTINATION`.
#
macro(catkin_destinations)
  # verify that project() has been called before
  if(NOT PROJECT_NAME)
    message(FATAL_ERROR "catkin_destinations() PROJECT_NAME is not set. You must call project() before you can call catkin_destinations().")
  endif()

  # execute catkin_destinations() only once, skip repeated invocations
  if(NOT DEFINED _${PROJECT_NAME}_CATKIN_DESTINATIONS)
    debug_message(10 "catkin_destinations()")

    # mark that catkin_destinations() was called
    set(_${PROJECT_NAME}_CATKIN_DESTINATIONS TRUE)

    # set project specific install destinations
    if (CYGWIN)
	  set(CATKIN_PACKAGE_BIN_DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})	#DLLs get copied here by default. Put them together to avoid putting every directory in PATH
	else()
	  set(CATKIN_PACKAGE_BIN_DESTINATION ${CATKIN_GLOBAL_LIBEXEC_DESTINATION}/${PROJECT_NAME})
	endif()
    set(CATKIN_PACKAGE_ETC_DESTINATION ${CATKIN_GLOBAL_ETC_DESTINATION}/${PROJECT_NAME})
    set(CATKIN_PACKAGE_INCLUDE_DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}/${PROJECT_NAME})
    set(CATKIN_PACKAGE_LIB_DESTINATION ${CATKIN_GLOBAL_LIB_DESTINATION})
    set(CATKIN_PACKAGE_PYTHON_DESTINATION ${CATKIN_GLOBAL_PYTHON_DESTINATION}/${PROJECT_NAME})
    set(CATKIN_PACKAGE_SHARE_DESTINATION ${CATKIN_GLOBAL_SHARE_DESTINATION}/${PROJECT_NAME})

    # set project specific output directory for libraries
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_LIB_DESTINATION})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_LIB_DESTINATION})
    # set project specific output directory for binaries
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_BIN_DESTINATION})
  endif()
endmacro()
