#pragma once

#include "ButtonWidget.h"
#include "ImageWidget.h"
#include "Movie.h"
#include "TextWidget.h"
#include "Widget.h"
#include <set>
#include <string>
#include <vector>

using namespace std;

// MovieBrowser is the logic container

class MovieBrowser {
private:
    string title;
    string uninitialized;
    int width, height;
    float canvas_width;
    float canvas_height;
    vector<Movie*> movies;
    vector<Movie*> filteredMovies;
    vector<Widget*> widgets;
    vector<Widget*> year_widgets;
    vector<Widget*> gender_widgets;
    set<string> years;
    set<string> genres;
    size_t currentMovie;
    bool dirty;
    bool dirty_filter;

    TextWidget* txt_title;
    TextWidget* txt_director;
    TextWidget* txt_stars;
    TextWidget* txt_year;
    TextWidget* txt_genres;
    ButtonWidget* next;
    ButtonWidget* previous;
    ImageWidget* moviePicture;


    string selectedYear;
    string selectedGenre;

    //dokimes
    Widget* active_button = nullptr;
    Widget* bt = nullptr;

public:
    MovieBrowser(string title, int width, int height);
    ~MovieBrowser();

    void init();
    void preloadAssets();
    void load();
    void setupWidgets();
    void mainLoop();

    void draw();
    void update(float ms);

    void clickEvent(ButtonWidget* source);
};
