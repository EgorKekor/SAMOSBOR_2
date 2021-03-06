#include <iostream>
#include <cli/Level.h>
#include "tinyxml.h"

using namespace std;
using namespace sf;

//возвращаем номер свойства в нашем списке
int Object::GetPropertyInt(const std::string& name1) {
  return atoi(properties[name1].c_str());
}

float Object::GetPropertyFloat(const std::string& name2) {
  return (float) strtod(properties[name2].c_str(), nullptr);
}

//получить имя в виде строки.вроде понятно
std::string Object::GetPropertyString(const std::string& name3) {
  return properties[name3];
}

bool Level::LoadFromFile(const std::string &filename) //двоеточия-обращение к методам класса вне класса
{
  TiXmlDocument levelFile(filename.c_str()); //загружаем файл в TiXmlDocument

  // загружаем XML-карту
  if (!levelFile.LoadFile()) //если не удалось загрузить карту
  {
    std::cout << "Loading level \"" << filename << "\" failed." << std::endl;//выдаем ошибку
    return false;
  }

  // работаем с контейнером map
  TiXmlElement *map;
  map = levelFile.FirstChildElement("map");

  // пример карты: <map version="1.0" orientation="orthogonal"
  // width="10" height="10" tilewidth="34" tileheight="34">
  width = atoi(map->Attribute("width"));//извлекаем из нашей карты ее свойства
  height = atoi(map->Attribute("height"));//те свойства, которые задавали при работе в
  tileWidth = atoi(map->Attribute("tilewidth"));//тайлмап редакторе
  tileHeight = atoi(map->Attribute("tileheight"));

  // Берем описание тайлсета и идентификатор первого тайла
  TiXmlElement *tilesetElement;
  tilesetElement = map->FirstChildElement("tileset");
  firstTileID = atoi(tilesetElement->Attribute("firstgid"));

  // source - путь до картинки в контейнере image
//  TiXmlElement *image;
//  image = tilesetElement->FirstChildElement("image");
  string imagepath("../Graphics/map/test1.png"); //image->Attribute("source"));

  // пытаемся загрузить тайлсет
  sf::Image img;

  if (!img.loadFromFile(imagepath)) {
    std::cout << "Failed to load tile sheet." << std::endl;//если не удалось загрузить тайлсет-выводим ошибку в консоль
    return false;
  }

  img.createMaskFromColor(sf::Color(255, 255, 255));//для маски цвета.сейчас нет маски
  tilesetImage.loadFromImage(img);
  tilesetImage.setSmooth(false);//сглаживание

  // получаем количество столбцов и строк тайлсета
  int columns = tilesetImage.getSize().x / tileWidth;
  int rows = tilesetImage.getSize().y / tileHeight;

  // вектор из прямоугольников изображений (TextureRect)
  std::vector<sf::Rect<int>> subRects;

  for (int y = 0; y < rows; y++)
    for (int x = 0; x < columns; x++) {
      sf::Rect<int> rect;

      rect.top = y * tileHeight;
      rect.height = tileHeight;
      rect.left = x * tileWidth;
      rect.width = tileWidth;

      subRects.push_back(rect);
    }

  // работа со слоями
  TiXmlElement *layerElement;
  layerElement = map->FirstChildElement("layer");
  while (layerElement) {
    Layer layer;

    // если присутствует opacity, то задаем прозрачность слоя, иначе он полностью непрозрачен
    if (layerElement->Attribute("opacity")) {
      double opacity = strtod(layerElement->Attribute("opacity"), nullptr);
      layer.opacity = 255 * (int) opacity;
    } else {
      layer.opacity = 255;
    }

    //  контейнер <data>
    TiXmlElement *layerDataElement;
    layerDataElement = layerElement->FirstChildElement("data");

    if (!layerDataElement) {
      std::cout << "Bad map. No layer information found." << std::endl;
    }

    //  контейнер <tile> - описание тайлов каждого слоя
    TiXmlElement *tileElement;
    tileElement = layerDataElement->FirstChildElement("tile");

    if (!tileElement) {
      std::cout << "Bad map. No tile information found." << std::endl;
      return false;
    }

    int x = 0;
    int y = 0;

    while (tileElement) {
      int tileGID = atoi(tileElement->Attribute("gid"));
      int subRectToUse = tileGID - firstTileID;

      // Устанавливаем TextureRect каждого тайла
      if (subRectToUse >= 0) {
        sf::Sprite sprite;
        sprite.setTexture(tilesetImage);
        sprite.setTextureRect(subRects[subRectToUse]);
        sprite.setPosition(x * tileWidth, y * tileHeight);
        sprite.setColor(sf::Color(255, 255, 255, (Uint8) layer.opacity));

        layer.tiles.push_back(sprite);//закидываем в слой спрайты тайлов
      }

      tileElement = tileElement->NextSiblingElement("tile");

      x++;
      if (x >= width) {
        x = 0;
        y++;
        if (y >= height)
          y = 0;
      }
    }

    layers.push_back(layer);

    layerElement = layerElement->NextSiblingElement("layer");
  }

  // работа с объектами
  TiXmlElement *objectGroupElement;

  // если есть слои объектов
  if (map->FirstChildElement("objectgroup")) {
    objectGroupElement = map->FirstChildElement("objectgroup");
    while (objectGroupElement) {
      //  контейнер <object>
      TiXmlElement *objectElement;
      objectElement = objectGroupElement->FirstChildElement("object");

      while (objectElement) {
        // получаем все данные - тип, имя, позиция, и тд
        std::string objectType;
        if (objectElement->Attribute("type")) {
          objectType = objectElement->Attribute("type");
        }
        std::string objectName;
        if (objectElement->Attribute("name")) {
          objectName = objectElement->Attribute("name");
        }
        int x = atoi(objectElement->Attribute("x"));
        int y = atoi(objectElement->Attribute("y"));

        int width, height;

        sf::Sprite sprite;
        sprite.setTexture(tilesetImage);
        sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
        sprite.setPosition(x, y);

        if (objectElement->Attribute("width")) {
          width = atoi(objectElement->Attribute("width"));
          height = atoi(objectElement->Attribute("height"));
        } else {
          width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
          height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
          sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
        }

        // экземпляр объекта
        Object object;
        object.name = objectName;
        object.type = objectType;
        object.sprite = sprite;

        sf::Rect<float> objectRect;
        objectRect.top = y;
        objectRect.left = x;
        objectRect.height = height;
        objectRect.width = width;
        object.rect = objectRect;

        // "переменные" объекта
        TiXmlElement *properties;
        properties = objectElement->FirstChildElement("properties");
        if (properties) {
          TiXmlElement *prop;
          prop = properties->FirstChildElement("property");
          if (prop) {
            while (prop) {
              std::string propertyName = prop->Attribute("name");
              std::string propertyValue = prop->Attribute("value");

              object.properties[propertyName] = propertyValue;

              prop = prop->NextSiblingElement("property");
            }
          }
        }

        objects.push_back(object);

        objectElement = objectElement->NextSiblingElement("object");
      }
      objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
    }
  } else {
    std::cout << "No object layers found..." << std::endl;
  }

  return true;
}

