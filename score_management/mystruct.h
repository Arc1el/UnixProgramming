#ifndef __MYSTRUCT_H__
#define __MYSTRUCT_H__

#define NAME_SIZE 16

typedef struct score
{
        int id;
        char name[NAME_SIZE];
        int korean;
        int english;
        int math;
        int all;
        float avg;
}score;

#endif
