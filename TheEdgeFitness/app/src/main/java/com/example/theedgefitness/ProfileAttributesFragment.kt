package com.example.theedgefitness


import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.lifecycle.ViewModelProviders


// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val ARG_PARAM1 = "param1"
private const val ARG_PARAM2 = "param2"

/**
 * A simple [Fragment] subclass.
 *
 */
class ProfileAttributesFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val v = inflater.inflate(R.layout.fragment_profile_attributes, container, false)

        currIsProfile = true
        currIsDiet = false
        currIsPlans = false
        currIsQuotes = false

        var dailyCalories: TextView = v.findViewById<TextView>(R.id.pageCalories)
        dailyCalories.text = "Today\'s Calories:  $totalCalories calories"
        var dailyWater: TextView = v.findViewById<TextView>(R.id.pageWater)
        dailyWater.text = "Today\'s Water:  $totalWater fl. oz."

        val model = activity?.let { ViewModelProviders.of(it).get(MyViewModel::class.java)}

        var user: UserInfo = model?.getCurrentUser(currUser)!!
        var firstName: TextView = v.findViewById(R.id.pageFirstName)
        firstName.text = "First Name:  " + user.firstName
        var lastName: TextView = v.findViewById(R.id.pageLastName)
        lastName.text = "Last Name:  " + user.lastName
        var age: TextView = v.findViewById(R.id.pageAge)
        age.text = "Age:  " + user.age
        var gender: TextView = v.findViewById(R.id.pageGender)
        gender.text = "Gender:  " + user.gender
        var email: TextView = v.findViewById(R.id.pageEmail)
        email.text = "Email:  " + user.email
        var password: TextView = v.findViewById(R.id.pagePassword)
        password.text = "Password:  " + user.password

        return v
    }


}
