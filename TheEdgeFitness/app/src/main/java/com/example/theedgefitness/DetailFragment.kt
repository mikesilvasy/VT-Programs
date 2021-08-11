package com.example.theedgefitness


import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import com.bumptech.glide.Glide


// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val ARG_PARAM1 = "param1"
private const val ARG_PARAM2 = "param2"

/**
 * A simple [Fragment] subclass.
 *
 */
class DetailFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val v = inflater.inflate(R.layout.fragment_detail, container, false)

        currIsProfile = false
        currIsDiet = false
        currIsPlans = false
        currIsQuotes = false

        v.findViewById<TextView>(R.id.exercise).text = clickedExercise.Exercise

        var sR: String = ""
        var i: Int = 0
        while (i < clickedExercise.setsAndReps.size) {
            if (specialCase == null) {
                sR += "Set " + (i + 1).toString() + ":  " + clickedExercise.setsAndReps.get(i).toString() + " Reps\n"
            }
            else {
                sR += "Set " + (i + 1).toString() + ":  " + clickedExercise.setsAndReps.get(i).toString() + " $specialCase\n"
            }
            i += 1
        }
        v.findViewById<TextView>(R.id.setsReps).text = sR

        val gif: ImageView = v.findViewById<ImageView>(R.id.exerciseGif)
        addExerciseGif(gif)

        return v
    }

    private fun addExerciseGif(gif: ImageView) {
        var exercise: String = clickedExercise.Exercise
        when (exercise) {
            "Bench Press"->Glide.with(this).load(R.drawable.benchpress).into(gif)
            "Incline Bench Press"->Glide.with(this).load(R.drawable.inclinebenchpress).into(gif)
            "Dumbell Bench Press"->Glide.with(this).load(R.drawable.dumbellbenchpress).into(gif)
            "Incline Dumbell Bench Press"->Glide.with(this).load(R.drawable.inclinedumbellbenchpress).into(gif)
            "Bicep Curls"->Glide.with(this).load(R.drawable.bicepcurls).into(gif)
            "Dumbell Overhead Press"->Glide.with(this).load(R.drawable.dumbelloverheadpress).into(gif)
            "Tricep Extension"->Glide.with(this).load(R.drawable.tricepextension).into(gif)
            "Seated Machine Dips"->Glide.with(this).load(R.drawable.seatedmachinedips).into(gif)
            "Stair Master"->Glide.with(this).load(R.drawable.stairmaster).into(gif)
            "Treadmill"->Glide.with(this).load(R.drawable.treadmill).into(gif)
            "Bike"->Glide.with(this).load(R.drawable.bikecardio).into(gif)
            "Spinner"->Glide.with(this).load(R.drawable.spinner).into(gif)
            "Elliptical"->Glide.with(this).load(R.drawable.elliptical).into(gif)
            "Swimming"->Glide.with(this).load(R.drawable.swimming).into(gif)
            "Plank"->Glide.with(this).load(R.drawable.plank).into(gif)
            "V Sit-Ups"->Glide.with(this).load(R.drawable.vsitups).into(gif)
            "Russian Twists"->Glide.with(this).load(R.drawable.russiantwists).into(gif)
            "SuperMan"->Glide.with(this).load(R.drawable.superman).into(gif)
            "Leg Raises"->Glide.with(this).load(R.drawable.legraises).into(gif)
            "Dead Bug"->Glide.with(this).load(R.drawable.deadbug).into(gif)
            "Windshield Wiper"->Glide.with(this).load(R.drawable.windshieldwiper).into(gif)
            "Bicycle Kicks"->Glide.with(this).load(R.drawable.bicyclekicks).into(gif)
            "6-Inch Leg Raises"->Glide.with(this).load(R.drawable.sixinchlegraises).into(gif)
            "Stability Ball Crunch"->Glide.with(this).load(R.drawable.stabilityballcrunch).into(gif)
            "Pull-Ups"->Glide.with(this).load(R.drawable.pullups).into(gif)
            "Dips"->Glide.with(this).load(R.drawable.dips).into(gif)
            "Squats"->Glide.with(this).load(R.drawable.squats).into(gif)
            "Single Leg Bench Lunges"->Glide.with(this).load(R.drawable.singlelegbenchlunges).into(gif)
            "Front Squats"->Glide.with(this).load(R.drawable.frontsquats).into(gif)
            "Dead Lifts"->Glide.with(this).load(R.drawable.deadlift).into(gif)
            "Leg Press"->Glide.with(this).load(R.drawable.legpress).into(gif)
            "Isolated Leg Press"->Glide.with(this).load(R.drawable.isolatedlegpress).into(gif)
        }
    }


}
