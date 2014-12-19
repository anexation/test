add_definitions(-DTRANSLATION_DOMAIN="menda_kwin_deco")

find_package(KDecoration2 REQUIRED)
find_package(KF5 REQUIRED COMPONENTS CoreAddons ConfigWidgets WindowSystem)
find_package(Qt5 CONFIG REQUIRED COMPONENTS DBus)

### XCB
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

################# configuration #################
configure_file(config-menda.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-menda.h )

################# newt target #################
### plugin classes
set(mendadecoration_SRCS
    mendacolorsettings.cpp
    mendabutton.cpp
    mendadecoration.cpp
    mendaexceptionlist.cpp
    mendasettingsprovider.cpp
    mendasizegrip.cpp)

kconfig_add_kcfg_files(mendadecoration_SRCS mendasettings.kcfgc)

### config classes
### they are kept separately because they might move in a separate library in the future
set(mendadecoration_config_SRCS
    config/mendaconfig.cpp
    config/mendaconfigwidget.cpp
    config/mendadetectwidget.cpp
    config/mendaexceptiondialog.cpp
    config/mendaexceptionlistwidget.cpp
    config/mendaexceptionmodel.cpp
    config/mendaitemmodel.cpp
)

set(mendadecoration_config_PART_FORMS
   config/ui/mendaconfigurationui.ui
   config/ui/mendadetectwidget.ui
   config/ui/mendaexceptiondialog.ui
   config/ui/mendaexceptionlistwidget.ui
)

ki18n_wrap_ui(mendadecoration_config_PART_FORMS_HEADERS ${mendadecoration_config_PART_FORMS})

### build library
add_library(mendadecoration MODULE
    ${mendadecoration_SRCS}
    ${mendadecoration_config_SRCS}
    ${mendadecoration_config_PART_FORMS_HEADERS})

target_link_libraries(mendadecoration
    PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::DBus
    PRIVATE
        KDecoration2::KDecoration
        KF5::ConfigCore
        KF5::CoreAddons
        KF5::ConfigWidgets
        KF5::GuiAddons
        KF5::I18n
        KF5::WindowSystem)

if(MENDA_HAVE_X11)
  target_link_libraries(mendadecoration
    PUBLIC
      Qt5::X11Extras
      XCB::XCB)
endif()


install(TARGETS mendadecoration DESTINATION ${PLUGIN_INSTALL_DIR}/org.kde.kdecoration2)
