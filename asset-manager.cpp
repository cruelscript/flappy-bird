#include <iostream>
#include "asset-manager.hpp"

void AssetManager::loadTexture(const std::string& name, const std::string& filename)
{
  sf::Texture texture;
  if(texture.loadFromFile(filename))
  {
    textures_[name] = texture;
  }
}

sf::Texture& AssetManager::getTexture(const std::string& name)
{
  return textures_[name];
}

void AssetManager::loadFont(const std::string& name, const std::string& filename)
{
  sf::Font font;
  if(font.loadFromFile(filename))
  {
    fonts_[name] = font;
  }
}

sf::Font& AssetManager::getFont(const std::string& name)
{
  return fonts_[name];
}
