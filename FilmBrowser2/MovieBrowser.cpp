#include "MovieBrowser.h"

#include <iostream>
#include <random>
#include <string>

#include <sgg/graphics.h>

#include "ButtonWidget.h"
#include "ImageWidget.h"
#include "TextWidget.h"


using namespace std;

static const std::string assets_path = "assets/";

// Constructor

MovieBrowser::MovieBrowser(string title, int width, int height) : title(title), width(width), height(height), canvas_width(100), canvas_height(100) {
    cout << "MovieBrowser created \n";

    txt_title = nullptr;
    txt_director = nullptr;
    txt_stars = nullptr;
    txt_year = nullptr;
    txt_genres = nullptr;
    uninitialized = "no movie found";
    next = nullptr;
    previous = nullptr;
    moviePicture = nullptr;

    dirty_filter = false;

    selectedYear = "";
    selectedGenre = "";
}

// Destructor

MovieBrowser::~MovieBrowser() {
    graphics::destroyWindow();

    for (auto m : movies) {
        delete m;
    }

    for (auto w : widgets) {
        delete w;
    }
}

// Defines canvas size and color

void MovieBrowser::init() {
    graphics::createWindow(width, height, title);

    graphics::Brush br;
    br.fill_color[0] = 0.0f;
    br.fill_color[1] = 0.0f;
    br.fill_color[2] = 0.0f;
    graphics::setWindowBackground(br);
    graphics::setFont(assets_path + "orange juice 2.0.ttf");

    graphics::setCanvasSize(canvas_width, canvas_height);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::setUserData(this);
}

// Loads assets

void MovieBrowser::preloadAssets() {
    const auto assests = graphics::preloadBitmaps("assets");
    for (const auto asset : assests) {
        std::cout << "PRELOADING : " << asset << std::endl;
    }
}

// Loads a set of movies

void MovieBrowser::load() {
    cout << "Loading movies \n";

    
    movies.push_back(new Movie("Rita Hayworth and the Shawshank Redemption", 1994, "Frank Darabont", "Tim Robbins, Morgan Freeman, Bob Gunton", "drama", "Shawshank_Redemption_compressed.png"));

    movies.push_back(new Movie("The Godfather", 1972, "Francis Ford Coppola", "Marlon Brando, Al Pacino, James Caan", "drama, history", "Godfather_compressed.png"));

    movies.push_back(new Movie("The Dark Knight", 2008, "Christopher Nolan", "Christian Bale, Heath Ledger, Aaron Eckhart", "action, crime, drama", "Dark_knight_compressed.png"));

    movies.push_back(new Movie("The Godfather II", 1974, "Francis Ford Coppola", "Al Pacino, Robert De Niro, Robert Duvali", "crime, drama", "Godfather_2_compressed.png"));

    movies.push_back(new Movie("12 Angry Men", 1957, "Sidney Lumet", "Henry Fonda, Lee J. Cobb, Martin Balsam", "crime, drama", "12_Angry_Men_compressed.png"));

    movies.push_back(new Movie("Schindler's List", 1993, "Steven Spielberg", "Liam Neeson, Ralph Fiennes, Ben Kingsley, Ben Kingsley", "biography, drama, history", "Schindlers_List_compressed.png"));

    movies.push_back(new Movie("The Lord of the Rings: The Return of the King", 2003, "Peter Jackson", "Elijah Wood, Viggo Mortensen, Ian McKellen", "action, adventure, drama", "Lord_of_the_rings_compressed.png"));

    movies.push_back(new Movie("Pulp Fiction", 1994, "Quentin Tarantino", "John Travolta, Uma Thurman, Samuel L. Jackson", "crime, drama", "PulpFiction_compressed.png"));

    movies.push_back(new Movie("The Good, The Bad, The Ugly", 1966, "Sergio Leone", "Clint Eastwood, Eli Wallach, Lee Van Cleef", "adventure, western", "Buono-Brutto-Cattivo_compressed.png"));

    filteredMovies = movies;

    cout << "Total movies: " << movies.size() << endl;

    for (auto m : movies) {
        string s = std::to_string(m->getYear());
        years.insert(s);
    }

     
    

    genres.insert("drama");
    genres.insert("crime");
    genres.insert("action");
    genres.insert("biography");
    genres.insert("history");
    genres.insert("western");
    genres.insert("adventure"); 

    

    currentMovie = movies.size() / 2;
    dirty = true;
}

// SGG main loop

