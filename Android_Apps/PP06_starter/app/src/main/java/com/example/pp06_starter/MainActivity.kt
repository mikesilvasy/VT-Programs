package com.example.pp06_starter

import android.content.Context
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.view.animation.Animation
import android.view.animation.RotateAnimation
import android.widget.Button
import android.widget.ImageView
import java.lang.Math.atan

class MainActivity : AppCompatActivity(), SensorEventListener {

    var currentDegree = 0.0f
    lateinit var left: Button
    lateinit var right: Button
    //suggested picture: https://clipart.wpblink.com/wallpaper-1606027
    lateinit var image: ImageView

    private lateinit var sensorManager: SensorManager
    private var accel: Sensor? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        left = findViewById(R.id.left)
        right = findViewById(R.id.right)
        image = findViewById(R.id.plane)

//        left.setOnClickListener(this)
//        right.setOnClickListener(this)
        left.visibility = View.INVISIBLE
        right.visibility = View.INVISIBLE
        image.setImageResource(R.drawable.airplane)

        sensorManager = getSystemService(Context.SENSOR_SERVICE) as SensorManager
        accel = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER)


    }

    override fun onSensorChanged(event: SensorEvent?) {
        var x = event!!.values[0]
        var y = event!!.values[1]
        var angle = atan((x / y).toDouble())

        if (angle < 0) {
            val rotateAnimation = RotateAnimation(
                currentDegree, currentDegree + angle.toFloat(),
                Animation.RELATIVE_TO_SELF, 0.5f,
                Animation.RELATIVE_TO_SELF, 0.5f)
            rotateAnimation.duration = 10000
            rotateAnimation.fillAfter = true

            image.animation = rotateAnimation
            currentDegree += angle.toFloat()
        }
        if (angle > 0) {
            val rotateAnimation = RotateAnimation(
                currentDegree, currentDegree - angle.toFloat(),
                Animation.RELATIVE_TO_SELF, 0.5f,
                Animation.RELATIVE_TO_SELF, 0.5f)
            rotateAnimation.duration = 10000
            rotateAnimation.fillAfter = true

            image.animation = rotateAnimation
            currentDegree -= angle.toFloat()
        }
    }

    override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {

    }

    override fun onPause() {
        super.onPause()
        sensorManager.unregisterListener(this)
    }

    override fun onResume() {
        super.onResume()
        accel?.also { sensor -> sensorManager.registerListener(this, sensor, SensorManager.SENSOR_DELAY_NORMAL)}
    }


//    override fun onClick(v: View?) {
//
//
//        if(v!=null && v == left){
//            val rotateAnimation = RotateAnimation(
//                currentDegree,
//                currentDegree-45f,
//                Animation.RELATIVE_TO_SELF, 0.5f,
//                Animation.RELATIVE_TO_SELF, 0.5f)
//            rotateAnimation.duration = 1000
//            rotateAnimation.fillAfter = true
//
//            image.startAnimation(rotateAnimation)
//            currentDegree -= 45f
//        }
//        if(v!=null && v == right){
//            val rotateAnimation = RotateAnimation(
//                currentDegree,
//                currentDegree+45f,
//                Animation.RELATIVE_TO_SELF, 0.5f,
//                Animation.RELATIVE_TO_SELF, 0.5f)
//            rotateAnimation.duration = 1000
//            rotateAnimation.fillAfter = true
//
//            image.startAnimation(rotateAnimation)
//            currentDegree += 45f
//
//        }
//    }
}
