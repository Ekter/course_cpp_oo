set(PROJECT_SOURCES
  imageparams.h
  main.cpp
  checkerimage.cpp checkerimage.h
  mainwindow.cpp mainwindow.h
)

add_executable(lab04_basic
  ${PROJECT_SOURCES}
)

target_link_libraries(lab04_basic PRIVATE Qt::Core Qt::Gui Qt::Widgets)
