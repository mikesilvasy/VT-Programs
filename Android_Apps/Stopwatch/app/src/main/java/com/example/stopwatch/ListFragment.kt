package com.example.stopwatch


import android.content.res.Configuration
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import androidx.lifecycle.ViewModelProviders
import androidx.navigation.findNavController
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView

/**
 * A simple [Fragment] subclass.
 *
 */
class ListFragment : Fragment() {

    private lateinit var recyclerView: RecyclerView
    private lateinit var viewAdapter: RecyclerView.Adapter<*>
    private var totalLaps = ArrayList<String>()

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment

        var v = inflater.inflate(R.layout.fragment_list, container, false)
        val model = activity?.let { ViewModelProviders.of(it).get(MyViewModel::class.java) }

        (v.findViewById(R.id.back) as Button).setOnClickListener {
            if (v.getResources().getConfiguration().orientation != Configuration.ORIENTATION_LANDSCAPE) {
                v.findNavController().navigate(R.id.action_listFragment_to_controlFragment)
            }
        }

        totalLaps.clear()
        totalLaps = model?.totalLaps()!!

        recyclerView = v.findViewById(R.id.recyclerView)

        recyclerView.layoutManager = LinearLayoutManager(context, RecyclerView.VERTICAL, false)

        viewAdapter = RecyclerViewAdapter(totalLaps, activity as MainActivity)

        recyclerView.adapter = viewAdapter

        return v
    }
}

class RecyclerViewAdapter(private val myDataset: ArrayList<String>, private val activity: MainActivity) :
    RecyclerView.Adapter<RecyclerViewAdapter.ViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup,
                                    viewType: Int): RecyclerViewAdapter.ViewHolder {

        val v = LayoutInflater.from(parent.context)
            .inflate(R.layout.recyclerviewitem, parent, false)

        return ViewHolder(v, activity)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        holder.bindItems(myDataset[position])
    }

    class ViewHolder(private val view: View, private val activity: MainActivity) : RecyclerView.ViewHolder(view){
        fun bindItems(lap: String) {
            val currLap: TextView = itemView.findViewById(R.id.lapString)

            currLap.text = lap
        }
    }

    // Return the size of your dataset (invoked by the layout manager)
    override fun getItemCount() = myDataset.size



}
