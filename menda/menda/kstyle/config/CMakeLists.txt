### configuration plugin
add_definitions(-DTRANSLATION_DOMAIN=\"menda_style_config\")
set(kstyle_menda_config_PART_SRCS mendastyleconfig.cpp)

if(MENDA_USE_KDE4)

  kde4_add_kcfg_files(kstyle_menda_config_PART_SRCS ../mendastyleconfigdata.kcfgc)
  kde4_add_ui_files(kstyle_menda_config_PART_SRCS ui/mendastyleconfig.ui)
  kde4_add_plugin(kstyle_menda_config ${kstyle_menda_config_PART_SRCS})

  target_link_libraries(kstyle_menda_config ${KDE4_KDEUI_LIBS} )
  install(TARGETS kstyle_menda_config DESTINATION ${PLUGIN_INSTALL_DIR})

else()

  kconfig_add_kcfg_files(kstyle_menda_config_PART_SRCS ../mendastyleconfigdata.kcfgc)
  set(kstyle_menda_config_PART_FORMS ui/mendastyleconfig.ui)
  ki18n_wrap_ui(kstyle_menda_config_PART_FORMS_HEADERS ${kstyle_menda_config_PART_FORMS})

  add_library(kstyle_menda_config MODULE
    ${kstyle_menda_config_PART_SRCS}
    ${kstyle_menda_config_PART_FORMS_HEADERS}
 )

  target_link_libraries(kstyle_menda_config Qt5::Core Qt5::Gui Qt5::Widgets Qt5::DBus)
  target_link_libraries(kstyle_menda_config KF5::ConfigCore KF5::ConfigWidgets KF5::I18n)
  install(TARGETS kstyle_menda_config DESTINATION ${QT_PLUGIN_INSTALL_DIR})

endif()

########### next target ###############
if(KF5Service_FOUND AND NOT MENDA_USE_KDE4)

  set(menda_settings_SOURCES
    mendaconfigdialog.cpp
    main.cpp)

  set(menda_settings_FORMS ui/mendaconfigdialog.ui)

  ki18n_wrap_ui(menda_settings_FORMS_HEADERS ${menda_settings_FORMS})

  add_executable(menda-settings5
      ${menda_settings_SOURCES}
      ${menda_settings_FORMS_HEADERS}
 )

  target_link_libraries(menda-settings5 Qt5::Core Qt5::Gui Qt5::Widgets Qt5::DBus)
  target_link_libraries(menda-settings5 KF5::I18n KF5::WidgetsAddons KF5::ConfigCore KF5::ConfigGui KF5::Service)

  install(TARGETS menda-settings5 ${INSTALL_TARGETS_DEFAULT_ARGS})

endif()
