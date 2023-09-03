#include <iostream>

#include "Movie.h"

using namespace std;

// Constructor

Movie::Movie(string name, int year, string directors, string stars, string genres, string img) : name(name), year(year), directors(directors), stars(stars), genres(genres), img(img) {
    cout << "Movie created: " << name << " " << year << " " << directors << " " << stars << " " << genres << " " << endl;
}

// Destructor

Movie::~Movie() {
    cout << "Movie destroyed: " << name << " " << year << " " << directors << " " << stars << " " << genres << " " << img << endl;
}
