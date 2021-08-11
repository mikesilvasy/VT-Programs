package com.example.t04

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey
import java.util.*


@Entity(tableName = "movie_table")
data class MovieItem(@PrimaryKey @ColumnInfo(name ="id") var id: Long,
                 @ColumnInfo(name ="vote_count") var vote_count: Long,
                 @ColumnInfo(name ="vote_average") var vote_average: Float,
                 @ColumnInfo(name ="title") var title: String,
                 @ColumnInfo(name ="popularity") var popularity: Float,
                 @ColumnInfo(name ="poster_path") var poster_path: String,
                 @ColumnInfo(name ="overview") var overview: String,
                 @ColumnInfo(name ="release_date") var release_date: Date

)


