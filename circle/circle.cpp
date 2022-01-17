#include <array>
#include <thread>
#include <random>
#include <numbers>

#include "window/window.h"
#include "window/bitmap.h"

#pragma comment(lib,"window")


void initBitmap()
{
    bitmapData[dim/2][dim/2]= Colour::set;
}

constexpr int gap{100};
double        radius{gap};

void walk()
{
    std::mt19937                            rng{std::random_device{}()};
    std::discrete_distribution              direction{100,100,100,100};

    std::uniform_real_distribution<double>  angle{0, 2*std::numbers::pi};


    while(   !done
          && radius < dim/2)
    {
        auto startAngle = angle(rng);

        int row   = dim/2 + static_cast<int>(radius * std::sin(startAngle));
        int column= dim/2 + static_cast<int>(radius * std::cos(startAngle));

        bitmapData[row][column]=50;

        auto distance = [&]
        {
            auto dr = row-dim/2;
            auto dc = column-dim/2;

            return std::sqrt(dr*dr+dc*dc);
        };

        while(distance() < dim/2)
        {
            auto step=direction(rng);

            switch(step)
            {
            case 0: column--; break;
            case 1: column++; break;
            case 2: row--;    break;
            case 3: row++;    break;
            }

            bitmapData[row][column]=10;

            if(   bitmapData[row+1][column] == 255
                || bitmapData[row-1][column] == 255
                || bitmapData[row  ][column-1] == 255
                || bitmapData[row  ][column+1] == 255)
            {
                bitmapData[row][column]=255;

                radius = std::max(radius, distance()+gap);

                break;
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
