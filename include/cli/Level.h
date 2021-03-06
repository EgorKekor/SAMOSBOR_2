#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "tinyxml2.h"

struct Object {
  int GetPropertyInt(const std::string& name1);                   //номер свойства объекта в нашем списке
  float GetPropertyFloat(const std::string& name2);

  std::string GetPropertyString(const std::string& name3);

  std::string name;                                       //объявили переменную name типа string
  std::string type;                                       //а здесь переменную type типа string
  sf::Rect<float> rect;                                   //тип Rect с нецелыми значениями
  std::map<std::string, std::string> properties;          //создаём ассоциатиный массив. ключ - строковый тип, значение - строковый

  sf::Sprite sprite;                                      //объявили спрайт
};

struct Layer {
  int opacity;                                            //непрозрачность слоя
  std::vector<sf::Sprite> tiles;                          //закидываем в вектор тайлы
};

class Level                                                 //главный класс - уровень
{
 public:
  bool LoadFromFile(const std::string& filename);                //возвращает false если не получилось загрузить
  Object GetObject(const std::string& name);

  std::vector<Object> GetObjects(const std::string& name);       //выдаем объект в наш уровень
  std::vector<Object> GetAllObjects();                    //выдаем все объекты в наш уровень
  void Draw(sf::RenderWindow &window);                    //рисуем в окно
  sf::Vector2i GetTileSize();                             //получаем размер тайла
  bool increase_opaciti(int layNum, int inc);
  int get_layer_damage(int layNum);

 private:
  int width, height, tileWidth, tileHeight;               //в tmx файле width height в начале,затем размер тайла
  int firstTileID;                                        //получаем айди первого тайла
  sf::Rect<float> drawingBounds;                          //размер части карты которую рисуем
  sf::Texture tilesetImage;                               //текстура карты
  std::vector<Object> objects;                            //массив типа Объекты, который мы создали
  std::vector<Layer> layers;
};

#endif
