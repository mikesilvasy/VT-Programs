package com.example.theedgefitness

import android.app.NotificationManager
import android.app.PendingIntent
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import androidx.core.app.NotificationCompat

class UpdateReceiver : BroadcastReceiver() {
    override fun onReceive(context: Context, intent: Intent) {
        var notificationManager: NotificationManager = context.getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
        var repeatingIntent: Intent = Intent(context, RepeatingActivity::class.java)

        repeatingIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP)
        var pendingIntent= PendingIntent.getActivity(context, 100, repeatingIntent, PendingIntent.FLAG_UPDATE_CURRENT)
        var builder = NotificationCompat.Builder(context)
            .setContentIntent(pendingIntent)
            .setSmallIcon(android.R.drawable.arrow_up_float)
            .setContentTitle("The Edge Fitness At VT")
            .setContentText("Reminder:  Go to the gym today")
            .setAutoCancel(true)
        notificationManager.notify(100, builder.build())
    }
}