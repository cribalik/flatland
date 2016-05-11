//
// Created by cmarte on 5/31/15.
//

#include "Menu.h"
#include "Game.h"

class MenuModel {
public:
    typedef std::tuple<std::string, fl::Action> Item;
private:
    int top = 300, bottom = 900, _x = 960, _w = 100;
    std::size_t num_items = 3, curr = 0;
    std::vector<Item> items;
public:
    MenuModel(const std::vector<Item>& items, int top = 300, int bottom = 900) :  top(top), bottom(bottom), items(items) {}
    void next() {++curr; curr %= num_items;}
    void prev() {curr = curr == 0? num_items-1 : curr-1;}
    int y() {return top + (curr*(bottom-top))/num_items;}
    int x() {return _x;}
    int& w() {return _w;}
    std::size_t numItems() {return items.size();}
    fl::Action getAction() {return std::get<1>(items[curr]);}
    std::string name() {return std::get<0>(items[curr]);}
};

class MenuSelector : public fl::InputHandler {
public:
    fl::SpriteHandle marker;
    MenuModel menu;
    MenuSelector(const MenuModel& model) : menu(model) {}
    virtual void init(fl::EntityWrapper e, fl::InputHandle h) {
        using namespace fl;
        SpriteOptions opt = e.getSpriteOptions(marker);
        opt.offset.x = menu.x() - menu.w() / 2.;
        opt.offset.y = menu.y();
        e.setSpriteOptions(marker, opt);
    }
    virtual void buttonUp(fl::EntityWrapper e, fl::InputHandle, fl::Button b) {}
    virtual void buttonDown(fl::EntityWrapper e, fl::InputHandle, fl::Button b) {
        using namespace fl;
        /* Run action on selected item */
        if (b == Button::A) {
            menu.getAction()(e);
            return;
        }

        /* Move selection */
        if (b == Button::DOWN) menu.next();
        else if (b == Button::UP) menu.prev();
        else return;

        /* Move marker */
        SpriteOptions opt = e.getSpriteOptions(marker);
        opt.offset.x = menu.x() - menu.w() / 2.;
        opt.offset.y = menu.y();
        e.setSpriteOptions(marker, opt);
    }
    virtual void destroy(fl::EntityWrapper e, fl::InputHandle) {delete this;}
};

class FloatyEffect : public fl::Updatable {
    fl::SpriteHandle target;
    double amp;
    double alpha = 0;
    double speed = 3.;
public:
    FloatyEffect(fl::SpriteHandle target, double amplitude = 10.) : target(target), amp(amplitude) {}
    virtual void updateInit(fl::EntityWrapper) {}
    virtual void updateDestroy(fl::EntityWrapper) {delete this;}
    void update(fl::EntityWrapper e, fl::Time dt) {
        alpha += dt * speed / 360.;
        fl::SpriteOptions s = e.getSpriteOptions(target);
        s.offset.y += amp * (sin(alpha + dt*speed/360.) - sin(alpha));
        s.offset.x += amp * (cos(alpha + dt*speed/360.) - cos(alpha));
        e.setSpriteOptions(target, s);
    }
};

Menu* Menu::Create(Game& game) {
    using namespace fl;

    auto e = game.getWorld().createEntity();

    MenuModel menu(
            {
                    MenuModel::Item {"New Game", newGame},
                    MenuModel::Item {"Continue", fl::action::destroyEntity},
                    MenuModel::Item {"Exit", fl::action::exitProgram}
            }
    );
    menu.w() = 400;
    MenuSelector* selector = new MenuSelector(menu);
    selector->marker = e.addSpriteComponent(fl::SpriteOptions("/home/cmarte/Downloads/shine.png", Box{100, 100}));

    /* Draw text for menu items */
    for (int i = 0; i < menu.numItems(); ++i) {
        TextOptions topt;
        topt.text = selector->menu.name();
        topt.offset = fl::Point {(double) selector->menu.x(), (double) selector->menu.y()};
        e.addTextComponent(topt);
        selector->menu.next();
    }
    e.addInputComponent(InputOptions(InputOptions::FIRST_FREE, selector));
    /* Add a floating effect on the marker */
    e.addUpdateListener(new FloatyEffect(selector->marker));

    return new Menu(game, e);
};


void Menu::newGame(fl::EntityWrapper e) {
    Menu* menu = e.getLogic<Menu>();
    menu->game().startLevel(Level::Create(menu->game(), "/home/cmarte/ClionProjects/flatland/Game/res/Levels/level1.lv"));
    menu->destroy();
}
