ADD_LIBRARY(
  EmbedGUI EXCLUDE_FROM_ALL
  Canvas.hpp
  GUI.cpp
  GUI.hpp
  RotatableCanvas.hpp
  Widget.hpp
  widgets/Animation.hpp
  widgets/Image.hpp
  widgets/Text.hpp)

TARGET_INCLUDE_DIRECTORIES(EmbedGUI PUBLIC . widgets)
