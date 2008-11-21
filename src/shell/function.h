#ifndef DEF_FUNCTION
#define DEF_FUNCTION

class Function {
  public:
    Function();
    Function(QString name);
    int getKey();
    bool getEnable();
    void setKey(int key);
    void setEnable(bool value);
    
  private:
    bool enable;
    int key;
};

#endif