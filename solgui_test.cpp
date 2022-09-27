//
//
//

#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#define GLEW_STATIC     // для статической линковки
#include <GLFW/glfw3.h>
#include <FTGL/ftgl.h>
#include <clocale>
#include <time.h>
#include <iostream>
//#include "solgui.cpp"

// Включаем GLM
//#include <glm/glm.hpp>
#include "solgui.h"
//using namespace glm;


//////////////////////////////////////////////////////////////
// Глобальные переменные
// ->
    int windowWidth = 1280;    // Размер окна
    int windowHeight = 600;   // Размер окна
    double duration;   // Счетчик времени программы
    double mouse_x, mouse_y; // Координаты мыши
    std::string mouse_but_state;
    std::wstring temp_caption;
    double time_start; // Момент запуска программы
    FTGLPixmapFont font("data/fonts/isocpeur_regular.ttf");

    //bool edit_str; // проверка редактирования editbox
    // std::string key_press;    // глобальная переменная нажатия кнопок
    short int key_press;               // глобальная переменная нажатия кнопок
    std::string temp_str; // временная строка для хранения данных при редакторовании
    short int wheel_mouse = 0; //глобальная переменная мышинного колеса
    bool lbutton_down;          // нажата ли кнопка мыши
    short int x, y;            // временные текущие координаты
    
    float scale = 1.0;
// <-
//////////////////////////////////////////////////////////////

// Создаем объекты классов
// -> 
  // кнопки
Buttn b1(10, 400, 80, 20, mouse_x, mouse_y, mouse_but_state, L"button1");
Buttn b2(10, 490, 80, 20, mouse_x, mouse_y, mouse_but_state, L"Кнопка_2");

 // едитбокс
EditBox e1(10, 430, 80, 20, mouse_x, mouse_y, wheel_mouse, mouse_but_state, "30");
EditBox e2(10, 460, 80, 20, mouse_x, mouse_y, wheel_mouse, mouse_but_state, "15");

// Caption
Caption capt1(200, 200, L"Тестовое сообщение");
Caption capt2(20, 160, L"Events = ");

//SpinButtn
SpinButtn SpB1(300, 300, 10.0, 1.0);
SpinButtn SpB2(320, 300, 10.0, 1.0);

//ComboBox
ComboBox CB1(20, 190);

//Slider
Slider S1(10, 250, 150);



// Error
void error ( int error, const char * description )
{
    fputs ( description, stderr );
}

// Проверка состояния нажатия кнопок
void key ( GLFWwindow * window, int key, int scancode, int action, int mods )
{
    if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS ) // ESC
        glfwSetWindowShouldClose ( window, GL_TRUE );
  

   key_press = 100; // означает "ничего не нажато"

   if ( key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS) 
        key_press = 199; 
   if ( key == GLFW_KEY_0 && action == GLFW_PRESS) 
        key_press = 0;
   if ( key == GLFW_KEY_1 && action == GLFW_PRESS) 
        key_press = 1;
   if ( key == GLFW_KEY_2 && action == GLFW_PRESS) 
        key_press = 2;
   if ( key == GLFW_KEY_3 && action == GLFW_PRESS) 
        key_press = 3;
   if ( key == GLFW_KEY_4 && action == GLFW_PRESS) 
        key_press = 4;
   if ( key == GLFW_KEY_5 && action == GLFW_PRESS) 
        key_press = 5;
   if ( key == GLFW_KEY_6 && action == GLFW_PRESS) 
        key_press = 6;
   if ( key == GLFW_KEY_7 && action == GLFW_PRESS) 
        key_press = 7;
   if ( key == GLFW_KEY_8 && action == GLFW_PRESS) 
        key_press = 8;
   if ( key == GLFW_KEY_9 && action == GLFW_PRESS) 
        key_press = 9;
   if ( key == GLFW_KEY_KP_DECIMAL && action == GLFW_PRESS) 
        key_press = 99;
   if ( key == GLFW_KEY_COMMA && action == GLFW_PRESS) 
        key_press = 99;
   if ( key == GLFW_KEY_PERIOD && action == GLFW_PRESS) 
        key_press = 99;
    
}
// Мышь, проверка состояния кнопок
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        mouse_but_state = "Right";
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        mouse_but_state = "Left";
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
        mouse_but_state = "Middle";
    if (action != GLFW_PRESS) mouse_but_state = "";
}
// Мышь, проверка колеса
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//std::cout << "mouse wheel = " << yoffset << std::endl; //отладка
    if (yoffset < 0) wheel_mouse = -1;
    else wheel_mouse = 1;
}
/// Мышь, проверка драга
void mouse_cursor_callback( GLFWwindow * window, double xpos, double ypos)  
{  

  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
  {
     return;
  }

  // `write your drag code here`
  /*if (desk1.on_mouse == true)
  {
    world1.x1 = mouse_x;
    world1.y1 = mouse_y;
  }*/
}

