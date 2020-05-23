#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include "./Component.h"
#include "./EntityManager.h"

class EntityManager;
class Component;

class Entity {
private:
    EntityManager& manager;
    bool isActive;
    std::vector<Component*> components;

public:
    std::string name;
    Entity(EntityManager& manager);
    Entity(EntityManager& manager, std::string name);
    void Update(float deltaTime);
    void Render();
    void Destroy();
    bool IsActive() const;

    // templates in c++
    // http://www.cplusplus.com/doc/oldtutorial/templates/
    template <typename T, typename... Targs>
    T& AddComponent(Targs&&... args) {
        T* component(new T(std::forward<Targs>(args)...));
        component->owner = this;
        components.emplace_back(component);
        component->Initialize();

        return *component;
    };
};

#endif
