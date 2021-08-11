package com.example.theedgefitness


import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.Toast
import androidx.appcompat.widget.AppCompatEditText
import com.google.android.material.textfield.TextInputEditText
import android.text.Editable
import android.text.TextUtils
import android.text.TextWatcher
import android.util.Log
import android.widget.EditText


// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val ARG_PARAM1 = "param1"
private const val ARG_PARAM2 = "param2"
var totalCalories: Int = 0
var totalWater: Int = 0

/**
 * A simple [Fragment] subclass.
 *
 */
class DietTrackingFragment : Fragment() {
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val v = inflater.inflate(R.layout.fragment_diet_tracking, container, false)

        currIsProfile = false
        currIsDiet = true
        currIsPlans = true
        currIsQuotes = false

        val inputCalories = v.findViewById<EditText>(R.id.inputCalories)
        val enterCalories: Button = v.findViewById<Button>(R.id.enterCalories)
        enterCalories.setOnClickListener {
            var caloriesString: String = inputCalories.text.toString()
            if (!TextUtils.isEmpty(caloriesString)) {
                var calories: Int = caloriesString.toInt()
                if (calories in 1..1500) {
                    totalCalories += calories
                    inputCalories.text!!.clear()
                    showCaloriesAndWater()
                }
                else {
                    Toast.makeText(context, "Please enter a number of calories between 1 and 1500 inclusive.",
                        Toast.LENGTH_LONG).show()
                }
            }
        }

        val inputWater = v.findViewById<EditText>(R.id.inputWater)
        val enterWater: Button = v.findViewById<Button>(R.id.enterWater)
        enterWater.setOnClickListener {
            var waterString: String = inputWater.text.toString()
            if (!TextUtils.isEmpty(waterString)) {
                var water: Int = waterString.toInt()
                if (water in 1..64) {
                    totalWater+= water
                    inputWater.text!!.clear()
                    showCaloriesAndWater()
                }
                else {
                    Toast.makeText(context, "Please enter an amount of water in fl. oz. between 1 and 64 inclusive.",
                        Toast.LENGTH_LONG).show()
                }
            }
        }

        return v
    }

    private fun showCaloriesAndWater() {
        Toast.makeText(context, "Total Calories:  $totalCalories calories\nTotal Water:  $totalWater fl. oz.",
            Toast.LENGTH_LONG).show()
    }
}