void setParamsGUI()
{
    //e1.enabled = false;
    e1.step = 0.1;       //кратность изменения параметра
    e2.step = 1.0;       //кратность изменения параметра

    // Изменение пределов изменения числа (default min = 0, max = 1000)
    e1.maxCounter = 35;
    e1.minCounter = -1;

    //b1.enabled = false;

    b1.iFontSize = 16;
    b2.iFontSize = 16;

    // изменение дефолтного шрифта
    capt1.path_font = "data/fonts/neuropol_medium.ttf";

    capt2.path_font = "data/fonts/isocpeur_regular.ttf";
    capt2.iFontSize = 18;

    //изменение дефолтного цвета
    capt1.setColor(0.2, 0.7, 0.4);
    

    // attach Spinbutton, присоединение spinbutton к editbox
    e1.attach(SpB1);
    e2.attach(SpB2);

    // добавление в ComboBox строк
    CB1.addString(L"Первая строка");
    CB1.addString(L"Green color");
    CB1.addString(L"third string");
    CB1.addString(L"синий цвет");
    //CB1.caption=L"Caption";
        // отладка
        //CB1.printString();
    
}

// Настройка свойств OpenGL
void Init ()  
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, windowWidth, windowHeight, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
////////////////////////////


// Отрисовка главной сцены
void display_text ( GLFWwindow * window )
{
    char buff[100];
    const char *cstr;
        
    glColor3f(1.0,1.0,1.0);
    font.FaceSize(18);
    glRasterPos2i(20,80);
    font.Render("deltaT = ");
    glRasterPos2i(100,80);
       sprintf (buff, "%f", duration*1.0); // перевод duration из double в char
    font.Render(buff);

    glColor3f(1.0,1.0,1.0);
    // Вывод координат курсора мыши
    glRasterPos2i(20,100);
    font.Render("Mouse = ");
       sprintf (buff, "%g", mouse_x); // перевод mouse_x из double в char
    glRasterPos2i(90,100);
    font.Render(buff);
       sprintf (buff, "%g", mouse_y); // перевод mouse_y из double в char
    glRasterPos2i(140,100);
    font.Render(buff);

    // Вывод нажатия кнопок мыши
    glRasterPos2i(20,120);
    font.Render("Mouse button state = ");
    glRasterPos2i(200,120);
     cstr = mouse_but_state.c_str(); // Преобразование string в char
    font.Render(cstr);


    // Рисуем квадрат
    glLoadIdentity();
    glTranslatef(windowWidth/40, windowHeight/17, 0.0f);
    glRotatef(duration*10.0f,0.0f,0.0f,1.0f);         // и вращаем его
    glColor3f(0.1,0.1,0.9);
     glBegin(GL_QUADS);
      glVertex2f(-20.0f, -20.0f);
      glVertex2f(-20.0f, 20.0f);
      glVertex2f(20.0f, 20.0f);
      glVertex2f(20.0f, -20.0f);
     glEnd();
    glLoadIdentity();
    
   // Отрисовка классов
    
    //glColor4f(0.5,0.75,0.7,1.0);// задаём цвет
    b1.draw(); // buttn
    b2.draw();

    e1.draw(); // отрисовка editbox1
    e1.getSpinButtnState(SpB1); // получение параметров spinbutton
    e2.draw(); // отрисовка editbox2
    e2.getSpinButtnState(SpB2);

    capt1.draw(); // caption
    capt2.draw();

    SpB1.draw();  // spinbutton
    SpB2.draw(); 

    CB1.draw(); // ComboBox

    S1.draw();  // Slider

    // Проверка взаимодействия с мышью элементов интерфейса
    b1.MouseOn(mouse_x, mouse_y, mouse_but_state);
    b2.MouseOn(mouse_x, mouse_y, mouse_but_state);
    e1.MouseOn(mouse_x, mouse_y, wheel_mouse, mouse_but_state, duration, key_press);
    e2.MouseOn(mouse_x, mouse_y, wheel_mouse, mouse_but_state, duration, key_press);
    SpB1.MouseOn(mouse_x, mouse_y, mouse_but_state, duration);
    SpB2.MouseOn(mouse_x, mouse_y, mouse_but_state, duration);
    CB1.MouseOn(mouse_x, mouse_y, wheel_mouse, mouse_but_state, duration);
    

    // что происходит при нажатии кнопок b1, b2 и т.д.
    if (b1.state == true) 
     {
       temp_caption =  L"button 1 pressed";
       b1.state = false;
     }
    if (b2.state == true) 
     {
       b2.state = false;
       temp_caption = L"button 2 pressed";
       capt1.caption = L"Динамическое изменение";
     }

     capt1.iFontSize = atof(e2.text.c_str()); /* изменение размера шрифта 
                                                 через изменение текста в editbox e1 */

     capt2.caption = L"Events = " + temp_caption;

    // изменение в комбобоксе     
    if (CB1.index_list == 3) { 
        capt1.colorRed = 0.2;
        capt1.colorGreen = 0.4;
        capt1.colorBlue = 0.75;
     }
    if (CB1.index_list == 1) { 
        capt1.colorRed = 0.2;
        capt1.colorGreen = 0.8;
        capt1.colorBlue = 0.3;
     }

    wheel_mouse = 0; //сбрасывеам состояние колеса мыши на ноль
}

