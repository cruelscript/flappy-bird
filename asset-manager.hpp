#ifndef FLAPPYBIRD_ASSET_MANAGER_HPP
#define FLAPPYBIRD_ASSET_MANAGER_HPP

#include <map>
#include <SFML/Graphics.hpp>

class AssetManager
{
public:
  void loadTexture(const std::string& name, const std::string& filename);
  sf::Texture& getTexture(const std::string& name);

  void loadFont(const std::string& name, const std::string& filename);
  sf::Font& getFont(const std::string& name);

private:
  std::map<std::string, sf::Texture> textures_;
  std::map<std::string, sf::Font> fonts_;
};

#endif //FLAPPYBIRD_ASSET_MANAGER_HPP
