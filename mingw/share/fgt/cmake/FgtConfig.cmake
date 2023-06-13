# Adapted version of CMakeFindDependencyMacro. We can't
# use the real McCoy b/c we need to set NO_CMAKE_SYSTEM_PATH,
# to avoid CMake's outdated FindArmadillo.cmake
if (NOT Armadillo_FOUND)
    set(cmake_fd_quiet_arg)
    if(Fgt_FIND_QUIETLY)
      set(cmake_fd_quiet_arg QUIET)
    endif()
    find_package(Armadillo
        4.600.1
        ${cmake_fd_quiet_arg}
        REQUIRED
        NO_CMAKE_SYSTEM_PATH)

    if (NOT Armadillo_FOUND)
        set(Fgt_NOT_FOUND_MESSAGE "Fgt could not be found because dependency Armadillo could not be found.")
        set(Fgt_FOUND False)
        return()
    endif()
    set(cmake_fd_quiet_arg)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/FgtTargets.cmake")
