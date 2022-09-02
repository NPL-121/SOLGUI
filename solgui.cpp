#include <locale>
#include <codecvt>
#include <iostream>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include <FTGL/ftgl.h>
#include <time.h>
#include <wchar.h>
//#include <glm/glm.hpp>  // Включаем GLM
#include "solgui.h"


//const char *pathFont = "data/fonts/fabryka_4f_medium.ttf";
const char *pathFont = "data/fonts/TerminusTTF-4.47.0.ttf";

// Buttn ===========================================================================================================
Buttn::Buttn(float _x, float _y, float _a, float _b, 
                  double _mousex, double _mousey, std::string _mouse_state,
                  std::wstring _caption, 
                  const char *_path_font):
                   x(_x), y(_y), a(_a), b(_b), alpha(1.0), 
                   mousex(_mousex), mousey(_mousey), mouse_state(_mouse_state),
                   caption (_caption), path_font(_path_font) {};

void Buttn::draw() // Отрисовка кнопки
  {
     if (this->enabled) glColor3f(guiColorBase.x, guiColorBase.y, guiColorBase.z);   /* если едитбокс активен*/
     else glColor3f(guiColorBase.x*0.5f, guiColorBase.y*0.5f, guiColorBase.z*0.5f);  /* то цвет ярче, иначе темнее*/
     glBegin(GL_LINE_STRIP);
     glVertex2f(x, y);
     glVertex2f(x, y+b);
     glVertex2f(x+a, y+b);
     glVertex2f(x+a, y);
     glVertex2f(x, y);
     glEnd();
    
    FTGLPixmapFont font(path_font);
    font.CharMap(ft_encoding_unicode);
    font.FaceSize(iFontSize);

    glRasterPos2i(x+(a/2)-(iFontSize*caption.length()/4),y+(b/2)+5);
    wcstr = caption.c_str();
    
    font.Render(wcstr);

    
    
  }

// Проверка наличия курсора мыши над Buttn и действия при этом
void Buttn::MouseOn(double mousex, double mousey, std::string mouse_state)  
  {
    if (this->enabled) {
    // std::cout << mousex << std::endl;
     if ( (mousex > x) and (mousex < x+a) )
       {
       //  std::cout << "mouse X on bound" << std::endl; 
          if ( mousey > y  and mousey < y+b ) 
            {
              // std::cout << "mouse X and Y on bound" << std::endl;
               glColor4f(0.2,0.35,0.3,this->alpha);
               glBegin(GL_LINE_STRIP);
               glVertex2f(x+2, y+2);
               glVertex2f(x+2, y-2+b);
               glVertex2f(x-2+a, y-2+b);
               glVertex2f(x-2+a, y+2);
               glVertex2f(x+2, y+2);
               glEnd();
               if (mouse_state == "Left") // Если мышь на кнопке и нажата кнопка
                {
                 glColor4f(0.0,0.0,0.0,this->alpha); // Закрашивание черным
                 glBegin(GL_LINE_STRIP);             // имеющейся рамки
                  glVertex2f(x, y);                  // для эффекта нажатия
                  glVertex2f(x, y+b);
                  glVertex2f(x+a, y+b);
                  glVertex2f(x+a, y);
                  glVertex2f(x, y);
                 glEnd();

                 glColor3f(0.0,0.0,0.0);
                    glBegin(GL_QUADS); // Рисуем прямоугольник (фон EditBox)
                    glVertex2f(x, y+2);
                    glVertex2f(x, y+b-2);
                    glVertex2f(x+a-2, y+b-2);
                    glVertex2f(x+a-2, y+2);
                glEnd();
                      

                      glColor3f(0.3, 0.5, 0.45);
                      FTGLPixmapFont font(path_font); // Уменьшение
                      font.FaceSize(iFontSize*0.85);       // надписи
                      glRasterPos2i(x+(3*a/5)-(iFontSize*caption.length()/4),y+(b/2)+5);
                      wcstr = caption.c_str();
                      font.Render(wcstr); 

                 glColor4f(0.5,0.75,0.55,this->alpha); // Отрисовка новой рамки
                 glBegin(GL_LINE_STRIP);               // кнопки для эффекта
                  glVertex2f(x+5, y+5);                // нажатия
                  glVertex2f(x+5, y-5+b);
                  glVertex2f(x-5+a, y-5+b);
                  glVertex2f(x-5+a, y+5);
                  glVertex2f(x+5, y+5);
                 glEnd();
                  
                 state = true;
                }
            }
       }
   // if ( mousey > y  and mousey < y+b ) std::cout << "mouse Y on bound" << std::endl;
  }
}

  // <- Buttn /////////////////////////////////////////////////

