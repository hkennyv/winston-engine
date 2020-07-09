#ifndef ENTITY_H
#define ENTITY_H

#include "./Constants.h"
#include "./Component.h"
#include "./EntityManager.h"
#include <map>
#include <string>
#include <vector>

class EntityManager;
class Component;

class Entity {
private:
  EntityManager &manager;
  bool isActive;
  std::vector<Component *> components;
  std::map<const std::type_info *, Component *> componentTypeMap;

public:
  std::string name;
  LayerType layer;

  Entity(EntityManager &manager);
  Entity(EntityManager &manager, std::string name, LayerType layer);
  void Update(float deltaTime);
  void Render();
  void Destroy();
  bool IsActive() const;
  void ListAllComponents() const;

  // templates in c++
  // http://www.cplusplus.com/doc/oldtutorial/templates/
  template <typename T, typename... Targs> T &AddComponent(Targs &&... args) {
    T *component(new T(std::forward<Targs>(args)...));
    component->owner = this;
    components.emplace_back(component);
    componentTypeMap[&typeid(*component)] = component;
    component->Initialize();

    return *component;
  };

  template <typename T> bool HasComponent() const {
    return componentTypeMap.count(&typeid(T));
  }

  // want to keep track of the types of the components
  template <typename T> T *GetComponent() {
    return static_cast<T *>(componentTypeMap[&typeid(T)]);
  }

  // // check if we have a component
  // template <typename T> bool HasComponent() const {
  //   return componentTypeMap.find(&typeid(T)) == componentTypeMap.end();
  // }
};

#endif
