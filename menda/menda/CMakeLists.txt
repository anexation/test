project(menda)
set(PROJECT_VERSION "5.1.90")
set(PROJECT_VERSION_MAJOR 5)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

include(WriteBasicConfigVersionFile)
include(FeatureSummary)

if(USE_KDE4)
  add_subdirectory(kstyle)
else()
  find_package(ECM 0.0.9 REQUIRED NO_MODULE)
  set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

  include(KDEInstallDirs)
  include(KDECMakeSettings)
  include(KDECompilerSettings)
  include(GenerateExportHeader)

  add_subdirectory(kdecoration)
  add_subdirectory(kstyle)
  add_subdirectory(misc)
  add_subdirectory(qtquickcontrols)
  add_subdirectory(wallpapers)

  INSTALL(FILES colors/Menda.colors DESTINATION ${DATA_INSTALL_DIR}/color-schemes/)
  INSTALL(FILES colors/MendaDark.colors DESTINATION ${DATA_INSTALL_DIR}/color-schemes/)
  if(EXISTS ${CMAKE_SOURCE_DIR}/po AND IS_DIRECTORY ${CMAKE_SOURCE_DIR}/po)
    find_package(KF5I18n CONFIG REQUIRED)
    ki18n_install(po)
  endif()
endif()

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
message(" * Orion theme for GTK 2 and 3 will be set by gtkmenda kconf_update binary,"
        " please install or add a runtime dependency to packages. https://github.com/shimmerproject/Orion")
