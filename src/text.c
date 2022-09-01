#include "text.h"
#include "shapes.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct Pixel Pixel;
struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
};

#define w 256
#define h 256

unsigned int id;

void Text_init(){
    const int byteCount = w * h * 4; // change this and some other 3's to 4 i guess idk it just don't work man help
    char* pixels = malloc(byteCount);
    
    FILE * stream;
    stream = fopen("test.upf", "r");
    if(!stream) printf("OMGAH the path is wrong!");
    // stream = fopen("Lucida Console.png", "r");
    // fseek(stream, 33, SEEK_SET);
    // // rewind(stream);
    
    int _count = fread(&pixels, sizeof(char), byteCount, stream);
    fclose(stream);


    for(int i = 0; i < byteCount; i += 4){
        // printf("%x  %x  %x  %x\n", pixels[i], pixels[i + 1], pixels[i + 2], pixels[i + 3]);
        if(i > 256) break;
        // if(i > 512) break;
        // unsigned char 
        //     a = pixels[i    ], 
        //     r = pixels[i + 1], 
        //     g = pixels[i + 2], 
        //     b = pixels[i + 3];
        // pixels[i    ] = r & 0xFF; 
        // pixels[i + 1] = g & 0xFF; 
        // pixels[i + 2] = b & 0xFF; 
        // pixels[i + 3] = a & 0xFF;
    }


    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //Setup texture scaling filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    // free(pixels);  
    // ! TEST TO SEE IF THIS WORKS!!!
}

Text new_Text(char* str, Vector2 pos){
    Text text;
    strcpy(text.text, str);
    // puts(text.text);
    text.pos = pos;
    text.cs = 16;
    text.shouldCenter = false;
    return text;
}

void Text_draw(Text text){
    int _y = text.pos.y;
    int index = 0;
    // printf("%d %s\n", strlen(text.text), text.text);
    for(int i = 0; i < strlen(text.text); i ++){

        if(text.text[i] == '\r') continue;
        if(text.text[i] == '\n') {
            index = 0;
            _y += 16;
            continue;
        }

        int charCode = (int) text.text[i] - 32;
        double
            tx = (charCode % 16 / 16.0),
            ty = (floor(charCode / 16.0) / 16.0);

        int _x = text.pos.x + index * text.cs;
        if(text.shouldCenter) _x -= strlen(text.text) / 2 * text.cs;

        // printf("%d, %d, %f, %f, %d", _x, _y, tx, ty, id);
        // system("pause");
        character(_x, _y, 16, 16, tx, ty, 0.0625, 0.0625, id);
        // character(200, 200, 256, 256, 0, 0, 1, 1, id);
        index ++;
    }
}