// =================================================================================================================
// EditBox
void EditBox::draw() // Отрисовка editbox
  {
     changed_flag = false;
     
     // если длина текста дольше чем размер editbox.a
     // то, уменьшаем шрифт текста
        if (iFontSize*text.length()/2+7 > a) iFontSize--;
     // если шрифт меньше ширины-4, то с учетом вышестоящего условия,
     // увеличиваем шрифт
        if ((iFontSize+4 < b) and (iFontSize*text.length()/2+7 <= a)) iFontSize++;
     
     if (this->enabled) glColor3f(guiColorBase.x, guiColorBase.y, guiColorBase.z);   /* если едитбокс активен*/
     else glColor3f(guiColorBase.x*0.5f, guiColorBase.y*0.5f, guiColorBase.z*0.5f);  /* то цвет ярче, иначе темнее*/

     glBegin(GL_LINE_STRIP); // Рисуем контур
     glVertex2f(x, y);
     glVertex2f(x, y+b);
     glVertex2f(x+a, y+b);
     glVertex2f(x+a, y);
     glVertex2f(x, y);
     glEnd();
     

     glColor3f(0.05,0.1,0.15);
     glBegin(GL_QUADS); // Рисуем прямоугольник (фон EditBox)
     glVertex2f(x, y+2);
     glVertex2f(x, y+b-2);
     glVertex2f(x+a-2, y+b-2);
     glVertex2f(x+a-2, y+2);
     //glVertex2f(x, y);
     glEnd();

    if (this->enabled) glColor3f(guiColorBase.x, guiColorBase.y, guiColorBase.z);   /* если едитбокс активен*/
    else glColor3f(guiColorBase.x*0.5f, guiColorBase.y*0.5f, guiColorBase.z*0.5f);  /* то цвет ярче, иначе темнее*/
    
    FTGLPixmapFont font(path_font);
    font.FaceSize(iFontSize+2);  
    glRasterPos2i(x+4,y+(b/2)+4);
    cstr = text.c_str();
    font.Render(cstr);   
  }

