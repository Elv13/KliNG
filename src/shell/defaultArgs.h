#ifndef DEF_DEFAULT_ARGS
#define DEF_DEFAULT_ARGS

class DefaultArgs {
  public:
    DefaultArgs();
    DefaultArgs(QString command);
    int getKey();
    bool getEnable();
    void setKey(int key);
    void setEnable(bool value);
    
  private:
    bool enable;
    int key;
};

#endif