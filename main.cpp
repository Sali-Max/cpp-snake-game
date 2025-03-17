#include<iostream>
#include<string>
#include<ncurses.h> //console managment
#include<unistd.h> // sleep()
#include<vector>
using namespace std;

//Global
enum Direction {up, down, left, right, none};

class snake
{
    private:
        int body_size = 2;
        Direction direction = up;
        bool getFood = false;
    public:

        vector<pair<int, int>> body = {{12,19}, {12,10}};
        int food_x = 4;
        int food_y = 3;
    
        void generate_food(int h, int w)
        {
            if(getFood == true)
            {
                srand(time(0));
                food_y = rand() % h;
                food_x = rand() % w;
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
        
        void move_up()
        {
            direction = Direction::up;
        }
        void move_down()
        {
            direction = Direction::down;
        }
        void move_left()
        {
            direction = Direction::left;
        }
        void move_right()
        {
            direction = Direction::right;
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
            return body_size;
        }
        void add_size()
        {
            body_size++;
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
        // cout << setw(w - 1) << "#";
        mvprintw(i, w-1, "#");
        printw("\n");
    }
    for (size_t i = 0; i < w; i++)
    {
        printw("#");
    }
}



void run(int h, int w, snake& object)
{
    int start_y = h / 2;    //Start Position
    int start_x = w / 2;

    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE); // Special key

    
    

    while (true)
    {
        clear();
        
        drawFrame(h, w);
        

        // Update head Position
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

        //update body Position
        if(object.whatis_direction() != Direction::none)    //fix Press other key to hide body
        {
            for (size_t i = object.get_size() ; i > 1; i--)
            {
                object.set_body_value(object.body.back().first, object.body.back().second, i-1);
            }
            object.set_body_value(start_x, start_y, 0);
        }


        mvprintw(start_y, start_x, "@");    //Draw head
        for (size_t i = 0; i < object.get_size(); i++)  //Drow Body
        {
            mvprintw(object.body[i].second,object.body[i].first,"@");
        }
        

        if(start_x == object.food_x and start_y == object.food_y) //check get food
        {
            object.foodSetTrue();
        }

        object.generate_food(h, w);

        {   //input
            int key = getch();
            if(key == 258) //UP
            {
                object.move_up();
            }
            else if(key == 259) //DOWN
            {
                object.move_down(); 
            }
            else if(key == 260) //LEFT
            {
                object.move_left();
            }
            else if(key == 261) //RIGHT
            {
                object.move_right();
            }
            else if(key == 27)
            {
                endwin();
                exit(1);
            }
            else
            {
                object.move_none();
            }
        }

        
        refresh();
    }


    endwin();
}

int main()
{
    snake player;

    run(24,24, player);
    return 0;
}