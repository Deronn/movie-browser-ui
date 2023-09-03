#pragma once

#include <set>
#include <string>

using namespace std;

// Movie class

class Movie {
private:
    string name;
    int year;
    string directors;
    string stars;
    string genres;
    string img;

public:
    Movie(string name, int year, string directors, string stars, string genres, string img);
    ~Movie();

    string getName() {
        return name;
    }

    int getYear() {
        return year;
    }

    string getDirectors() {
        return directors;
    }

    string getStars() {
        return stars;
    }
    string getGenres() {
        return genres;
    }

    string getImage() {
        return img;
    }
};