package com.example.theedgefitness

import androidx.core.app.NotificationManagerCompat
import android.app.PendingIntent
import android.content.Intent
import android.R
import android.app.Notification
import android.util.Log
import androidx.core.app.JobIntentService


class NotificationIntentService : JobIntentService() {
    private val NOTIFICATION_ID = 3

    override fun onHandleWork(intent: Intent) {
        Log.d("APPlE", "Service")
        val builder = Notification.Builder(this)
        builder.setContentTitle("My Title")
        builder.setContentText("This is the Body")
        builder.setSmallIcon(R.drawable.arrow_up_float)
        val notifyIntent = Intent(this, MainActivity::class.java)
        val pendingIntent = PendingIntent.getActivity(this, 2, notifyIntent, PendingIntent.FLAG_UPDATE_CURRENT)
        //to be able to launch your activity from the notification
        builder.setContentIntent(pendingIntent)
        val notificationCompat = builder.build()
        val managerCompat = NotificationManagerCompat.from(this)
        managerCompat.notify(NOTIFICATION_ID, notificationCompat)
    }
}