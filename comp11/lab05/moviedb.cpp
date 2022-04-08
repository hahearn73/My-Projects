/*
    Harry Ahearn
    moviedb.cpp
    Purpose: Interact with arrays of structs by manipulating
            and searching a movie database
    Written by: Keisha Mukasa
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int NUM_MOVIES = 450;
const int NUM_ACTORS = 5;

struct Movie
{
    string title;
    int year;
    double gross;
    string director;
    string actors[NUM_ACTORS];
};

void read_movie_data(Movie movies[NUM_MOVIES]);
void print_movies(Movie movies[NUM_MOVIES]);
void findMovie(Movie movie_list[NUM_MOVIES], string title);
void printMoviesInYear(Movie movie_list[NUM_MOVIES], int year);
void grossData(Movie movie_list[NUM_MOVIES]);
void biggestYear(Movie movie_list[NUM_MOVIES]);

int main()
{
    // This line of code declares a list of 450 movies obje
    Movie movie_list[NUM_MOVIES];
    // This function call is populating the movie list with all
    // the movies in the file. Do not worry about its implementation.
    read_movie_data(movie_list);

    /* Your code goes here */
    
    // problem 1 find movie
    string title;
    cout << "Input movie name: ";
    getline(cin, title);
    findMovie(movie_list, title);
    
    // problem 2 find movies in Year
    int year;
    cout << "Input year: ";
    cin >> year;
    printMoviesInYear(movie_list, year);
    
    // problem 3
    grossData(movie_list);
    
    //problem 4
    biggestYear(movie_list);

    return 0;
}
/*


YOUR FUNCTIONS GO HERE


*/

/*
 * findMovie
 * parameters: the array of movies and the title to find
 * purpose: print out the movie with that titles information
 * void: no return
 */
void findMovie(Movie movie_list[NUM_MOVIES], string title) {
    bool flag = true;
    for (int i = 0; i < NUM_MOVIES; i++) {
        if (movie_list[i].title == title) {
            flag = false;
            cout << movie_list[i].year << "\n" << movie_list[i].gross << "\n" << movie_list[i].director << endl;
            for (int j = 0; j < NUM_ACTORS; j++) {
                cout << movie_list[i].actors[j] << endl;
            }
        }
    }
    if (flag) {
        cout << title << " was not found in the movie database" << endl;
    }
}

/*
 * printMoviesInYear
 * parameters: list of movies and the year
 * purpose: prints out all movies in the year specified
 * void - no return
 */
void printMoviesInYear(Movie movie_list[NUM_MOVIES], int year) {
    bool flag = true;
    for (int i = 0; i < NUM_MOVIES; i++) {
        if (movie_list[i].year == year) {
            cout << movie_list[i].title << endl;
            flag = false;
        }
    }
    if (flag) {
        cout << "There are no movies from " << year << endl;
    }
}

/*
 * grossData
 * parameters: the list of movies 
 * purpose: prints out the highest and lowest grossing movie, and the average
 * void - no return
 */
void grossData(Movie movie_list[NUM_MOVIES]) {
    Movie highestGrossingMovie = movie_list[0];
    Movie lowestGrossingMovie = movie_list[0];
    double total = 0;
    for (int i = 0; i < NUM_MOVIES; i++) {
        total += movie_list[i].gross;
        if (movie_list[i].gross > highestGrossingMovie.gross) {
            highestGrossingMovie = movie_list[i];
        }
        if (movie_list[i].gross < lowestGrossingMovie.gross) {
            lowestGrossingMovie = movie_list[i];
        }
    }
    double average = total / NUM_MOVIES;
    cout << "Highest grossing movie: " << highestGrossingMovie.title << endl;
    cout << "Lowest grossing movie: " << lowestGrossingMovie.title << endl;
    cout << "Average gross: " << average << endl;
}

/*
 * biggestYear
 * parameters: the list of movies 
 * purpose: prints out the highest grossing year 
 * void - no return 
 */
void biggestYear(Movie movie_list[NUM_MOVIES]) {
    double yearlyGross[2018 - 1900 + 1] = {0}; // sets the array to all zeroes
    for (int i = 0; i < NUM_MOVIES; i++) { 
        yearlyGross[movie_list[i].year - 1900] += movie_list[i].gross;
    }
    // for loop adds the gross from each movie to its corresponding year
    
    int greatestYear;
    double greatestGross = 0;
    for (int i = 0; i <= 2018 - 1900; i++) {
        if (yearlyGross[i] > greatestGross) {
            greatestGross = yearlyGross[i];
            greatestYear = i + 1900;
        }
    }
    cout << greatestYear << endl;
}

/************************************************************
 *                     NOTE                               
 * The function below are part of the starter code that enable
 * you to read in from a file. You do not need to understand
 * the code below to complete the lab and we encourage you to
 * ignore this code. This implementation will be covered in the
 * future but is not currently required for lab or hw.
*************************************************************/

/*  
*   READ_MOVIE_DATA
*   Parameters: Empty movie array
*   Purpose: Read lists of movies data from a file and store in array
*   Returns: Does not return anything
*/
void read_movie_data(Movie movies[NUM_MOVIES])
{
    // ifstream object declaration in order to open and read
    // from a file
    ifstream infile;
    string filename = "moviedata.txt";

    // open file
    infile.open(filename);

    // check if file successfully opened if it isn't the program is
    // exited immediately
    if (infile.fail())
    {
        cerr << "ERROR: Error opening file, please check file name: "
             << filename << endl;
        exit(EXIT_FAILURE);
    }

    // read through file
    for (int i = 0; i < NUM_MOVIES; i++)
    {
        getline(infile, movies[i].title);
        infile >> movies[i].year;
        infile >> movies[i].gross;
        infile.ignore();
        getline(infile, movies[i].director);

        // reads in each actors name
        for (int j = 0; j < NUM_ACTORS; j++)
        {
            getline(infile, movies[i].actors[j]);
        }
    }
}