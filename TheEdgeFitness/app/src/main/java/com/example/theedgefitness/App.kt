package com.example.theedgefitness

import android.app.Application
import android.app.NotificationChannel
import android.app.NotificationManager
import android.os.Build

class App: Application() {
    var CHANNEL_ID: String = "channel1"

    override fun onCreate() {
        super.onCreate()
        createNotificationChannel()
    }

    private fun createNotificationChannel() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            var channel: NotificationChannel = NotificationChannel(CHANNEL_ID, "Channel 1", NotificationManager.IMPORTANCE_HIGH)
            channel.description = "This is Channel"

            var manager: NotificationManager = getSystemService(NotificationManager::class.java)
            manager.createNotificationChannel(channel)

        }
    }
}