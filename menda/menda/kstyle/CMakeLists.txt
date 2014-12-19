project(kstyle-menda)

set(MENDA_USE_KDE4 ${USE_KDE4})
if(MENDA_USE_KDE4)

  ############ Language and toolchain features
  ############ copied from ECM
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
  elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel" AND NOT WIN32)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
  endif()

endif()

################# Qt/KDE #################
if(MENDA_USE_KDE4)

  find_package(KDE4 REQUIRED)
  include(KDE4Defaults)
  include(MacroLibrary)

  add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
  include_directories(${KDE4_INCLUDES})

  ### XCB
  if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(XCB xcb x11-xcb)
    set(MENDA_HAVE_X11 ${XCB_FOUND})
  else()
    set(MENDA_HAVE_X11 FALSE)
  endif()

  ### KStyle
  set(MENDA_HAVE_KSTYLE FALSE)

else()

  find_package(Qt5 REQUIRED CONFIG COMPONENTS Widgets DBus)
  find_package(KF5 REQUIRED COMPONENTS
      I18n
      Config
      ConfigWidgets
      WindowSystem)

  find_package( KF5FrameworkIntegration CONFIG )
  set_package_properties(KF5FrameworkIntegration PROPERTIES
      DESCRIPTION "KF5 Framework Integration"
      URL "https://projects.kde.org/projects/frameworks/frameworkintegration"
      TYPE OPTIONAL
      PURPOSE "Required to use KStyle convenience functionalities in style")

  set(MENDA_HAVE_KSTYLE ${KF5FrameworkIntegration_FOUND})

  find_package(KF5Service CONFIG)
  set_package_properties(KF5Service PROPERTIES
      DESCRIPTION "KF5 Service Framework"
      URL "https://projects.kde.org/projects/frameworks/kservice"
      TYPE OPTIONAL
      PURPOSE "Required for menda-settings5 application to build")

  find_package(XCB COMPONENTS XCB)
  set_package_properties(XCB PROPERTIES
      DESCRIPTION "X protocol C-language Binding"
      URL "http://xcb.freedesktop.org"
      TYPE OPTIONAL
      PURPOSE "Required to pass style properties to native Windows on X11 Platform"
  )

  if(UNIX AND NOT APPLE)

    set(MENDA_HAVE_X11 ${XCB_XCB_FOUND})
    if (XCB_XCB_FOUND)
      find_package(Qt5 REQUIRED CONFIG COMPONENTS X11Extras)
    endif()

  else()

    set(MENDA_HAVE_X11 FALSE)

  endif()


endif()

################# includes #################
include_directories(
  animations
  debug
)

################# configuration #################
configure_file(config-menda.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-menda.h )

########### next target ###############
set(menda_PART_SRCS
    animations/mendaanimation.cpp
    animations/mendaanimations.cpp
    animations/mendaanimationdata.cpp
    animations/mendabaseengine.cpp
    animations/mendabusyindicatordata.cpp
    animations/mendabusyindicatorengine.cpp
    animations/mendadialdata.cpp
    animations/mendadialengine.cpp
    animations/mendaenabledata.cpp
    animations/mendagenericdata.cpp
    animations/mendaheaderviewdata.cpp
    animations/mendaheaderviewengine.cpp
    animations/mendascrollbardata.cpp
    animations/mendascrollbarengine.cpp
    animations/mendaspinboxengine.cpp
    animations/mendaspinboxdata.cpp
    animations/mendatabbarengine.cpp
    animations/mendatabbardata.cpp
    animations/mendatoolboxengine.cpp
    animations/mendawidgetstateengine.cpp
    animations/mendawidgetstatedata.cpp
    debug/mendawidgetexplorer.cpp
    mendaaddeventfilter.cpp
    mendaframeshadow.cpp
    mendahelper.cpp
    mendamdiwindowshadow.cpp
    mendamnemonics.cpp
    mendapropertynames.cpp
    mendashadowhelper.cpp
    mendasplitterproxy.cpp
    mendastyle.cpp
    mendastyleplugin.cpp
    mendatileset.cpp
    mendawindowmanager.cpp
)

if(MENDA_USE_KDE4)

  kde4_add_kcfg_files(menda_PART_SRCS mendastyleconfigdata.kcfgc)
  kde4_add_plugin(menda ${menda_PART_SRCS})
  target_link_libraries(menda  ${KDE4_KDEUI_LIBS})

  if(MENDA_HAVE_X11)
    target_link_libraries(menda ${X11_XCB_LIBRARIES})
    target_link_libraries(menda ${XCB_LIBRARIES})
  endif()

  install(TARGETS menda  DESTINATION ${PLUGIN_INSTALL_DIR}/plugins/styles/)

else()

  kconfig_add_kcfg_files(menda_PART_SRCS mendastyleconfigdata.kcfgc)
  add_library(menda MODULE ${menda_PART_SRCS})
  target_link_libraries(menda Qt5::Core Qt5::Gui Qt5::Widgets Qt5::DBus)
  target_link_libraries(menda KF5::ConfigCore KF5::ConfigWidgets KF5::GuiAddons KF5::WindowSystem)

  if( KF5FrameworkIntegration_FOUND )
  target_link_libraries(menda KF5::Style)
  endif()

  if (WIN32)
    # As stated in http://msdn.microsoft.com/en-us/library/4hwaceh6.aspx M_PI only gets defined
    # when if _USE_MATH_DEFINES is defined
    target_compile_definitions(menda PRIVATE _USE_MATH_DEFINES _BSD_SOURCE)
  endif()

  if(MENDA_HAVE_X11)
    target_link_libraries(menda ${XCB_LIBRARIES})
    target_link_libraries(menda Qt5::X11Extras)
  endif()

  install(TARGETS menda DESTINATION ${QT_PLUGIN_INSTALL_DIR}/styles/)

endif()

########### install files ###############
install(FILES menda.themerc  DESTINATION  ${DATA_INSTALL_DIR}/kstyle/themes)

########### subdirectories ###############
add_subdirectory(config)
