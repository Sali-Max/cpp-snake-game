#include<iostream>
#include<string>
#include<iomanip>

using namespace std;


class snake
{
    private:
        int size = 1;
    public:
        void move_up()
        {

        }
        void move_down()
        {

        }

        void add_size()
        {
            size++;
        }
};


void createFrame(int h, int w)
{
    for (size_t i = 0; i < w; i++)
    {
        printf("#");
    }

    printf("\n");
    
    for (int i=1; i < (h-1); i++) {
        printf("#");
        cout << setw(w - 1) << "#";
        printf("\n");

    }

    for (size_t i = 0; i < w; i++)
    {
        printf("#");
    }
}



int main()
{
    createFrame(12,50);
    return 0;
}