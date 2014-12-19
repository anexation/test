find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(KF5 REQUIRED COMPONENTS CoreAddons Config)

add_executable(gtkmenda main.cpp)

target_link_libraries(gtkmenda Qt5::Widgets KF5::CoreAddons KF5::ConfigCore)

install(TARGETS gtkmenda DESTINATION ${LIB_INSTALL_DIR}/kconf_update_bin/)
install(FILES gtkmenda.upd DESTINATION ${KCONF_UPDATE_INSTALL_DIR})
