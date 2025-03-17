#include<iostream>
#include<string>
#include<iomanip>
#include<ncurses.h>
#include<unistd.h>
using namespace std;


class snake
{
    private:
        int size = 1;
        enum Direction {up, down, left, right};
        Direction direction = up;
    public:
        void move_up()
        {
            direction = up
        }
        void move_down()
        {
            direction = down;
        }
        void move_left()
        {
            direction = left;
        }
        void move_right()
        {
            direction = right;
        }
        
        void add_size()
        {
            size++;
        }
};


void run(int h, int w)
{
    initscr();

    while (true)
    {   
        for (size_t i = 0; i < w; i++)
        {
            printw("#");
        }
        printw("\n");
        for (int i=1; i < (h-1); i++) {
            printw("#");
            // cout << setw(w - 1) << "#";
            mvprintw(i, w-1, "#");
            printw("\n");
        }
        for (size_t i = 0; i < w; i++)
        {
            printw("#");
        }
        
        
        refresh();
    }


    refresh();
    endwin();
}

int main()
{
    // createFrame(12,25);
    run(10,25);
    return 0;
}