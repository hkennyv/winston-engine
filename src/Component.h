#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Entity;

class Component {
private:

public:
    Entity* owner;

    std::string name;

    virtual ~Component() {}
    virtual void Initialize() {}
    virtual void Update(float deltaTime) {}
    virtual void Render() {}
};

#endif
