package com.example.t04

import androidx.annotation.WorkerThread
import androidx.lifecycle.LiveData

class MovieItemRepository(private val movieDao: MovieItemDao){

//    val allMoviesByTitle: LiveData<List<MovieItem>> = movieDao.getAllMoviesTitle()
//    val allMoviesByVote: LiveData<List<MovieItem>> = movieDao.getAllMoviesVote()
    var allMovies: LiveData<List<MovieItem>> = movieDao.getAllMovies()

    fun sortByTitle() {
        allMovies = movieDao.getAllMoviesTitle()
    }

    fun sortByVote() {
        allMovies = movieDao.getAllMoviesVote()
    }
    @WorkerThread
    fun insert(movie: MovieItem){
        movieDao.insertMovie(movie)
    }

    @WorkerThread
    fun deleteAll(){
        movieDao.DeleteAll()
    }


}