// Проверка наличия курсора мыши над EditBox и действия при этом
void EditBox::MouseOn(double mousex, double mousey, short int wheel, std::string mouse_state, 
                      double duration_state, short int key)
{
    if (this->enabled){
     if ( mousex > x and mousex < x+a 
        and  mousey > y  and mousey < y+b ) // при наведении мыши
            {                                  // делаем фон чуть светлее
              glColor4f(0.1,0.15,0.25,this->alpha);
              glBegin(GL_QUADS); // Рисуем прямоугольник (фон EditBox)
              glVertex2f(x, y+2);
              glVertex2f(x, y+b-2);
              glVertex2f(x+a-2, y+b-2);
              glVertex2f(x+a-2, y+2);
              glEnd();
                  glColor4f(0.5,0.75,0.55,this->alpha); // Пишем текст
                  FTGLPixmapFont font(path_font);
                  font.FaceSize(iFontSize+2);  
                  glRasterPos2i(x+4,y+(b/2)+4);
                  cstr = text.c_str();
                  font.Render(cstr);

              if (mouse_state == "Left")  // Если нажата кнопка мыши
                {
                   //std::cout << "LBM pressed on control elements" << std::endl; // отладка
                   state = true;
          // момент времени от старта программы, принимаемый за точку отсчета в цикле
          // моргания каретки
                   timer_start = duration_state;
                   
                   glColor4f(0.9,0.9,1.0,this->alpha);
                   glBegin(GL_LINE_STRIP); // Рисуем каретку
                   glVertex2f(x+2+iFontSize*text.length()/2 + 2, y+2);
                   glVertex2f(x+2+iFontSize*text.length()/2 + 2, y+b-2);
                   glEnd(); 
                }
             // wheel's change value 
             if ( num_wheel == true && wheel == 1 )
              {
                //std::cout << "mouse wheel up"<< std::endl;
                double num = atof(this->text.c_str());
                if (this->type_num == 0) { // double
                  num = num + 0.01f * multiply;
                  short int precisionVal = 2; // точность
                  this->text = std::to_string(num).substr(0, std::to_string(num).find(".") + precisionVal + 1);
                }
              }
             if ( num_wheel == true && wheel == -1 )
              {
                //std::cout << "mouse wheel down"<< std::endl;
                double num = atof(this->text.c_str());
                if (this->type_num == 0) { // double
                  num = num - 0.01f * multiply;
                  short int precisionVal = 2; // точность
                  this->text = std::to_string(num).substr(0, std::to_string(num).find(".") + precisionVal + 1);
                }
              }
       }
    else       // Нажитие кнопки мыши за пределами EditBox, прерывает режим редактирования
        if (mouse_state == "Left") 
        {
         //std::cout << "LBM pressed" << std::endl; // отладка
         this->state = false;
        }

    /// если нажали кнопку мыши, то переходим в режим редактирования (state == true),
    /// включаем моргание каретки, перехватываем нажатия кнопок
    if (state == true)   
       {
         // таймер каретки, зависящий от времени работы программы и от момента
         // нажатия на editbox (момент state == true)
         double timer = duration_state - timer_start; 
            // std::cout << timer << std::endl; // отладочный вывод
         if (timer <= 1.0) //Рисуем каретку
         {
          glColor4f(0.9,0.9,1.0,this->alpha);
          glBegin(GL_LINE_STRIP);
          glVertex2f(x+2+iFontSize*text.length()/2 + 2, y+2);
          glVertex2f(x+2+iFontSize*text.length()/2 + 2, y+b-2);
          glEnd();
         }
         if (timer > 1.0 and timer <= 1.5)
         {
          glColor4f(0.1,0.15,0.25,this->alpha);  
          glBegin(GL_LINE_STRIP); // Затираем каретку фоном
          glVertex2f(x+2+iFontSize*text.length()/2 + 2, y+2);
          glVertex2f(x+2+iFontSize*text.length()/2 + 2, y+b-2);
          glEnd();
         }
         if (timer > 1.5) timer_start = duration_state;
 
       // перехват нажатия кнопок
          
          if (key == 100 ) // если ничего не нажато
          {
           // std::cout << key << std::endl; // отладка
          }
          else // если нажата кнопка то проверяем какая и выполняем
          { 
            //std::cout << key << std::endl; // отладка
            if (key == 199) // Удаление последнего символа
               {
   
                  if (timer <= 0.03) //Добавляем addtext к имеющемся text
                    {   
                     text.erase(text.end()-1); // стираем последний символ в строке
                     if (text =="") text = "0";
                     //std::cout << key << std::endl; // отладка
                    }
                  if (timer > 0.03 and timer <= 0.1)
                  {
                     key = 100; // присваеваем "ничего не нажато"
                  }
                  if (timer > 0.1) timer_start = duration_state;
              }
              
              addtext ="0";
              if (key != 100)
              {
              bool edit = false;
              switch (key)  // добавляем символ
              {
                 case 0 : addtext = "0"; edit = true; break;
                 case 1 : addtext = "1"; edit = true; break;
                 case 2 : addtext = "2"; edit = true; break;
                 case 3 : addtext = "3"; edit = true; break;
                 case 4 : addtext = "4"; edit = true; break;
                 case 5 : addtext = "5"; edit = true; break;
                 case 6 : addtext = "6"; edit = true; break;
                 case 7 : addtext = "7"; edit = true; break;
                 case 8 : addtext = "8"; edit = true; break;
                 case 9 : addtext = "9"; edit = true; break;
                 case 99 : addtext = "."; edit = true; break;
              }

              
              //std::cout << addtext << std::endl; // отладка

              if (edit == true)
              {
                 if (timer <= 0.03) //Добавляем addtext к имеющемся text
                  {    
                        if ((text == "0") and (addtext == ".")) text = "0.";
                        else
                        if (text == "0") text = addtext;
                        else
                        text = text + addtext;
                        //std::cout << addtext << std::endl; // отладка
                  }
                  if (timer > 0.03 and timer <= 0.1)
                  {
                     key = 100; // присваеваем "ничего не нажато"
                  }
                  if (timer > 0.1) timer_start = duration_state;
                
                edit = false;
              }     
          }
         }
                   
       }
   }    
}
// <- EditBox /////////////////////////////////////////////////

//===============================================================================
// Caption
void Caption::draw()
{
    FTGLPixmapFont font(path_font);
    font.CharMap(ft_encoding_unicode);
    font.FaceSize(iFontSize);

    glRasterPos2i(x,y);
    wcstr = caption.c_str();
    
    font.Render(wcstr);
}