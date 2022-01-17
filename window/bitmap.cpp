#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstddef>
#include <utility>
#include <mutex>


#include "bitmap.h"


namespace
{

auto makeHeader()
{
    auto header = reinterpret_cast<BITMAPINFO*>( new  std::byte[ sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)]);

    header->bmiHeader.biSize            = sizeof(BITMAPINFOHEADER);
    header->bmiHeader.biWidth           =  dim;
    header->bmiHeader.biHeight          = -dim;
    header->bmiHeader.biPlanes          =    1;
    header->bmiHeader.biBitCount        =    8;
    header->bmiHeader.biCompression     = BI_RGB;
    header->bmiHeader.biSizeImage       = dim*dim,
    header->bmiHeader.biXPelsPerMeter   = 0;
    header->bmiHeader.biYPelsPerMeter   = 0;
    header->bmiHeader.biClrUsed         = 0;
    header->bmiHeader.biClrImportant    = 0;

    for(int i=0;i<=255;i++)
    {
        header->bmiColors[i]= RGBQUAD(i,i,i);
    }
                                                  //  B    G    R
    header->bmiColors[Colour::set]        = RGBQUAD(255, 255, 255);

    return header;
}

}


BITMAPINFO     *bitmapHeader        {makeHeader()};
uint8_t         bitmapData[dim][dim]{};
//                               ^---- must be multiple of 4





