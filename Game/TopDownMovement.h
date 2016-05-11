//
// Created by cmarte on 6/9/15.
//

#ifndef FLATLAND_TOPDOWNMOVEMENT_H
#define FLATLAND_TOPDOWNMOVEMENT_H


#include <InputSystem.h>

class TopDownMovement : public fl::InputHandler {

    TopDownMovement() {};
public:
    virtual void init(fl::EntityWrapper wrapper, fl::InputHandle handle);

    virtual void buttonDown(fl::EntityWrapper wrapper, fl::InputHandle handle, fl::Button button);

    virtual void buttonUp(fl::EntityWrapper wrapper, fl::InputHandle handle, fl::Button button);

    virtual void destroy(fl::EntityWrapper wrapper, fl::InputHandle handle);

    static TopDownMovement* Create();
};


#endif //FLATLAND_TOPDOWNMOVEMENT_H
