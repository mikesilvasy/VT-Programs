package com.example.theedgefitness

import android.app.*
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.graphics.BitmapFactory
import android.graphics.Color
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import android.util.Log
import android.widget.Toast
import androidx.appcompat.widget.ActionMenuView
import androidx.appcompat.widget.SearchView
import androidx.fragment.app.Fragment
import androidx.navigation.findNavController
import androidx.navigation.fragment.findNavController
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.android.synthetic.main.fragment_detail.*
import java.util.*
import androidx.core.os.HandlerCompat.postDelayed
import android.app.AlarmManager
import android.app.PendingIntent
import android.content.SharedPreferences
import android.view.*
import androidx.core.app.NotificationCompat
import androidx.core.app.NotificationManagerCompat
import androidx.lifecycle.ViewModelProviders
import com.google.firebase.database.DatabaseReference

var loggedIn: Boolean = false
var currIsProfile: Boolean = false
var currIsDiet: Boolean = false
var currIsPlans: Boolean = false
var currIsQuotes: Boolean = false

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //Notification
        var calendar: Calendar = Calendar.getInstance()
        calendar.set(Calendar.HOUR_OF_DAY, 8)
        calendar.set(Calendar.MINUTE, 36)
        calendar.set(Calendar.SECOND, 0)
        var sp: SharedPreferences = getSharedPreferences("TheEdgeFitnessAtVT", 0)
        sp.edit().putLong("CalendarTime", calendar.timeInMillis).commit()
        var intent: Intent = Intent(applicationContext, NotificationReceiver::class.java)
        var pendingIntent: PendingIntent = PendingIntent.getBroadcast(applicationContext, 100, intent, PendingIntent.FLAG_UPDATE_CURRENT)
        var alarmManager: AlarmManager = getSystemService(Context.ALARM_SERVICE) as AlarmManager
        alarmManager.setRepeating(AlarmManager.RTC_WAKEUP, calendar.timeInMillis, AlarmManager.INTERVAL_DAY, pendingIntent)

    }

    override fun onOptionsItemSelected(item: MenuItem?): Boolean {
        if (loggedIn) {
            when (item?.itemId) {
                R.id.profile_menu->{supportFragmentManager.beginTransaction().replace(fragment.id, ProfileAttributesFragment()).commit()
                                    return true}
                R.id.fitness_plans_menu->{supportFragmentManager.beginTransaction().replace(fragment.id, PlansFragment()).commit()
                                    return true}
                R.id.diet_tracking_menu->{supportFragmentManager.beginTransaction().replace(fragment.id, DietTrackingFragment()).commit()
                                    return true}
            }
        }
        else {
            Toast.makeText(this, "Please sign in before using the menu.", Toast.LENGTH_LONG).show()
        }
        return super.onOptionsItemSelected(item)
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        var inflater: MenuInflater = menuInflater
        inflater.inflate(R.menu.options_menu, menu)
        return true
    }

    override fun onKeyDown(keyCode: Int, event: KeyEvent): Boolean {
        if (Integer.parseInt(android.os.Build.VERSION.SDK) > 5
                && keyCode == KeyEvent.KEYCODE_BACK
                && event.getRepeatCount() == 0) {
            onBackPressed()
            return true
        }
        return super.onKeyDown(keyCode, event)
    }

    override fun onBackPressed() {
        if (currIsProfile || currIsDiet || currIsPlans) {
            supportFragmentManager.beginTransaction().replace(fragment.id, PlansFragment()).commit()
        }
        if (currIsQuotes) {

        }
        else {
            super.onBackPressed()
        }
    }
}
