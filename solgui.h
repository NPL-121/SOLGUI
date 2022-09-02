#ifndef SOLGUI_H
#define SOLGUI_H
#include <glm/glm.hpp>  // Включаем GLM

const glm::vec3 guiColorBase(0.5,0.75,0.7);  // базовый цвет линий интерфейса
//const char *pathFont = "data/fonts/TerminusTTF-4.47.0.ttf";


//////////////////////////////////////////////////////////////
// Классы
// ->
  // Класс объекта "Кнопка" /////////// Buttn ////////////////
  // ->
class Buttn
{
     public:
            float x,y,a,b,alpha;
            double mousex, mousey;
            std::string mouse_state;
            std::wstring caption;
            const char *cstr, *path_font;
            //const char *path_font;
            const wchar_t *wcstr;
            bool state;
            bool enabled = true;
            short int iFontSize = 15;

            Buttn(float x=0.0, float y=0.0, float a=20.0, float b=10.0, 
                  double mousex=0.0, double mousey=0.0, std::string mouse_state = "",
                  std::wstring caption = L"button", 
                  const char *path_font = "data/fonts/TerminusTTF-4.47.0.ttf");
            void draw();
            void MouseOn(double mousex, double mousey, std::string mouse_state);
};
      
  // EditBox -> ///////////////////////////////////////////////
class EditBox
{
    public:
           float x,y,a,b,alpha;
           double mousex, mousey;
           short int wheel=0;         // состояние колеса мыши
           std::string mouse_state, text;
           const char *cstr, *path_font;
           bool state;
           bool enabled = true;           //editbox активен
           bool changed_flag = false;
           short int iFontSize;
           double timer_start;
           bool num_wheel = true;  // переключатель для контроля смены цифр колесом мыши
           short unsigned int type_num=0; // тип integer or double;
           short int multiply = 1; // кратность
           
           
           EditBox(float _x=0.0, float _y=0.0, float _a=20.0, float _b=10.0,
                  double _mousex=0.0, double _mousey=0.0, short int _wheel=0, std::string _mouse_state = "",
                  std::string _text = "EditBox", 
                  const char *_path_font = "data/fonts/fabryka_4f_medium.ttf",
                  short int _iFontSize = 16) :
                   x(_x), y(_y), a(_a), b(_b),  alpha(1.0), 
                   mousex(_mousex), mousey(_mousey), wheel(_wheel), mouse_state(_mouse_state),
                   text (_text), path_font(_path_font), iFontSize(_iFontSize) {};
            void draw();
            void MouseOn(double mousex, double mousey, short int wheel, std::string mouse_state,
                         double duration_state, short int key);
   private:
           std::string addtext;
};
  // EditBox + SpinButton /////////////////////////////////////
class EditBoxSp : public EditBox
{
        public:
            void draw();
            void MouseOn();
};

  // Caption -> ///////////////////////////////////////////////
class Caption
{
    public:
        short int x,y;
        float step = 0.5;
        std::wstring caption;
        const char *cstr, *path_font;
        const wchar_t *wcstr;
        short int iFontSize = 20;

        void draw();
        
        Caption(short int _x=0, short int _y=0, std::wstring _caption = L"Caption", 
                const char *_path_font = "data/fonts/fabryka_4f_medium.ttf") : 
                x(_x), y(_y), caption(_caption), path_font(_path_font) {};
};


#endif
