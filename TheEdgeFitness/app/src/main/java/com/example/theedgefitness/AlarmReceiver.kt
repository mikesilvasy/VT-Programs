package com.example.theedgefitness

import android.app.AlarmManager
import android.content.Context.ALARM_SERVICE
import androidx.core.content.ContextCompat.getSystemService
import android.app.PendingIntent
import android.content.Intent
import androidx.core.content.ContextCompat.startActivity
import android.widget.Toast
import android.content.BroadcastReceiver
import android.content.Context
import java.util.*


class AlarmReceiver : BroadcastReceiver() {

    override fun onReceive(context: Context, intent: Intent) {
        val message = "Hellooo, alrm worked ----"
        Toast.makeText(context, message, Toast.LENGTH_SHORT).show()
    }

    fun setAlarm(context: Context) {

        // get a Calendar object with current time
        val cal = Calendar.getInstance()
        // add 30 seconds to the calendar object
        cal.add(Calendar.SECOND, 30)
        val intent = Intent(context, AlarmReceiver::class.java)
        val sender = PendingIntent.getBroadcast(context, 192837, intent, PendingIntent.FLAG_UPDATE_CURRENT)

        // Get the AlarmManager service
        val am = context.getSystemService(ALARM_SERVICE) as AlarmManager
        am.set(AlarmManager.RTC_WAKEUP, cal.getTimeInMillis(), sender)
    }
}