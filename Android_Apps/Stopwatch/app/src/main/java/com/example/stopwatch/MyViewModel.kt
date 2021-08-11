package com.example.stopwatch

import android.os.AsyncTask
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import kotlinx.coroutines.*
import java.util.*

//This class shows off three different ways of performing short lived background tasks.
class MyViewModel: ViewModel(){
    //Java 'Timer'
    private var timer = Timer()

    //Live data for passing seconds to DisplayFragment
    private val mElapsedTime = MutableLiveData<Long>()

    //Live data for saving laps
    private val mLap = MutableLiveData<String>()

    //1000ms
    private val ONE_SECOND = 1000

    private var running = false

    private var totalSeconds: Long = 0

    private var totalLaps = ArrayList<String>()

    private var lapCounter: Int = 1

    //constructor call
    init {
        mLap.value = "Laps:"
        mElapsedTime.value= 0
    }

    //ControlFragment will invoke this
    fun start(){
        if (!running) {
            mElapsedTime.value = totalSeconds
            timer = Timer()
            // Option 1 -- Timer : Update the elapsed time every second.
            timer.scheduleAtFixedRate(object : TimerTask() {
                // runs on a non-UI thread.
                override fun run() {
                    totalSeconds++
                    //'posting' new values every second to the MutableLiveData object
                    // notice that this is happening on a non-UI thread.
                    mElapsedTime.postValue(totalSeconds)
                }
                //delay              //period
            }, ONE_SECOND.toLong(), ONE_SECOND.toLong())
            running=!running
        }
    }

    fun stop() {
        if (running) {
            timer.cancel()
            running = !running
        }
    }

    fun reset() {
        stop()
        totalSeconds = 0
        mElapsedTime.value = 0
        totalLaps.clear()
        lapCounter = 1
        running = false
    }

    //DisplayFragment will use this method to retrieve the live data object.
    fun getElapsedTime(): LiveData<Long> {
        return mElapsedTime
    }

    fun addLap() {
        var minutes = totalSeconds / 60
        var minutes0 = ""
        if (minutes < 10) {
            minutes0 = "0"
        }

        var seconds = totalSeconds % 60
        var seconds0 = ""
        if (seconds < 10) {
            seconds0 = "0"
        }
        var time = "$minutes0$minutes:$seconds0$seconds"
        totalLaps.add("Lap$lapCounter $time")
        lapCounter++
    }

    fun totalLaps(): ArrayList<String> {
        return totalLaps
    }
}