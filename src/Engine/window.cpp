#include "window.h"

Window::Window(std::string title, int width, int height)
{

        if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
            error() << "Window:" << "SDL Failed to initialize!";
        m_sdlWindow = SDL_CreateWindow(title.c_str(),
                                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    width, height, SDL_WINDOW_OPENGL);
        m_glContext = SDL_GL_CreateContext(m_sdlWindow);
        if(glewInit() != GLEW_OK)
            error() << "Window:"  << "GLEW Failed to initialize";
        else{
            m_isOpen = true;
            glewExperimental = true;
            //Initialize opengl color attributes buffer size
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 2);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32); //very deep buffer

            m_width = width;
            m_height= height;
            m_mouseX = m_mouseY = m_pmouseX = m_pmouseY = 0;
            for(int i=0; i < KNUM; i++)
                m_keymap[i] = UP;
            m_time = m_ptime = 0;

        }
}
Window::~Window()
{
    //destroy context then window
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_sdlWindow);
    SDL_Quit();
}

//Accessors
bool Window::isOpen() const
{
    return m_isOpen;
}

double Window::getDelta() const
{
    return m_timeDelta;
}


void Window::getMousePosition(int& x, int& y) const
{
    x = m_mouseX;
    y = m_mouseY;
}

void Window::getMouseDelta(int& dx, int& dy) const
{
    dx = m_pmouseX - m_mouseX;
    dy = m_pmouseY - m_mouseY;
}
int Window::getWidth() const
{
    return m_width;
}
int Window::getHeight() const
{
    return m_height;
}


void Window::clear(float red, float green, float blue, float alpha)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(red,green,blue,alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::update()
{
     m_ptime = m_time;

    //swap render and display buffers
    SDL_GL_SwapWindow(m_sdlWindow);

    //Poll input events
    SDL_Event event;
    m_pmouseX = m_mouseX;
    m_pmouseY = m_mouseY;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            m_isOpen = false;
        else if (event.type == SDL_MOUSEMOTION)
        {
            int x= event.motion.x, y= event.motion.y;
            if(x > 0 && x < m_width)
                m_mouseX= x;
            if(y > 0 && y < m_height)
                m_mouseY= y;
        }
        else if (event.type == SDL_KEYUP)
        {
            m_keymap[event.key.keysym.sym] = UP;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            int keysym = event.key.keysym.sym;
            switch (keysym)
            {
            case SDLK_ESCAPE:
                m_isOpen = false;
                break;
            default:
                //if was previously down
                if(m_keymap[keysym]==JUST_DOWN)
                    m_keymap[event.key.keysym.sym] = DOWN;
                else
                    m_keymap[event.key.keysym.sym] = JUST_DOWN;
                break;
            }
        }
    }
    //delay
//    if (SDL_GetTicks() - m_time < 1000.0/FPS)
//          SDL_Delay(1000/FPS - (SDL_GetTicks() - m_time));
//    m_timeDelta = (double)((SDL_GetTicks()  - m_ptime)*1000 / SDL_GetPerformanceFrequency() );
    m_time = SDL_GetTicks();
    return m_isOpen;
}