long mtime() // Функция получения момента времени
{
  struct timespec t;
  clock_gettime(CLOCK_REALTIME, &t);
  long mt = (long)t.tv_sec*1000 + t.tv_nsec/1000000;
  return mt;
}


int main ()
{
   // получаем момент времени запуска программы
   time_start = mtime();

   key_press = 100;
    glfwSetErrorCallback ( error );
    
    if ( !glfwInit() )
        exit ( 1 );
    
    GLFWwindow * window = glfwCreateWindow ( windowWidth, windowHeight, "Прототип простого GUI", NULL, NULL );
    
    if ( !window )
    {
        glfwTerminate ();
        exit ( 1 );
    }

    glfwMakeContextCurrent ( window );
    glfwSwapInterval       ( 1 );
    glfwSetKeyCallback     ( window, key);

    setParamsGUI(); // установка начальных параметров GUI


    while ( !glfwWindowShouldClose ( window ) )
    {
        Init();
        glfwGetCursorPos(window, &mouse_x, &mouse_y); // Получение координат курсора
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        mouse_cursor_callback(window, mouse_x, mouse_y);
        glfwSetScrollCallback(window, scroll_callback);
        duration = ( mtime() - time_start ) / 1000; // Счетчик времени, сек
        display_text ( window );
        glfwSwapBuffers ( window );
        glfwPollEvents  ();
    }
    
    glfwDestroyWindow ( window );
    glfwTerminate     ();
    
    return 0;
}
