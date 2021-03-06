class DrawWindow {
    public:
        DrawWindow();
        void printCharacter(int x, int y, char c);
        void drawRect(int startX, int startY, int width, int heigth);
        void drawMenu();
        void printCommand(int* cnt);
        void printCredits();
        void credits(int direction);
};