void MovieBrowser::mainLoop() {
    graphics::startMessageLoop();
}

// Initializes all widgets

void MovieBrowser::setupWidgets() {
    string title_font = assets_path + "orange juice 2.0.ttf";
    string movie_title_font = assets_path + "OpenSans-Semibold.ttf";
    string details_title_font = assets_path + "OpenSans-Regular.ttf";

    graphics::Brush title_brush;
    title_brush.fill_secondary_color[0] = 1.0f;
    title_brush.fill_secondary_color[1] = 1.0f;
    title_brush.fill_secondary_color[2] = 1.0f;

    graphics::Brush button_title_brush;
    button_title_brush.fill_color[0] = 0.0f;
    button_title_brush.fill_color[1] = 0.0f;
    button_title_brush.fill_color[2] = 0.0f;
    button_title_brush.fill_secondary_color[0] = 0.0f;
    button_title_brush.fill_secondary_color[1] = 0.0f;
    button_title_brush.fill_secondary_color[2] = 0.0f;

    graphics::Brush background_brush;
    background_brush.fill_secondary_color[0] = 0.5f;
    background_brush.fill_secondary_color[1] = 0.5f;
    background_brush.fill_secondary_color[2] = 0.5f;

    graphics::Brush button_brushes[2] = {button_title_brush, background_brush};

    // not interactive text fields
    widgets.push_back(new TextWidget(title_brush, 35.0f, 10.0f,0, "Movie Browser", 5, title_font));
    widgets.push_back(new TextWidget(title_brush, 5.0f, 64.0f,0, "Director:", 2, details_title_font));
    widgets.push_back(new TextWidget(title_brush, 5.0f, 68.0f,0, "Stars:", 2, details_title_font));
    widgets.push_back(new TextWidget(title_brush, 5.0f, 72.0f,0, "Year:", 2, details_title_font));
    widgets.push_back(new TextWidget(title_brush, 5.0f, 76.0f,0, "Genres:", 2, details_title_font));

    widgets.push_back(new ButtonWidget(button_brushes, 10.0f, 80.0f,0, "", 1, 80, 0.05f, movie_title_font));

    widgets.push_back(new TextWidget(title_brush, 5.0f, 84.0f,0, "Filters:", 2, movie_title_font));

    // Buttons
    previous = new ButtonWidget(button_brushes, 5.0f, 50,0, "previous", 2, 10, 4, movie_title_font);
    next = new ButtonWidget(button_brushes, 85.0f, 50,0, "next", 2, 10, 4, movie_title_font);
    widgets.push_back(next);
    widgets.push_back(previous);

    // interactive text fields
    txt_title = new TextWidget(title_brush, 5.0f, 60.0f, 0, uninitialized, 2, movie_title_font);
    txt_director = new TextWidget(title_brush, 20.0f, 64.0f,0, uninitialized, 2, details_title_font);
    txt_stars = new TextWidget(title_brush, 20, 68.0f,0, uninitialized, 2, details_title_font);
    txt_year = new TextWidget(title_brush, 20, 72.0f,0, uninitialized, 2, details_title_font);
    txt_genres = new TextWidget(title_brush, 20, 76.0f,0, uninitialized, 2, details_title_font); 

    widgets.push_back(txt_title);
    widgets.push_back(txt_director);
    widgets.push_back(txt_stars);
    widgets.push_back(txt_year);
    widgets.push_back(txt_genres);

    // Images
    graphics::Brush image_brush;
    image_brush.fill_color[0] = 1.0f;
    image_brush.fill_color[1] = 1.0f;
    image_brush.fill_color[2] = 1.0f;
    image_brush.fill_opacity = 1.0f;
    image_brush.outline_opacity = 0.0f;
    image_brush.texture = assets_path + "questionmark.png";

    moviePicture = new ImageWidget(image_brush, 50, 35,0, 30, 40);
    widgets.push_back(moviePicture);

    // Filters
    int offset = 0;

    for (string s : years) {
        cout << "Adding year filter button: " << s << endl;
        widgets.push_back(new ButtonWidget(button_brushes, 15.0f + offset * 10, 88, 1, s, 2, 6, 3, movie_title_font));
        
        offset++;
    }

    offset = 0;

    for (string s : genres) {
        cout << "Adding genres filter button: " << s << endl;
        widgets.push_back( new ButtonWidget(button_brushes, 15.0f + offset * 15, 96, 2, s, 2, 10, 3, movie_title_font));
        
        
        offset++;
    }
}

