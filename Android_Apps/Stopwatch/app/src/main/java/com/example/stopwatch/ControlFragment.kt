package com.example.stopwatch


import android.content.res.Configuration
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProviders
import androidx.navigation.findNavController
import androidx.recyclerview.widget.RecyclerView

/**
 * A simple [Fragment] subclass.
 *
 */
class ControlFragment : Fragment() {

    private var time = "00:00"

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        var v = inflater.inflate(R.layout.fragment_control, container, false)

        val model = activity?.let { ViewModelProviders.of(it).get(MyViewModel::class.java) }

        (v.findViewById(R.id.start) as Button).setOnClickListener {
            model?.start()
        }

        model?.getElapsedTime()?.observe(this, Observer<Long>{ time ->
            var minutes = time / 60
            var minutes0 = ""
            if (minutes < 10) {
                minutes0 = "0"
            }

            var seconds = time % 60
            var seconds0 = ""
            if (seconds < 10) {
                seconds0 = "0"
            }
            this.time = "$minutes0$minutes:$seconds0$seconds"
            v?.findViewById<TextView>(R.id.clock)?.text = this.time
        })

        (v.findViewById(R.id.stop) as Button).setOnClickListener {
            model?.stop()
        }

        (v.findViewById(R.id.reset) as Button).setOnClickListener {
            model?.reset()
        }

        (v.findViewById(R.id.next) as Button).setOnClickListener {

            if (v.getResources().getConfiguration().orientation != Configuration.ORIENTATION_LANDSCAPE) {
                v.findNavController().navigate(R.id.action_controlFragment_to_listFragment)
            }
        }

        (v.findViewById(R.id.lap) as Button).setOnClickListener {
            model?.addLap()
        }

        return v
    }
}
