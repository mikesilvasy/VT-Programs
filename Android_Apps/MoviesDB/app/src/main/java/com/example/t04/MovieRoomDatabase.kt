package com.example.t04

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import androidx.room.TypeConverters


@Database(entities = [MovieItem::class], version = 1, exportSchema = false)
@TypeConverters(DateConverter::class)
abstract class MovieRoomDatabase: RoomDatabase(){
    abstract fun movieDao(): MovieItemDao

    companion object {
        @Volatile
        private var INSTANCE: MovieRoomDatabase? = null

        fun getDatabase(
            context: Context
        ): MovieRoomDatabase {
            val tempInstance = INSTANCE

            if (tempInstance != null) {
                return tempInstance
            }

            return INSTANCE ?: synchronized(this) {

                val instance = Room.databaseBuilder(
                    context.applicationContext,
                    MovieRoomDatabase::class.java,
                    "Movie_database"
                ).build()
                INSTANCE = instance
                instance
            }
        }
    }
}