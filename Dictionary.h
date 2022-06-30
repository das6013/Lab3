#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <QString>

struct  Dictonary
{
    QString key;// key
    float val;//value
    Dictonary (QString _key, float _val)//consructor 
    {
        key = _key;
        val = _val;
    } ;
};
#endif // DICTIONARY_H
