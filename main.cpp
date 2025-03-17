#include<iostream>
#include<string>
#include<cstring>
#include<ncurses.h> //console managment
#include<unistd.h> // sleep()
#include<sys/ioctl.h>
#include<vector>
using namespace std;

//Global
enum Direction {up, down, left, right, none};

class snake
{
    private:
        Direction direction = none;
        bool getFood = false;
        int snake_delay = 180000;
    public:
        
        vector<pair<int, int>> body = {{0,0}};   
        int food_x = 4;
        int food_y = 3;

        void generate_food(int h, int w)
        {
            if(getFood == true)
            {
                srand(time(0));
                food_y = (rand() % (h-2))+1;
                food_x = (rand() % (w-2))+1;
                
                body.push_back({body.back().first, body.back().second});
                

                getFood = false;
            }
    
            mvprintw(food_y,food_x, "*");
        }
        
        void foodSetFalse()
        {
            getFood = false;
        }
        void foodSetTrue()
        {
            getFood = true;
        }
        bool footStatus()
        {
            return getFood;
        }
        
        int get_delay()
        {
            return snake_delay;
        }
        void move_up()
        {
            if(direction != Direction::down)
            {
                direction = Direction::up;
            }
        }
        void move_down()
        {
            if(direction != Direction::up)
            {
                direction = Direction::down;
            }
        }
        void move_left()
        {
            if(direction != Direction:: right)
            {
                direction = Direction::left;
            }
        }
        void move_right()
        {
            if(direction != Direction::left)
            {
                direction = Direction::right;
            }
        }
        void move_none()
        {
            direction = Direction::none;
        }
        Direction whatis_direction()
        {
            return direction;
        }
        void set_body_value(int x, int y, int index)
        {
            body[index] = {x, y};
        }
        int get_size()
        {
            return body.size();
        }

};



void drawFrame(int h, int w)
{
    for (size_t i = 0; i < w; i++)
    {
        printw("#");
    }
    printw("\n");
    for (int i=1; i < (h-1); i++) {
        printw("#");
        
        mvprintw(i, w-1, "#");
        printw("\n");
    }
    for (size_t i = 0; i < w; i++)
    {
        printw("#");
    }
}

void gameOver()
{
    endwin();
    printf("gameOver");
    exit(0);
}

void colission(int h, int w, int start_x, int start_y, snake& object)
{   
    ////////////////////////////////// head Check
    if(start_y == 0 or start_y == h-1)
    {
        gameOver();
    }
    else if(start_x == 0 or start_x == w-1)
    {
        
        gameOver();
    }
    //////////////////////////////////
    /////////////////////////////////////////// Body Check
    for(int i=1; i < object.body.size(); i++)
    {
        if (start_x == object.body[i].first && start_y == object.body[i].second) //debug
        {   
            gameOver();
        }
        
    }
    ///////////////////////////////////////////
}

void run(snake& object) 
{
    int h;
    int w;

    ///////////////////////////////////////// get scr size for generate start snake position
    struct winsize startpos;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &startpos);
    /////////////////////////////////////////
    int start_y = (startpos.ws_row-1)/ 2;    //Start Position
    int start_x = (startpos.ws_col-1) / 2;

    initscr();
    noecho();   //not show input char 
    curs_set(0);
    nodelay(stdscr, TRUE);  // no wait for get input
    keypad(stdscr, TRUE); // Special key

    
    while (true)
    {
        ////////////////////////////////////////////////////// Update Scr Size
        struct winsize scr;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &scr);  // Get Terminal Detail
        h = scr.ws_row-1;
        w = scr.ws_col-1;
        ///////////////////////////////////////////////////////
        
        
        clear();
        
        drawFrame(h, w);
        
        //update body Position
        if(object.whatis_direction() != Direction::none)    //fix Press other key to hide body
        {
            for (int i = object.body.size()-1; i > 0; i--)
            {
                object.set_body_value(object.body[i-1].first, object.body[i-1].second, i);
            }
        
            object.set_body_value(start_x, start_y, 0);
        }

        
        
        colission(h, w, start_x, start_y, object);  // Game Over Handled
        
        ////////////////////////////////////////////////// Update head Position
        if(object.whatis_direction() == Direction::up)
        {
            start_y++;
        }
        else if(object.whatis_direction() == Direction::down)
        {
            start_y--;
        }
        else if(object.whatis_direction() == Direction::left)
        {
            start_x--;
        }
        else if(object.whatis_direction() == Direction::right)
        {
            start_x++;   
        }
        ///////////////////////////////////////////////////
        

        
        
        

        if(start_x == object.food_x and start_y == object.food_y) //check get food
        {
            object.foodSetTrue();
        }

        object.generate_food(h, w);


        ////////////////////////////////////// Draw Snake
        mvprintw(start_y, start_x, "@");    //head
        for (size_t i = 0; i < object.get_size(); i++)  //Body
        {
            mvprintw(object.body[i].second,object.body[i].first,"@");
        }
        //////////////////////////////////////

        ////////////////////// input
        int key = getch();
        if(key == 258) //UP
        {
            object.move_up();
            // flushinp(); //clear input buffer
        }
        else if(key == 259) //DOWN
        {
            object.move_down(); 
            // flushinp(); //clear input buffer
        }
        else if(key == 260) //LEFT
        {
            object.move_left();
            // flushinp(); //clear input buffer
        }
        else if(key == 261) //RIGHT
        {
            object.move_right();
            // flushinp(); //clear input buffer
        }
        else if(key == 27)
        {
            endwin();
            exit(1);
        }
        ////////////////////////////endInput


        refresh();
        usleep(object.get_delay()); //Snake Speed
    }


    endwin();
}

int main()
{
    snake player;

    run(player);
    return 0;
}