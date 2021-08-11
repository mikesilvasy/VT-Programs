package com.example.theedgefitness


import android.content.*
import android.os.Bundle
import android.os.IBinder
import android.text.TextUtils
import android.util.Log
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import androidx.lifecycle.ViewModelProviders
import androidx.navigation.findNavController
import org.w3c.dom.Text

var isMakingNewProfile: Boolean = false


// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val ARG_PARAM1 = "param1"
private const val ARG_PARAM2 = "param2"

lateinit var currUser: String

/**
 * A simple [Fragment] subclass.
 *
 */
class LoginFragment : Fragment() {

//    var notificationService: NotificationService? = null
//    var notificationReceiver: NotificationReceiver? = null
//    var startNotificationServiceIntent: Intent? = null
//    var isInitialized = false
//    var isBound = false
//
//    private val notificationServiceConnection = object : ServiceConnection {
//        override fun onServiceConnected(componentName: ComponentName, iBinder: IBinder) {
//            val binder = iBinder as NotificationService.MyBinder
//            notificationService = binder.getService()
//            isBound = true
//        }
//        override fun onServiceDisconnected(componentName: ComponentName?) {
//            notificationService = null
//            isBound = false
//        }
//    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val v = inflater.inflate(R.layout.fragment_login, container, false)

        val model = activity?.let { ViewModelProviders.of(it).get(MyViewModel::class.java)}
        model?.readValidUsers()
        model?.readUsers()
        model?.readQuotes()

        loggedIn = false
        currIsProfile = false
        currIsDiet = false
        currIsPlans = false
        currIsQuotes = false

        val inputEmail = v.findViewById<EditText>(R.id.email)
        val inputPassword = v.findViewById<EditText>(R.id.password)
        (v.findViewById<Button>(R.id.signupButton)).setOnClickListener {
            v.findNavController().navigate(R.id.profileFragment)
        }
        (v.findViewById<Button>(R.id.loginButton)).setOnClickListener{
            var email: String = inputEmail.text.toString()
            var password: String = inputPassword.text.toString()
            if (TextUtils.isEmpty(email) || TextUtils.isEmpty(password)) {
                Toast.makeText(context, "Please enter a username/password.", Toast.LENGTH_LONG).show()
            }
            else if (!model?.isValidUser(email)!!) {
                Toast.makeText(context, "$email is not a valid email.", Toast.LENGTH_LONG).show()
            }
            else if (!model?.hasMadeAccount(email)) {
                Toast.makeText(context, "$email has not been registered.\nPlease create an account.",
                    Toast.LENGTH_LONG).show()
            }
            else if (!model?.doesPasswordMatch(email, password)) {
                Toast.makeText(context, "Incorrect password.", Toast.LENGTH_LONG).show()
            }
            else {
                loggedIn = true
                currUser = email
                v.findNavController().navigate(R.id.quotesFragment)
            }
        }

//        startNotificationServiceIntent = Intent(activity, NotificationService::class.java)
//        if (!isInitialized) {
//            Log.d("Apple", "Play")
//            activity!!.startService(startNotificationServiceIntent)
//            isInitialized = true
//        }
//        notificationReceiver = NotificationReceiver()
//
//        activity!!.bindService(startNotificationServiceIntent, notificationServiceConnection, Context.BIND_AUTO_CREATE)
//        activity!!.registerReceiver(notificationReceiver, IntentFilter("complete intent"))
//
//        Log.d("Apple", "$notificationService")

        return v
    }
}
