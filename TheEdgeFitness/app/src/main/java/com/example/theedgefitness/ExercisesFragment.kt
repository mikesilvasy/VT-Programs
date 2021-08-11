package com.example.theedgefitness


import android.graphics.Color
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.navigation.findNavController
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import kotlinx.android.synthetic.main.card_view.*


// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val ARG_PARAM1 = "param1"
private const val ARG_PARAM2 = "param2"
lateinit var clickedExercise: ExerciseItem
var specialCase: String?=null

/**
 * A simple [Fragment] subclass.
 *
 */
class ExercisesFragment : Fragment() {

    private lateinit var recyclerView: RecyclerView
    private lateinit var viewAdapter: RecyclerView.Adapter<*>
    private val exerciseItems = ArrayList<ExerciseItem>()

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val v = inflater.inflate(R.layout.fragment_exercises, container, false)

        specialCase = null
        currIsProfile = false
        currIsDiet = false
        currIsPlans = false
        currIsQuotes = false

        v.findViewById<TextView>(R.id.exercises).text = clickedPlan

        if (clickedPlan == "BULK") {
            initArrayBulk(exerciseItems)
        }
        else if (clickedPlan == "CARDIO") {
            initArrayCardio(exerciseItems)
        }
        else if (clickedPlan == "ABS/CORE") {
            initArrayAbsCore(exerciseItems)
        }
        else if (clickedPlan == "MUSCLE ENDURANCE") {
            initArrayMuscleEndurance(exerciseItems)
        }
        else if (clickedPlan == "LEGS") {
            initArrayLegs(exerciseItems)
        }

        recyclerView = v.findViewById(R.id.exerciseView)

        recyclerView.layoutManager = LinearLayoutManager(context, RecyclerView.VERTICAL, false) as RecyclerView.LayoutManager?

        viewAdapter = ExercisesFragment.RecyclerViewAdapter(exerciseItems, activity as MainActivity)

        recyclerView.adapter = viewAdapter

