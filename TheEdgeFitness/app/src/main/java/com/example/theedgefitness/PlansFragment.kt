package com.example.theedgefitness


import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView
import android.graphics.Color
import android.widget.TextView
import androidx.navigation.findNavController
import androidx.recyclerview.widget.LinearLayoutManager

lateinit var clickedPlan: String;


/**
 * A simple [Fragment] subclass.
 *
 */
class PlansFragment : Fragment() {

    private lateinit var recyclerView: RecyclerView
    private lateinit var viewAdapter: RecyclerView.Adapter<*>
    private val planItems = ArrayList<PlanItem>()

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        initArray(planItems)
        var view = inflater.inflate(R.layout.fragment_plans, container, false)

        currIsProfile = false
        currIsDiet = false
        currIsPlans = true
        loggedIn = true
        isMakingNewProfile = false
        currIsQuotes = false

        recyclerView = view.findViewById(R.id.plans)

        recyclerView.layoutManager = LinearLayoutManager(context, RecyclerView.VERTICAL, false) as RecyclerView.LayoutManager?

        viewAdapter = RecyclerViewAdapter(planItems, activity as MainActivity)

        recyclerView.adapter = viewAdapter

        return view
    }

    private fun initArray(myDataset: MutableList<PlanItem>){
        myDataset.clear()

        myDataset.add(PlanItem("BULK", Color.WHITE))
        myDataset.add(PlanItem("CARDIO", Color.parseColor("#fdaa56")))
        myDataset.add(PlanItem("ABS/CORE", Color.WHITE))
        myDataset.add(PlanItem("MUSCLE ENDURANCE", Color.parseColor("#fdaa56")))
        myDataset.add(PlanItem("LEGS", Color.WHITE))


    }


    class RecyclerViewAdapter(private val myDataset: ArrayList<PlanItem>, private val activity: MainActivity) :
        RecyclerView.Adapter<RecyclerViewAdapter.ViewHolder>() {
        override fun onCreateViewHolder(parent: ViewGroup,
                                        viewType: Int): RecyclerViewAdapter.ViewHolder {
            val v = LayoutInflater.from(parent.context)
                .inflate(R.layout.card_view, parent, false)
            return ViewHolder(v, activity)
        }
        override fun onBindViewHolder(holder: ViewHolder, position: Int) {
            holder.bindItems(myDataset[position])
        }

        // Return the size of your dataset (invoked by the layout manager)
        override fun getItemCount() = myDataset.size

        class ViewHolder(private val view: View, private val activity: MainActivity) : RecyclerView.ViewHolder(view){
            fun bindItems(planItem: PlanItem) {
                val title: TextView = itemView.findViewById(R.id.title)
                val setsAndReps: TextView = itemView.findViewById(R.id.setsAndReps)
                itemView.setBackgroundColor(planItem.color)

                title.text = planItem.Exercise
                setsAndReps.text = ""

                //itemView.setOnClickListener {
                  //  view.findNavController().navigate(R.id.action_listFragment_to_detailFragment,
                    //    bundleOf("dept" to newsItem.dept, "news" to newsItem.content)
                   // )
                itemView.setOnClickListener {
                    clickedPlan = planItem.Exercise
                    view.findNavController().navigate(R.id.exercisesFragment)
                }
            }
        }
    }
}
