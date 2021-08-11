package com.example.theedgefitness

import android.app.AlarmManager
import android.app.Service
import android.content.Intent
import android.os.Binder
import android.os.IBinder
import android.util.Log
import android.widget.Toast

class NotificationService : Service() {
    inner class MyBinder: Binder(){
        fun getService():NotificationService{
            return this@NotificationService
        }
    }

    private val iBinder = MyBinder()

    override fun onBind(intent: Intent?): IBinder? {
        return iBinder
    }

    fun startAlarm() {
        Log.d("Apple", "Toasty")
    }
}