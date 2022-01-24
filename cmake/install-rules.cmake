if(PROJECT_IS_TOP_LEVEL)
  set(CMAKE_INSTALL_INCLUDEDIR include/codegen CACHE PATH "")
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package codegen)

install(
    TARGETS codegen_exe
    EXPORT codegenTargets
    RUNTIME COMPONENT codegen_Runtime
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    codegen_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(codegen_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${codegen_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT codegen_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${codegen_INSTALL_CMAKEDIR}"
    COMPONENT codegen_Development
)

install(
    EXPORT codegenTargets
    NAMESPACE codegen::
    DESTINATION "${codegen_INSTALL_CMAKEDIR}"
    COMPONENT codegen_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
