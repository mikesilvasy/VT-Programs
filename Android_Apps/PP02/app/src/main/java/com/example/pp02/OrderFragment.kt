package com.example.pp02


import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView

/**
 * A simple [Fragment] subclass.
 *
 */
class OrderFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        var view = inflater.inflate(R.layout.fragment_order, container, false)

        val appleAmount: TextView = view.findViewById(R.id.appleAmount)
        val applePlusButton = view.findViewById<Button>(R.id.applePlus)
        val appleMinusButton = view.findViewById<Button>(R.id.appleMinus)

        return inflater.inflate(R.layout.fragment_confirmation, container, false)
    }


}
