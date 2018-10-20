#ifndef PICTURE_H
#define PICTURE_H
#include "Shape.h"
#include <iostream>

typedef class ShapeLinkedListPair * ShapeLinkedList;
class ShapeLinkedListPair
{
public:
  Shape * info;
  ShapeLinkedList next;
  ShapeLinkedListPair( Shape * newInfo, ShapeLinkedList newNext )
    : info(newInfo), next( newNext )
  {
  }
};

class Picture
{
  ShapeLinkedList head;
public:
  Picture()
    : head( nullptr )
  {
  }

  void add( Shape * sp )
  {
    head = new ShapeLinkedListPair( sp, head );
  }

  void drawAll()
  {
    for (ShapeLinkedList p = head; p != nullptr; p = p->next)
        p->info->draw();
  }

  double totalArea()
  {
    double total = 0.0;
    for (ShapeLinkedList p = head; p != nullptr; p = p->next)
        total += p->info->area();
    return total;
  }

  ~Picture()
  {
    deleteList(head);
  }

private:
  static void deleteList( ShapeLinkedListPair * L)
  {
    if (L != nullptr)
    {
        deleteList(L->next);
        delete L->info;
        delete L;
    }
  }
        
};

#endif
