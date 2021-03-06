class EngineGame{
  protected:
    int frameGameX;
    int frameGameY;
    int height;
    int widht;
    bool quit;
    bool pause;
    Pbullet shoots;
    bool isShoot;
    int whileCount;
  public:
    EngineGame(int frameGameX,int frameGameY, int heigth, int width);
    void baseCommand();
    void moveCharacter(Character &character, int direction);
    bool isEmpty(int x, int y);
    Pbullet createBullet(int x, int y);
    void shootBullet();
    Pbullet destroyBullet();
    void engine(Character character, DrawWindow printer);
    void choiceGame(DrawWindow drawWindow, int *direction, int *selection);
    void runGame(Character character, DrawWindow drawWindow, int direction);
};