#include <array>
#include <thread>
#include <random>

#include "window/window.h"
#include "window/bitmap.h"

#pragma comment(lib,"window")


void initBitmap()
{
    for(int i=0;i<dim;i++)
    {
        bitmapData[dim-1][i]= Colour::set;
    }
}

constexpr int gap{100};
int           startRow{dim-gap};

void walk()
{
    std::mt19937                    rng{std::random_device{}()};
    std::uniform_int_distribution   startColumn{0,dim-1};
    std::discrete_distribution      direction{100,100,95,100};

    while(   !done
          && startRow > 0)
    {
        int row   =startRow;
        int column=startColumn(rng);

        while(row > 0)
        {
            auto step=direction(rng);

            switch(step)
            {
            case 0: column--; break;
            case 1: column++; break;
            case 2: row--;    break;
            case 3: row++;    break;
            }

            if(row == -1)
            {
                break;
            }

            if(column == -1 ) 
            {
                column=dim-1;
            }
            else if(column==dim)
            {
                column=0;
            }

            if(row!=0)
            {
                if(   bitmapData[row+1][column] 
                   || bitmapData[row-1][column] 
                   || bitmapData[row  ][column-1] 
                   || bitmapData[row  ][column+1] )
                {
                    bitmapData[row][column]= 1+(row % 255) ;

                    startRow = std::min(startRow, row-gap);

                    break;
                }
            }
        }
    }
}



int main()
{
    createWindow();

    initBitmap();    

    std::array<std::jthread,4>  threads;

    for(auto &thread:threads)
    {
        thread = std::jthread{walk};
    }

    windowMessageLoop();
}
