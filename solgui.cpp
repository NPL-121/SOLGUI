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
                    glBegin(GL_QUADS); // Рисуем прямоугольник (фон )
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
                  num = num + step;
                  if (num < minCounter) num = minCounter;
                  if (num > maxCounter) num = maxCounter;
                  short int precisionVal = 2; // точность
                  this->text = std::to_string(num).substr(0, std::to_string(num).find(".") + precisionVal + 1);
                }
              }
             if ( num_wheel == true && wheel == -1 )
              {
                //std::cout << "mouse wheel down"<< std::endl;
                double num = atof(this->text.c_str());
                if (this->type_num == 0) { // double
                  num = num - step;
                  if (num < minCounter) num = minCounter;
                  if (num > maxCounter) num = maxCounter;
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

void EditBox::attach(SpinButtn &spButtn)
{
  spButtn.height = this->b;
  spButtn.width = this->b;
  spButtn.x = this->x + this->a;
  spButtn.y = this->y;
  spButtn.step = this->step;
  spButtn.sValue = this->text;
  spButtn.minCounter = this->minCounter;
  spButtn.maxCounter = this->maxCounter;

  this->attached = true;
  spButtn.attach(*this);

}

void EditBox::getSpinButtnState(SpinButtn &spButtn)
{
  if (spButtn.changed) {
    //std::cout << "ButtnState changed" << std::endl;
    this->text = spButtn.sValue;
  }
  if (this->attached) {
    spButtn.sValue = this->text;
  }
}

// <- EditBox /////////////////////////////////////////////////

//==================================================================================================================
// SpinButtn
void SpinButtn::draw()
{
  if (this->enabled) glColor3f(guiColorBase.x, guiColorBase.y, guiColorBase.z);   /* если едитбокс активен*/
    else glColor3f(guiColorBase.x*0.5f, guiColorBase.y*0.5f, guiColorBase.z*0.5f);  /* то цвет ярче, иначе темнее*/
  
  glBegin(GL_LINE_STRIP); // Рисуем контур
     glVertex2f(x, y);
     glVertex2f(x, y+this->height);
     glVertex2f(x+this->width, y+this->height);
     glVertex2f(x+this->width, y);
     glVertex2f(x, y);
  glEnd();
  glBegin(GL_LINE_STRIP); // Рисуем разделение кнопок
     glVertex2f(x, y+this->height*0.5f);
     glVertex2f(x+this->width, y+this->height*0.5f);
  glEnd();
  glBegin(GL_TRIANGLES); // треугольник значок "вверх"
     glVertex2f(x+this->width*0.75f, y+this->height*0.1f); 
     glVertex2f(x+this->width*0.9f, y+this->height*0.4f);
     glVertex2f(x+this->width*0.6f, y+this->height*0.4f);
  glEnd();
  glBegin(GL_TRIANGLES); // треугольник значок "вниз"
     glVertex2f(x+this->width*0.25f, y+this->height*0.9f); 
     glVertex2f(x+this->width*0.1f, y+this->height*0.6f);
     glVertex2f(x+this->width*0.4f, y+this->height*0.6f);
  glEnd();
}

void SpinButtn::MouseOn(double mousex, double mousey, std::string mouse_state, 
                        double duration_state)
{
    if (this->enabled){
      if ( mousex > x and mousex < x+this->width       // верхняя кнопка
        and  mousey > y  and mousey < y+height*0.5f ) // при наведении мыши
            {
                //std::cout << "SpinButton on mouse" << std::endl;
                glColor3f(0.2,0.35,0.3);
                glBegin(GL_LINE_STRIP); // Рисуем контур верхней кнопки
                  glVertex2f(x+2, y+2);
                  glVertex2f(x+2, y+this->height*0.5f-2);
                  glVertex2f(x+2+this->width-4, y+this->height*0.5f-2);
                  glVertex2f(x+2+this->width-4, y+2);
                  glVertex2f(x+2, y+2);
                glEnd();

                this->changed = false;
              
                if (mouse_state == "Left") // Если мышь на кнопке и нажата кнопка
                {
                  glColor3f(0.0,0.0,0.0);             // Закрашивание черным
                  glBegin(GL_LINE_STRIP);             // имеющейся рамки
                    glVertex2f(x, y);                  // для эффекта нажатия
                    glVertex2f(x+this->width, y);
                    glVertex2f(x+this->width, y+this->height*0.5f);
                  glEnd();

                  glColor3f(0.0,0.0,0.0);
                  glBegin(GL_QUADS); // Рисуем прямоугольник (фон )
                    glVertex2f(x+2, y+2);
                    glVertex2f(x+2, y+this->height*0.5f-2);
                    glVertex2f(x+2+this->width-4, y+this->height*0.5f-2);
                    glVertex2f(x+2+this->width-4, y+2);
                  glEnd();

                  glColor3f(0.3, 0.5, 0.45);           // Отрисовка новой рамки
                  glBegin(GL_LINE_STRIP);              // кнопки для эффекта
                    glVertex2f(x+2, y+2);              // нажатия
                    glVertex2f(x+2, y-2+this->height*0.5f);
                    glVertex2f(x-2+this->width, y-2+this->height*0.5f);
                    glVertex2f(x-2+this->width, y+2);
                    glVertex2f(x+2, y+2);
                  glEnd();

                  glColor3f(0.3, 0.5, 0.45);
                  glBegin(GL_TRIANGLES); // треугольник значок "вверх"
                    glVertex2f(x+this->width*0.75f*0.9f, y+this->height*0.1f*0.9f); 
                    glVertex2f(x+this->width*0.9f*0.9f, y+this->height*0.4f*0.9f);
                    glVertex2f(x+this->width*0.6f*0.9f, y+this->height*0.4f*0.9f);
                  glEnd();

                  
                  double timer = duration_state - timer_start; //таймер для замедления ввода
                  // std::cout << timer << std::endl; // отладочный вывод
                  if (timer <= 0.03) //
                  {
                    //изменение параметра;
                    double num = atof(this->sValue.c_str());
                    num = num + step;
                    if (num < minCounter) num = minCounter;
                    if (num > maxCounter) num = maxCounter;
                    short int precisionVal = 2; // точность
                    this->sValue = std::to_string(num).substr(0, std::to_string(num).find(".") + precisionVal + 1);
                    this->value = num;
                    this->changed = true;
                  }
                  if (timer > 0.1) timer_start = duration_state;
                }

            }
      if ( mousex > x and mousex < x+this->width       // нижняя кнопка
        and  mousey > y+height*0.5f and mousey < y+height*1.0f ) // при наведении мыши
            {
                //std::cout << "SpinButton on mouse" << std::endl;
                glColor3f(0.2,0.35,0.3);
                glBegin(GL_LINE_STRIP); // Рисуем контур нижней кнопки
                  glVertex2f(x+2, y+this->height*0.5f+2);
                  glVertex2f(x+2, y+this->height*1.0f-2);
                  glVertex2f(x+2+this->width-4, y+this->height*1.0f-2);
                  glVertex2f(x+2+this->width-4, y+this->height*0.5f+2);
                  glVertex2f(x+2, y+this->height*0.5f+2);
                glEnd();

                this->changed = false;

                if (mouse_state == "Left") // Если мышь на кнопке и нажата кнопка
                {
                  glColor3f(0.0,0.0,0.0);             // Закрашивание черным
                  glBegin(GL_LINE_STRIP);             // имеющейся рамки           
                    glVertex2f(x, y+this->height);    // для эффекта нажатия
                    glVertex2f(x+this->width, y+this->height);
                    glVertex2f(x+this->width, y+this->height*0.5f);
                  glEnd();

                  glColor3f(0.0,0.0,0.0);
                  glBegin(GL_QUADS); // Рисуем прямоугольник (фон )
                    glVertex2f(x+2, y+this->height*0.5f+2);
                    glVertex2f(x+2, y+this->height*1.0f-2);
                    glVertex2f(x+2+this->width-4, y+this->height*1.0f-2);
                    glVertex2f(x+2+this->width-4, y+this->height*0.5f+2);
                  glEnd();

                  glColor3f(0.3, 0.5, 0.45);           // Отрисовка новой рамки
                  glBegin(GL_LINE_STRIP);              // кнопки для эффекта
                    glVertex2f(x+2, y+this->height*0.5f+2);              // нажатия
                    glVertex2f(x+2, y-2+this->height*1.0f);
                    glVertex2f(x-2+this->width, y-2+this->height*1.0f);
                    glVertex2f(x-2+this->width, y+this->height*0.5f+2);
                    glVertex2f(x+2, y+this->height*0.5f+2);
                  glEnd();

                  glColor3f(0.3, 0.5, 0.45);
                  glBegin(GL_TRIANGLES); // треугольник значок "вниз"
                    glVertex2f(x+this->width*0.25f*1.1f, y+this->height*0.9f*0.9f); 
                    glVertex2f(x+this->width*0.1f*1.1f, y+this->height*0.6f*0.9f);
                    glVertex2f(x+this->width*0.4f*1.1f, y+this->height*0.6f*0.9f);
                  glEnd();

                  double timer = duration_state - timer_start; //таймер для замедления ввода
                  // std::cout << timer << std::endl; // отладочный вывод
                  if (timer <= 0.03) //
                  {
                    //изменение параметра;
                    double num = atof(this->sValue.c_str());
                    num = num - step;
                    if (num < minCounter) num = minCounter;
                    if (num > maxCounter) num = maxCounter;
                    short int precisionVal = 2; // точность
                    this->sValue = std::to_string(num).substr(0, std::to_string(num).find(".") + precisionVal + 1);
                    this->value = num;
                    this->changed = true;
                  }
                  if (timer > 0.1) timer_start = duration_state;

                }
            }
    }
}

void SpinButtn::attach(EditBox &EdBox)
{
  //std::cout << "Attached" << std::endl;
  this->attached = true;
}


//===============================================================================
// Caption
void Caption::draw()
{
    glColor3f(this->colorRed, this->colorGreen, this->colorBlue);
    FTGLPixmapFont font(path_font);
    font.CharMap(ft_encoding_unicode);
    font.FaceSize(iFontSize);

    glRasterPos2i(x,y);
    wcstr = caption.c_str();
    
    font.Render(wcstr);
}

void Caption::setColor(float r, float g, float b)
{
    this->colorRed = r;
    this->colorGreen = g;
    this->colorBlue = b;
}

//===============================================================================
// ComboBox
void ComboBox::draw()
{
    glColor3f(guiColorBase.x, guiColorBase.y, guiColorBase.z);
    glBegin(GL_LINE_STRIP);             
        glVertex2f(x, y);                  
        glVertex2f(x+this->width, y);
        glVertex2f(x+this->width, y+this->height);
        glVertex2f(x, y+this->height);
        glVertex2f(x, y);
    glEnd();
    glBegin(GL_LINE_STRIP);                             
        glVertex2f(x+this->width-this->height, y);
        glVertex2f(x+this->width-this->height, y+this->height);
    glEnd();
    glBegin(GL_TRIANGLES); // треугольник значок "вниз"
        glVertex2f( x+this->width-(this->height*0.8f), y+this->height*0.25f);
        glVertex2f( x+this->width-(this->height*0.2f), y+this->height*0.25f);
        glVertex2f( x+this->width-(this->height*0.5f), y+this->height*0.8f);
    glEnd();

    //Caption
    glColor3f(this->colorRed, this->colorGreen, this->colorBlue);
    FTGLPixmapFont font(path_font);
    font.CharMap(ft_encoding_unicode);
    font.FaceSize(iFontSize);
    glRasterPos2i(x+5,y+height*0.76);
    wcstr = this->caption.c_str();   
    font.Render(wcstr);

    // если комбобокс открыт
    if (show_list == true) printString();
}

void ComboBox::MouseOn(double mousex, double mousey, short int wheel, std::string mouse_state,
                       double duration_state)
{
    double timer = duration_state - timer_start; //таймер для замедления ввода
    if (this->enabled){
      if (show_list) full_height = length_list; // если комбобокс открыт
      if ( mousex > x and mousex < x+this->width      
        and  mousey > y  and mousey < y+height+full_height )
            {
                glColor3f(guiColorPressed.x, guiColorPressed.y, guiColorPressed.z);
                glBegin(GL_LINE_STRIP); // 
                    glVertex2f(x+this->width-this->height+2, y+2);                  
                    glVertex2f(x+this->width-2, y+2);
                    glVertex2f(x+this->width-2, y+this->height-2);
                    glVertex2f(x+this->width-this->height+2, y+this->height-2);
                    glVertex2f(x+this->width-this->height+2, y+2);
                glEnd();

                if (show_list) {
                      //  printString();
                        if ( mousex > x and mousex < x+this->width      
                            and  mousey > y+height  and mousey < y+height+full_height ) {
                              //std::cout << mouse_state << std::endl;
                              // относительная координата по y
                              short int y0 = mousey-y-height;
                              // вычислим на какой строке находится мышь
                              short int num_str = (y0 / height) + 1;
                                //std::cout << index_total << std::endl;
                                 if (num_str < index_total + 1) {
                                    glColor3f(this->colorRed*1.2, this->colorGreen*1.2, this->colorBlue*1.2);
                                    FTGLPixmapFont font(path_font);
                                    font.CharMap(ft_encoding_unicode);
                                    font.FaceSize(iFontSize);
                                    glRasterPos2i(x,y+height*0.85+height*num_str);
                                    wcstr = this->listString[num_str-1].c_str();   
                                    font.Render(wcstr);
                                 }
   
                            if (mouse_state == "Left") // Если нажата кнопка
                            {
                                //std::cout << "clicked" << std::endl;
                                setCurrentIndex(num_str-1);
                            }
                        }
               }

                if (mouse_state == "Left") // Если мышь на кнопке и нажата кнопка
                {
                  timer_start = duration_state;
                  glColor3f(0.0,0.0,0.0);             // Закрашивание черным
                  glBegin(GL_LINE_STRIP);             // имеющейся рамки           
                    glVertex2f(x+this->width-this->height+0, y);                  
                    glVertex2f(x+this->width, y);
                    glVertex2f(x+this->width, y+this->height);
                    glVertex2f(x+this->width-this->height+0, y+this->height);
                    glVertex2f(x+this->width-this->height+0, y);
                  glEnd();
                  glColor3f(0.0,0.0,0.0);
                  glBegin(GL_QUADS); // Рисуем прямоугольник (фон )
                    glVertex2f(x+this->width-this->height, y);                  
                    glVertex2f(x+this->width, y);
                    glVertex2f(x+this->width, y+this->height);
                    glVertex2f(x+this->width-this->height, y+this->height);
                  glEnd();
                  glColor3f(0.5,0.75,0.55);// Отрисовка новой рамки
                  glBegin(GL_LINE_STRIP);              // кнопки для эффекта                              
                    glVertex2f(x+this->width-this->height+3, y+3);  // нажатия             
                    glVertex2f(x+this->width-3, y+3);
                    glVertex2f(x+this->width-3, y+this->height-3);
                    glVertex2f(x+this->width-this->height+3, y+this->height-3);
                    glVertex2f(x+this->width-this->height+3, y+3);
                  glEnd();
                  glColor3f(guiColorBase.x, guiColorBase.y, guiColorBase.z);
                  glBegin(GL_LINE_STRIP);                             
                    glVertex2f(x+this->width-this->height, y);
                    glVertex2f(x+this->width-this->height, y+this->height);
                  glEnd();
                  glColor3f(guiColorPressed.x, guiColorPressed.y, guiColorPressed.z);
                  glBegin(GL_TRIANGLES); // треугольник значок "вниз"
                    glVertex2f( x+this->width-(this->height*0.6f), y+this->height*0.3f);
                    glVertex2f( x+this->width-(this->height*0.3f), y+this->height*0.3f);
                    glVertex2f( x+this->width-(this->height*0.5f), y+this->height*0.6f);
                  glEnd();

                if (!show_list && (timer <= 0.4)) show_list = true;
                    else { show_list = false; full_height = 0; };

                if (timer > 0.1) timer_start = duration_state;
                }

            }
    }
}

void ComboBox::addString(std::wstring text)
{
    this->listString.push_back(text);
}

void ComboBox::printString()
{
   /* for (std::wstring n : this->listString)
        std::wcout << n << std::endl; */
    length_list = 0;
    short int i = 0;
    for (std::wstring n : this->listString)
    {
        length_list = length_list + this->height;
        glColor3f(this->colorRed, this->colorGreen, this->colorBlue);
        FTGLPixmapFont font(path_font);
        font.CharMap(ft_encoding_unicode);
        font.FaceSize(iFontSize);
        glRasterPos2i(x,y+height*0.85+length_list);
        wcstr = this->listString[i].c_str();   
        font.Render(wcstr);
        i++;
        this->index_total = i;
    }
    glColor3f(guiColorBase.x, guiColorBase.y, guiColorBase.z);
    glBegin(GL_LINE_STRIP);
      glVertex2f(x, y+height);
      glVertex2f(x, y+height+length_list);
      glVertex2f(x+width, y+height+length_list);
      glVertex2f(x+width, y+height);
    glEnd();
}

void ComboBox::setCurrentIndex(short int index)
{
    this->index_list = index;
    this->caption = this->listString[index];
}

// ==========================================================================
// Slider 
void Slider::draw()
{
    glColor3f(guiColorBase.x, guiColorBase.y, guiColorBase.z);
    glBegin(GL_LINE_STRIP);             
        glVertex2f(x, y);                  
        glVertex2f(x+this->width, y);
        glVertex2f(x+this->width, y+this->height);
        glVertex2f(x, y+this->height);
        glVertex2f(x, y);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x+(width*position)-2, y-5);
        glVertex2f(x+(width*position)+2, y-5);
        glVertex2f(x+(width*position)+2, y+10);
        glVertex2f(x+(width*position)-2, y+10);
    glEnd();
}

