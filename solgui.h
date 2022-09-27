#ifndef SOLGUI_H
#define SOLGUI_H
#include <glm/glm.hpp>  // Включаем GLM

const glm::vec3 guiColorBase(0.5,0.75,0.7);   // базовый цвет линий интерфейса
const glm::vec3 guiColorPressed(0.25,0.37,0.35); // цвет интерфейса при нажатии
//const char *pathFont = "data/fonts/TerminusTTF-4.47.0.ttf";

class Buttn;
class SpinButton;
class EditBox;
class Caption;
class ComboBox;

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
      
// SpinButton /////////////////////////////////////
class SpinButtn
{
        public:
            short int x, y;
            float value = 1.0;
            float step = 1.0;
            bool enabled = true;
            short int width = 10;
            short int height = 10;
            std::string sValue;
            bool attached = false;
            bool changed = false;
            double timer_start;
            float minCounter = 0;
            float maxCounter = 1000;
            
            void draw();
            void MouseOn(double mousex, double mousey, std::string mouse_state,
                         double duration_state);
            void attach(EditBox &edBox);
            void changeValue(EditBox &edBox);

            SpinButtn(short int _x=0, short int _y=0, float _value = 1.0, float _step = 1) :
                      x(_x), y(_y), value(_value), step(_step) {};

        private:
            const char *cstr;
            
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
           //short int multiply = 1; // кратность
           float step = 1.0;       // шаг изменения
           bool attached = false;
           float minCounter = 0;
           float maxCounter = 1000;

           void attach(SpinButtn &spButtn);
           void getSpinButtnState(SpinButtn &spButtn);
           void setColor(float r, float g, float b);    
           
           EditBox(float _x=0.0, float _y=0.0, float _a=20.0, float _b=10.0,
                  double _mousex=0.0, double _mousey=0.0, short int _wheel=0, std::string _mouse_state = "",
                  std::string _text = "EditBox", 
                  const char *_path_font = "data/fonts/fabryka_4f_medium.ttf",
                  short int _iFontSize = 16) :
                   x(_x), y(_y), a(_a), b(_b),  alpha(1.0), 
                   mousex(_mousex), mousey(_mousey), wheel(_wheel), mouse_state(_mouse_state),
                   text (_text), path_font(_path_font), iFontSize(_iFontSize) {};
            void draw();
            void draw(SpinButtn &spButtn);
            void MouseOn(double mousex, double mousey, short int wheel, std::string mouse_state,
                         double duration_state, short int key);
   private:
           std::string addtext;
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
        float colorRed = 1.0;
        float colorGreen = 1.0;
        float colorBlue = 1.0;

        void draw();
        void setColor(float r, float g, float b);
        
        Caption(short int _x=0, short int _y=0, std::wstring _caption = L"Caption", 
                const char *_path_font = "data/fonts/fabryka_4f_medium.ttf") : 
                x(_x), y(_y), caption(_caption), path_font(_path_font) {};
};

// ComboBox -> /////////////////////////////////////////////////
class ComboBox
{
    public:
        short int x, y;
        short int width = 140;
        short int height = 20;
        bool enabled = true;
        double mousex, mousey;
        short int wheel=0;         // состояние колеса мыши
        std::string mouse_state;
        std::vector<std::wstring> listString;
        short int iFontSize=16;
        double timer_start;
        float colorRed = guiColorBase.x;
        float colorGreen = guiColorBase.y;
        float colorBlue = guiColorBase.z;
        const char *path_font = "data/fonts/TerminusTTF-4.47.0.ttf";
        const wchar_t *wcstr;
        std::wstring caption;
        short int index_list = 0;
        short int index_total = 0;

        ComboBox(short int _x=0, short int _y=0) : x(_x), y(_y) {};

        void draw();
        void MouseOn(double mousex, double mousey, short int wheel, std::string mouse_state,
                     double duration_state);
        void addString(std::wstring text);
        void printString();
        void setCurrentIndex(short int index);

    private:
        bool show_list = false;
        short int length_list = 0;
        short int full_height = 0;     
};
// <- ComboBox //////////////////////////////////////////////////////

// Slider -> ////////////////////////////////////////////////////////
class Slider
{
    public:
    short int x, y;

    Slider(short int _x = 0, short int _y = 0) : x(_x), y(_y) {};
    void draw();
};

// <- Slider ////////////////////////////////////////////////////////

#endif
