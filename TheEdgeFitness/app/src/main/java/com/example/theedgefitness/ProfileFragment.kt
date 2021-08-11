package com.example.theedgefitness


import android.os.Bundle
import android.text.TextUtils
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.*
import androidx.lifecycle.ViewModelProviders
import androidx.navigation.findNavController


// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val ARG_PARAM1 = "param1"
private const val ARG_PARAM2 = "param2"

/**
 * A simple [Fragment] subclass.
 *
 */
class ProfileFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val v = inflater.inflate(R.layout.fragment_profile, container, false)

        currIsProfile = false
        currIsDiet = false
        currIsPlans = false
        loggedIn = false
        currIsQuotes = false

        val genderSpinner: Spinner = v.findViewById(R.id.genderSpinner)
        ArrayAdapter.createFromResource(context,
            R.array.genders,
            android.R.layout.simple_spinner_item
        ).also { adapter ->
            adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
            genderSpinner.adapter = adapter
        }

        genderSpinner.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
            override fun onNothingSelected(parent: AdapterView<*>?) {

            }
            override fun onItemSelected(parent: AdapterView<*>?, view: View?, position: Int, id: Long) {

            }
        }

        val inputEmail = v.findViewById<EditText>(R.id.emailSignup)
        val inputPassword = v.findViewById<EditText>(R.id.passwordSignup)
        val inputConfirmPassword = v.findViewById<EditText>(R.id.confirmPassword)
        val inputFirstName = v.findViewById<EditText>(R.id.pageFirstName)
        val inputLastName = v.findViewById<EditText>(R.id.pageLastName)
        val inputAge = v.findViewById<EditText>(R.id.pageAge)

        val model = activity?.let { ViewModelProviders.of(it).get(MyViewModel::class.java)}

        (v.findViewById<Button>(R.id.createAccount)).setOnClickListener {
            var email = inputEmail.text.toString()
            var password = inputPassword.text.toString()
            var confirmPassword = inputConfirmPassword.text.toString()
            var firstName = inputFirstName.text.toString()
            var lastName = inputLastName.text.toString()
            var age = inputAge.text.toString()
            var gender = genderSpinner.selectedItem.toString()
            if (!filledOut(email, password, confirmPassword, firstName, lastName, age)) {
                Toast.makeText(context, "Please fill in all information.", Toast.LENGTH_LONG).show()
            }
            else if (!model?.isValidUser(email)!!) {
                Toast.makeText(context, "$email is not a valid email", Toast.LENGTH_LONG).show()
            }
            else if (model?.hasMadeAccount(email)) {
                Toast.makeText(context, "$email is already registered.\nPlease log in.", Toast.LENGTH_LONG).show()
            }
            else if (!validAge(age.toInt())) {
                Toast.makeText(context, "Please enter an age between 18 and 60 inclusive.", Toast.LENGTH_LONG).show()
            }
            else if (!longEnoughPassword(password)) {
                Toast.makeText(context, "The password must be at least 8 characters long.", Toast.LENGTH_LONG).show()
            }
            else if (password != confirmPassword) {
                Toast.makeText(context, "Confirm Password does not match Password.", Toast.LENGTH_LONG).show()
            }
            else {
                var userIndex: Int = model?.readUserIndex()
                loggedIn = true
                isMakingNewProfile = true
                model?.saveInfo(email, password, firstName, lastName, age, gender, userIndex)
                model?.incrementUserIndex()
                currUser = email
                v.findNavController().navigate(R.id.quotesFragment)
            }
        }

        return v
    }

    private fun filledOut(email: String, password: String, confirmPassword: String, firstName: String, lastName: String,
                          age: String): Boolean {
        return !TextUtils.isEmpty(email) && !TextUtils.isEmpty(password) && !TextUtils.isEmpty(confirmPassword) &&
                !TextUtils.isEmpty(firstName) && !TextUtils.isEmpty(lastName) && !TextUtils.isEmpty(age)
    }

    private fun longEnoughPassword(password: String): Boolean {
        return password.length >= 8
    }

    private fun validAge(age: Int): Boolean {
        return age in 18..60
    }


}
