#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "log.h"


class Window
{
public:
    Window(std::string title, int width, int height);
    virtual ~Window();

    double getDelta() const;
    void getMousePosition(int& x, int& y) const;
    void getMouseDelta(int& dx, int& dy) const;
    int  getHeight() const;
    int getWidth() const;
    bool isOpen()const;
    bool update();
    void clear(float red, float green, float blue, float alpha);
    //Possible key states
    enum KeyState {JUST_DOWN, DOWN, UP};
private:
    //Number of possible keys
    static const int KNUM = 512;
    //Frames per second caps
    static const int FPS = 60;

    //if window is open
    bool          m_isOpen;

    //each sdlkey is mapped to a keystate
    KeyState m_keymap[KNUM];

    // number of frames between updates and previous ticks
    unsigned int m_time, m_ptime;

    // milliseconds between window updates
    double m_timeDelta;

    // mouse positions and previous positions
    int m_mouseX, m_mouseY,m_pmouseX, m_pmouseY;

    // window dimensions
    int m_width, m_height;

    //  Handle to SDL window to query opengl and OS events
    SDL_Window*     m_sdlWindow;

    //  Handle to SDL events, member to reduce reallocating on call stack
     SDL_Event*      m_sdlEvent;

    // OpengGL Context that will handle drawing to the screen
    SDL_GLContext  m_glContext;
};

#endif // WINDOW_H
