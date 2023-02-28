#include <stdio.h>
#include <stdlib.h>
//I've provided "min" and "max" functions in
//case they are useful to you
int min(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}
int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

//Declare your rectangle structure here!
struct tag_rectangle {
  int x;
  int y;
  int width;
  int height;
};
typedef struct tag_rectangle rectangle;

rectangle canonicalize(rectangle r) {
  //make the point (x,y) the right, bottom corner
  if (r.width < 0) {
    r.x += r.width;
    r.width = r.width * (-1);
  }
  if (r.height < 0) {
    r.y += r.height;
    r.height = r.height * (-1);
  }
  return r;
}

rectangle max_axis(rectangle r1, rectangle r2, int axis) {
  if (axis == 1) {
    int x_max = max(r1.x, r2.x);
    if (x_max == r1.x) {
      return r1;
    }
    else {
      return r2;
    }
  }
  else {
    int y_max = max(r1.y, r2.y);
    if (y_max == r1.y) {
      return r1;
    }
    else {
      return r2;
    }
  }
}

rectangle min_axis(rectangle r1, rectangle r2, int axis) {
  if (axis == 1) {
    int x_min = min(r1.x, r2.x);
    if (x_min == r1.x) {
      return r1;
    }
    else {
      return r2;
    }
  }
  else {
    int y_min = min(r1.y, r2.y);
    if (y_min == r1.y) {
      return r1;
    }
    else {
      return r2;
    }
  }
}

rectangle intersection(rectangle r1, rectangle r2) {
  // given two rectangles, find the region of overlap
  r1 = canonicalize(r1);
  r2 = canonicalize(r2);
  rectangle ri;
  rectangle rmax = max_axis(r1, r2, 1);
  rectangle rmin = min_axis(r1, r2, 1);
  if (rmax.x <= rmin.x + rmin.width) {
    ri.x = rmax.x;
    if (rmin.x + rmin.width <= rmax.x + rmax.width) {
      ri.width = rmin.x + rmin.width - rmax.x;
    }
    else {
      ri.width = rmax.width;
    }
  }
  else {
    ri.width = 0;
    ri.height = 0;
    return ri;
  }
  rmax = max_axis(r1, r2, 0);
  rmin = min_axis(r1, r2, 0);
  if (rmax.y <= rmin.y + rmin.height) {
    ri.y = rmax.y;
    if (rmin.y + rmin.height <= rmax.y + rmax.height) {
      ri.height = rmin.y + rmin.height - rmax.y;
    }
    else {
      ri.height = rmax.height;
    }
  }
  else {
    ri.height = 0;
    ri.width = 0;
  }
  return ri;
}

//You should not need to modify any code below this line
void printRectangle(rectangle r) {
  r = canonicalize(r);
  if (r.width == 0 && r.height == 0) {
    printf("<empty>\n");
  }
  else {
    printf("(%d,%d) to (%d,%d)\n", r.x, r.y, r.x + r.width, r.y + r.height);
  }
}

int main(void) {
  rectangle r1;
  rectangle r2;
  rectangle r3;
  rectangle r4;

  r1.x = 2;
  r1.y = 3;
  r1.width = 5;
  r1.height = 6;
  printf("r1 is ");
  printRectangle(r1);

  r2.x = 4;
  r2.y = 5;
  r2.width = -5;
  r2.height = -7;
  printf("r2 is ");
  printRectangle(r2);

  r3.x = -2;
  r3.y = 7;
  r3.width = 7;
  r3.height = -10;
  printf("r3 is ");
  printRectangle(r3);

  r4.x = 0;
  r4.y = 7;
  r4.width = -4;
  r4.height = 2;
  printf("r4 is ");
  printRectangle(r4);

  //test everything with r1
  rectangle i = intersection(r1, r1);
  printf("intersection(r1,r1): ");
  printRectangle(i);

  i = intersection(r1, r2);
  printf("intersection(r1,r2): ");
  printRectangle(i);

  i = intersection(r1, r3);
  printf("intersection(r1,r3): ");
  printRectangle(i);

  i = intersection(r1, r4);
  printf("intersection(r1,r4): ");
  printRectangle(i);

  //test everything with r2
  i = intersection(r2, r1);
  printf("intersection(r2,r1): ");
  printRectangle(i);

  i = intersection(r2, r2);
  printf("intersection(r2,r2): ");
  printRectangle(i);

  i = intersection(r2, r3);
  printf("intersection(r2,r3): ");
  printRectangle(i);

  i = intersection(r2, r4);
  printf("intersection(r2,r4): ");
  printRectangle(i);

  //test everything with r3
  i = intersection(r3, r1);
  printf("intersection(r3,r1): ");
  printRectangle(i);

  i = intersection(r3, r2);
  printf("intersection(r3,r2): ");
  printRectangle(i);

  i = intersection(r3, r3);
  printf("intersection(r3,r3): ");
  printRectangle(i);

  i = intersection(r3, r4);
  printf("intersection(r3,r4): ");
  printRectangle(i);

  //test everything with r4
  i = intersection(r4, r1);
  printf("intersection(r4,r1): ");
  printRectangle(i);

  i = intersection(r4, r2);
  printf("intersection(r4,r2): ");
  printRectangle(i);

  i = intersection(r4, r3);
  printf("intersection(r4,r3): ");
  printRectangle(i);

  i = intersection(r4, r4);
  printf("intersection(r4,r4): ");
  printRectangle(i);

  return EXIT_SUCCESS;
}
