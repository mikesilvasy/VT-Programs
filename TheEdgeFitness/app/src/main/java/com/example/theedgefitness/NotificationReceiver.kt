package com.example.theedgefitness

import android.app.Notification
import android.app.NotificationManager
import android.app.PendingIntent
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.content.SharedPreferences
import android.graphics.BitmapFactory
import android.util.Log
import androidx.core.app.NotificationCompat
import androidx.core.app.NotificationManagerCompat
import androidx.lifecycle.ViewModelProviders
import com.google.firebase.database.*

class NotificationReceiver: BroadcastReceiver() {
    override fun onReceive(context: Context?, intent: Intent?) {
        Log.d("NotifyAlarm", "Notified")
        var sp: SharedPreferences = context!!.getSharedPreferences("TheEdgeFitnessAtVT", 0)
        if (System.currentTimeMillis() >= sp.getLong("CalendarTime", 0) && System.currentTimeMillis() <=
                sp.getLong("CalendarTime", 0) + (1000 * 60)) {
            var notificationManager: NotificationManagerCompat = NotificationManagerCompat.from(context!!)
            var repeatingIntent: Intent = Intent(context, MainActivity::class.java)
            repeatingIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP)
            var pendingIntent: PendingIntent = PendingIntent.getActivity(context, 100, repeatingIntent, PendingIntent.FLAG_UPDATE_CURRENT)

            var notification: Notification = NotificationCompat.Builder(context!!, "channel1")
                .setContentIntent(pendingIntent)
                .setSmallIcon(R.drawable.vt_logo)
                .setLargeIcon(BitmapFactory.decodeResource(context.resources, R.drawable.bicepcurlpic))
                .setContentTitle("Reminder:")
                .setContentText("Go to the gym today")
                .setPriority(NotificationCompat.PRIORITY_HIGH)
                .setAutoCancel(true)
                .build()
            notificationManager.notify(1, notification)

            //From ViewModel
            val mDatabase: FirebaseDatabase = FirebaseDatabase.getInstance()
            val mRefQuoteIndex: DatabaseReference = mDatabase.getReference("QuotesIndex")
            var qIndex: Int = 0
            mRefQuoteIndex.addValueEventListener(object : ValueEventListener {
                override fun onDataChange(dataSnapshot: DataSnapshot) {
                    var keys: ArrayList<String> = ArrayList<String>()
                    for (keyNode in dataSnapshot.children) {
                        keys.add(keyNode.key!!)
                        qIndex = keyNode.getValue(Int::class.java)!!
                    }
                }

                override fun onCancelled(error: DatabaseError) {

                }
            })
            mRefQuoteIndex.child("i").setValue(qIndex + 1)
        }
    }
}