// Draws widgets

void MovieBrowser::draw() {
    for (auto w : widgets) {
        w->draw();
    }
}

// Updates all widgets
// Checks if data have changed
// ms is the SGG update argument

void MovieBrowser::update(float ms) {
    graphics::MouseState mouse;
    graphics::getMouseState(mouse);

    mouse.cur_pos_x = (int)graphics::windowToCanvasX((float)mouse.cur_pos_x, false);
    mouse.cur_pos_y = (int)graphics::windowToCanvasY((float)mouse.cur_pos_y, false);

    for (auto w : widgets) {
        w->update(ms, mouse);
    }

    // Filters movie data

    if (dirty_filter) {
        if (selectedGenre == "" && selectedYear == "") {
            if (filteredMovies.size() != movies.size()) {
                filteredMovies = movies;
            }
        } else {
            filteredMovies.clear();

            for (Movie* m : movies) {
                bool matches = true;

                if (selectedYear != "") {
                    matches = matches && std::to_string(m->getYear()) == selectedYear;
                }

                if (selectedGenre != "") {
                    matches = matches && m->getGenres().find(selectedGenre) != -1;
                }

                if (matches) {
                    filteredMovies.push_back(m);
                }
            }

            cout << "Filter applied, result: " << filteredMovies.size() << endl;
        }

        currentMovie = 0;

        dirty_filter = false;
        dirty = true;
    }

    // Updates movie data

    if (dirty) {
        cout << "dirty updated, current movie: " << currentMovie << endl;

        if (currentMovie >= 0 && currentMovie < filteredMovies.size()) {
            Movie* m = filteredMovies[currentMovie];
            string path = assets_path + m->getImage();
            moviePicture->updateTexture(path);

            cout << "texture set to: " << path << endl;

            txt_title->setText(m->getName());
            txt_director->setText(m->getDirectors());
            txt_stars->setText(m->getStars());
            txt_year->setText(std::to_string(m->getYear()));
            txt_genres->setText(m->getGenres());
        } else {
            string path = assets_path + "questionmark.png";
            moviePicture->updateTexture(path);

            txt_title->setText(uninitialized);
            txt_director->setText(uninitialized);
            txt_stars->setText(uninitialized);
            txt_year->setText(uninitialized);
            txt_genres->setText(uninitialized);
        }

        dirty = false;

        // proxeiro
        for (auto widgett : widgets) {
            if (widgett->contains(mouse.cur_pos_x, mouse.cur_pos_y)) {
                if (widgett->getKindof() != 0) {

                    widgett->setHighlight(true);
                }
            }
        }

        Widget* cur_button = nullptr;
        for (auto widgett : widgets) {

            if (widgett->contains(mouse.cur_pos_x, mouse.cur_pos_y)) {

                cur_button = widgett;
            }
        }

        if (mouse.button_left_pressed && cur_button) {

            active_button = cur_button;
            active_button->setActive(true);

            /**/ for (auto widgett : widgets) {
                if (widgett->getKindof() == active_button->getKindof()) {
                   

                        if (widgett != active_button) {

                            widgett->setActive(false);
                            widgett->setHighlight(false);
                        }
                    }
            } /* /*
            else if (widgett->getKindof() == 2) {

                    for (auto widgett : gender_widgets) {

                        if (widgett != active_button) {

                            widgett->setActive(false);
                        } 
                    }
                } */
            }
        }
    }

            

        

    


// Processes mouse events
// Source is the button clicked

void MovieBrowser::clickEvent(ButtonWidget* source) {
    cout << "Button clicked: " << this << endl;

    if (source == previous) {
        if (currentMovie > 0) {
            currentMovie--;
            cout << "previous" << endl;
            dirty = true;
        }
    } else if (source == next) {
        if (currentMovie < filteredMovies.size() - 1) {
            currentMovie++;

            cout << "next" << endl;
            dirty = true;
        }
    } else {
        string label = source->getText();
        int value = atoi(label.c_str());
        if (value == 0) {
            if (selectedGenre != label) {
                cout << "genre filter set to: " << label << endl;
                selectedGenre = label;
            } else {
                cout << "genre cleared" << endl;
                selectedGenre = "";
            }
            dirty_filter = true;
        } else {
            if (selectedYear != label) {
                cout << "year filter set to: " << label << endl;
                selectedYear = label;
            } else {
                cout << "year cleared" << label << endl;
                selectedYear = "";
            }

            dirty_filter = true;
        }
    }
}