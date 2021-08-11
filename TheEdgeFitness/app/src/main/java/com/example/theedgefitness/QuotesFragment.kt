package com.example.theedgefitness


import android.content.SharedPreferences
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.view.animation.AccelerateInterpolator
import android.view.animation.AlphaAnimation
import android.view.animation.AnimationSet
import android.view.animation.DecelerateInterpolator
import android.widget.Button
import android.widget.TextView
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
class QuotesFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val v = inflater.inflate(R.layout.fragment_quotes, container, false)

        currIsProfile = false
        currIsDiet = false
        currIsPlans = false
        loggedIn = false
        currIsQuotes = true

        val model = activity?.let { ViewModelProviders.of(it).get(MyViewModel::class.java)}
        var quoteIndex: Int = model?.readQuoteIndex()!!

        var quote: TextView = v.findViewById(R.id.quote)
        quote.text = model?.pullQuote(quoteIndex)!!
        val fadeIn = AlphaAnimation(0f, 1f)
        fadeIn.interpolator = DecelerateInterpolator() //add this
        fadeIn.duration = 1000 * 3
        val animation = AnimationSet(false) //change to false
        animation.addAnimation(fadeIn)
        quote.animation = animation

        val nextButton: Button = v.findViewById(R.id.nextButton)
        nextButton.setOnClickListener {
            v.findNavController().navigate(R.id.plansFragment)
        }

        return v
    }


}