        return v
    }

    private fun initArrayBulk(myDataset: MutableList<ExerciseItem>){
        myDataset.clear()

        var setsAndReps = listOf(5, 5, 5, 5);
        myDataset.add(ExerciseItem("Bench Press", Color.WHITE,setsAndReps))
        myDataset.add(ExerciseItem("Incline Bench Press", Color.parseColor("#fdaa56"),setsAndReps))
        myDataset.add(ExerciseItem("Dumbell Bench Press", Color.WHITE,setsAndReps))
        myDataset.add(ExerciseItem("Incline Dumbell Bench Press", Color.parseColor("#fdaa56"),setsAndReps))
        setsAndReps = listOf(5, 5, 5, 5, 5)
        myDataset.add(ExerciseItem("Bicep Curls", Color.WHITE,setsAndReps))
        setsAndReps = listOf(5, 5, 5, 5)
        myDataset.add(ExerciseItem("Dumbell Overhead Press", Color.parseColor("#fdaa56"),setsAndReps))
        myDataset.add(ExerciseItem("Tricep Extension", Color.WHITE,setsAndReps))
        setsAndReps = listOf(7, 7, 7, 7, 7)
        myDataset.add(ExerciseItem("Seated Machine Dips", Color.parseColor("#fdaa56"),setsAndReps))

    }

    private fun initArrayCardio(myDataset: MutableList<ExerciseItem>){
        myDataset.clear()

        var setsAndReps = listOf(10)
        myDataset.add(ExerciseItem("Stair Master", Color.WHITE, setsAndReps))
        myDataset.add(ExerciseItem("Treadmill", Color.parseColor("#fdaa56"), setsAndReps))
        myDataset.add(ExerciseItem("Bike", Color.WHITE, setsAndReps))
        myDataset.add(ExerciseItem("Spinner", Color.parseColor("#fdaa56"), setsAndReps))
        myDataset.add(ExerciseItem("Elliptical", Color.WHITE, setsAndReps))
        myDataset.add(ExerciseItem("Swimming", Color.parseColor("#fdaa56"), setsAndReps))
    }

    private fun initArrayAbsCore(myDataset: MutableList<ExerciseItem>){
        myDataset.clear()

        var setsAndReps = listOf(1, 1, 1)
        myDataset.add(ExerciseItem("Plank", Color.WHITE, setsAndReps))
        setsAndReps = listOf(20, 20, 20)
        myDataset.add(ExerciseItem("V Sit-Ups", Color.parseColor("#fdaa56"), setsAndReps))
        myDataset.add(ExerciseItem("Russian Twists", Color.WHITE, setsAndReps))
        myDataset.add(ExerciseItem("SuperMan", Color.parseColor("#fdaa56"), setsAndReps))
        myDataset.add(ExerciseItem("Leg Raises", Color.WHITE, setsAndReps))
        myDataset.add(ExerciseItem("Dead Bug", Color.parseColor("#fdaa56"), setsAndReps))
        myDataset.add(ExerciseItem("Windshield Wiper", Color.WHITE, setsAndReps))
        myDataset.add(ExerciseItem("Bicycle Kicks", Color.parseColor("#fdaa56"), setsAndReps))
        setsAndReps = listOf(30, 30, 30)
        myDataset.add(ExerciseItem("6-Inch Leg Raises", Color.WHITE, setsAndReps))
        setsAndReps = listOf(20, 20, 20)
        myDataset.add(ExerciseItem("Stability Ball Crunch", Color.parseColor("#fdaa56"), setsAndReps))

    }

    private fun initArrayMuscleEndurance(myDataset: MutableList<ExerciseItem>){
        myDataset.clear()

        var setsAndReps = listOf(12, 10, 8)
        myDataset.add(ExerciseItem("Bench Press", Color.WHITE, setsAndReps))
        myDataset.add(ExerciseItem("Incline Bench Press", Color.parseColor("#fdaa56"), setsAndReps))
        myDataset.add(ExerciseItem("Dumbell Bench Press", Color.WHITE, setsAndReps))
        myDataset.add(ExerciseItem("Incline Dumbell Bench Press", Color.parseColor("#fdaa56"), setsAndReps))
        myDataset.add(ExerciseItem("Bicep Curls", Color.WHITE, setsAndReps))
        setsAndReps = listOf(12, 12, 12)
        myDataset.add(ExerciseItem("Dumbell Overhead Press", Color.parseColor("#fdaa56"), setsAndReps))
        myDataset.add(ExerciseItem("Tricep Extension", Color.WHITE, setsAndReps))
        setsAndReps = listOf(5, 5, 5, 5)
        myDataset.add(ExerciseItem("Pull-Ups", Color.parseColor("#fdaa56"), setsAndReps))
        myDataset.add(ExerciseItem("Dips", Color.WHITE, setsAndReps))
    }

    private fun initArrayLegs(myDataset: MutableList<ExerciseItem>){
        myDataset.clear()

        var setsAndReps = listOf(10, 10, 10)
        myDataset.add(ExerciseItem("Squats", Color.WHITE, setsAndReps))
        myDataset.add(ExerciseItem("Single Leg Bench Lunges", Color.parseColor("#fdaa56"), setsAndReps))
        myDataset.add(ExerciseItem("Front Squats", Color.WHITE, setsAndReps))
        setsAndReps = listOf(8, 8, 8)
        myDataset.add(ExerciseItem("Dead Lifts", Color.parseColor("#fdaa56"), setsAndReps))
        setsAndReps = listOf(12, 10, 8)
        myDataset.add(ExerciseItem("Leg Press", Color.WHITE, setsAndReps))
        setsAndReps = listOf(7, 7, 7)
        myDataset.add(ExerciseItem("Isolated Leg Press", Color.parseColor("#fdaa56"), setsAndReps))
    }

    class RecyclerViewAdapter(private val myDataset: ArrayList<ExerciseItem>, private val activity: MainActivity) :
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
            var color: Boolean = true
            fun bindItems(exerciseItem: ExerciseItem) {
                val title: TextView = itemView.findViewById(R.id.title)
                val setsAndReps: TextView = itemView.findViewById(R.id.setsAndReps)
                itemView.setBackgroundColor(exerciseItem.color)

                title.text = exerciseItem.Exercise

                var setsReps: List<Int> = exerciseItem.setsAndReps
                if (clickedPlan == "CARDIO") {
                    setsAndReps.text = setsReps.get(0).toString() + "Min"
                }
                else {
                    var sameEntries: Boolean = true
                    var i: Int = 0
                    while (i < setsReps.size) {
                        if (i > 0 && setsReps.get(i - 1) != setsReps.get(i)) {
                            sameEntries = false
                        }
                        i += 1
                    }
                    if (sameEntries) {
                        setsAndReps.text = setsReps.size.toString() + "x" + setsReps.get(0).toString()
                        if (exerciseItem.Exercise == "Plank") {
                            setsAndReps.text = setsReps.size.toString() + "x" + setsReps.get(0).toString() + "Min"
                        }
                        else if (exerciseItem.Exercise == "6-Inch Leg Raises") {
                            setsAndReps.text = setsReps.size.toString() + "x" + setsReps.get(0).toString() + "Sec"
                        }
                        else if (exerciseItem.Exercise == "Single Leg Bench Lunges" || exerciseItem.Exercise == "Isolated Leg Press") {
                            setsAndReps.text = setsReps.size.toString() + "x" + setsReps.get(0).toString() + "(per leg)"
                        }
                    }
                    else {
                        var x: Int = 0
                        var sR: String = ""
                        while (x < setsReps.size - 1) {
                            sR += setsReps.get(x)
                            sR += "-"
                            x += 1
                        }
                        sR += setsReps.get(setsReps.size - 1)
                        setsAndReps.text = sR
                    }
                }

                //itemView.setOnClickListener {
                //  view.findNavController().navigate(R.id.action_listFragment_to_detailFragment,
                //    bundleOf("dept" to newsItem.dept, "news" to newsItem.content)
                // )
                itemView.setOnClickListener {
                    clickedExercise = exerciseItem
                    if (exerciseItem.Exercise == "Plank" || clickedPlan == "CARDIO") {
                        specialCase = "Min"
                    }
                    else if (exerciseItem.Exercise == "6-Inch Leg Raises") {
                        specialCase = "Sec"
                    }
                    else if (exerciseItem.Exercise == "Single Leg Bench Lunges" || exerciseItem.Exercise == "Isolated Leg Press") {
                        specialCase = "(per leg)"
                    }
                    view.findNavController().navigate(R.id.detailFragment)
                }
            }
        }
    }

}