Object Level::GetObject(const std::string &name) {
  // только первый объект с заданным именем
  for (auto & object : objects) {
    if (object.name == name)
      return object;
  }
  exit(-1);
}

std::vector<Object> Level::GetObjects(const std::string &name) {
  // все объекты с заданным именем
  std::vector<Object> vec;
  for (auto & object : objects) {
    if (object.name == name)
      vec.push_back(object);
  }
  return vec;
}

std::vector<Object> Level::GetAllObjects() {
  return objects;
}

sf::Vector2i Level::GetTileSize() {
  return sf::Vector2i(tileWidth, tileHeight);
}

void Level::Draw(sf::RenderWindow &window) {
  // рисуем все тайлы (объекты не рисуем!)
  for (auto & layer : layers)
    for (size_t tile = 0; tile < layer.tiles.size(); tile++)
      window.draw(layer.tiles[tile]);
}

bool Level::increase_opaciti(int layNum, int inc) {
  int k = 3;
  if ((layNum + k < 0) || ((unsigned) layNum + k > layers.size())) {
    return false;
  }
//  int c = layers[layNum + k].opacity + inc;
  if ((layers[layNum + k].opacity + inc > 170) || (layers[layNum + k].opacity + inc <= 0)) {
    return false;
  }
  layers[layNum + k].opacity += inc;
  for (size_t tile = 0; tile < layers[layNum + k].tiles.size(); tile++) {
    layers[layNum + k].tiles[tile].setColor(sf::Color(255, 255, 255, (Uint8) layers[layNum + k].opacity));
  }
  return true;
}

int Level::get_layer_damage(int layNum) {
  int k = 3;
  if ((layNum + k < 0) || ((unsigned) layNum + k > layers.size())) {
    return -1;
  }
  return (layers[layNum + k].opacity);
}

