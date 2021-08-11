package com.example.t04


import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.*
import androidx.core.os.bundleOf
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProviders
import androidx.navigation.findNavController
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.bumptech.glide.Glide
import com.bumptech.glide.request.RequestOptions
import kotlinx.android.synthetic.main.activity_main.*
import java.util.*


// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val ARG_PARAM1 = "param1"
private const val ARG_PARAM2 = "param2"

/**
 * A simple [Fragment] subclass.
 *
 */
class ListFragment : Fragment() {

    private var selected_sort: String? = null

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        var v = inflater.inflate(R.layout.fragment_list, container, false)

        val recyclerView = v.findViewById<RecyclerView>(R.id.movie_list)
        val adapter = MovieListAdapter()
        recyclerView.adapter = adapter
        recyclerView.layoutManager = LinearLayoutManager(context, RecyclerView.VERTICAL, false)

        val model = ViewModelProviders.of(this).get(MovieViewModel::class.java)

        val sortBySpinner: Spinner = v.findViewById(R.id.sortSpinner)
        ArrayAdapter.createFromResource(context,
            R.array.sort_by_entries,
            android.R.layout.simple_spinner_item
        ).also { adapter ->
            adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
            sortBySpinner.adapter = adapter
        }

        sortBySpinner.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
            override fun onNothingSelected(parent: AdapterView<*>?) {

            }

            override fun onItemSelected(parent: AdapterView<*>?, view: View?, position: Int, id: Long) {
                selected_sort = parent?.getItemAtPosition(position).toString()
                if (selected_sort == "Sort By: Title") {
                    model.sortByTitle()
                    model.allMovies.observe(
                        viewLifecycleOwner,
                        Observer<List<MovieItem>> { movies ->
                            movies?.let {
                                adapter.setMovies(it)
                            }
                        }
                    )
                }
                else if (selected_sort == "Sort By: Vote") {
                    model.sortByVote()
                    model.allMovies.observe(
                        viewLifecycleOwner,
                        Observer<List<MovieItem>> { movies ->
                            movies?.let {
                                adapter.setMovies(it)
                            }
                        }
                    )
                }
            }
        }

        (v.findViewById<Button>(R.id.refresh)).setOnClickListener{
            model.refreshMovies(1)
        }

        return v
    }

    inner class MovieListAdapter():
        RecyclerView.Adapter<MovieListAdapter.MovieViewHolder>(){
        private var movies = emptyList<MovieItem>()

        internal fun setMovies(movies: List<MovieItem>) {
            this.movies = movies
            notifyDataSetChanged()
        }

        override fun getItemCount(): Int {
            return movies.size
        }

        override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): MovieViewHolder {
            val v = LayoutInflater.from(parent.context)
                .inflate(R.layout.card_view, parent, false)
            return MovieViewHolder(v)
        }

        override fun onBindViewHolder(holder: MovieViewHolder, position: Int) {
//            holder.bindItems(movieList[position])
            Glide.with(this@ListFragment).load(resources.getString(R.string.picture_base_url)+movies[position].poster_path).apply( RequestOptions().override(128, 128)).into(holder.view.findViewById(R.id.moviePoster))
            holder.view.findViewById<TextView>(R.id.title).text=movies[position].title
            holder.view.findViewById<TextView>(R.id.rating).text=movies[position].vote_average.toString()
            holder.itemView.setOnClickListener(){
                holder.view.findNavController().navigate(R.id.action_listFragment_to_detailFragment, bundleOf ("moviePoster" to movies[position].poster_path, "movieTitle" to movies[position].title, "movieRelease" to movies[position].release_date, "movieOverview" to movies[position].overview))
            }
        }

        inner class MovieViewHolder(val view: View): RecyclerView.ViewHolder(view), View.OnClickListener {
            override fun onClick(view: View?) {
            }
        }
    }
}
