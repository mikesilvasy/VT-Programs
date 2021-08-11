package com.example.t04


import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import androidx.lifecycle.ViewModelProviders
import com.bumptech.glide.Glide
import com.bumptech.glide.request.RequestOptions
import java.util.*


// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val ARG_PARAM1 = "param1"
private const val ARG_PARAM2 = "param2"

/**
 * A simple [Fragment] subclass.
 *
 */
class DetailFragment : Fragment() {

    var movieTitle:String? = null

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        var v = inflater.inflate(R.layout.fragment_detail, container, false)

        val model = ViewModelProviders.of(this).get(MovieViewModel::class.java)

        return v
    }

    override fun onViewCreated(view: View, bundle: Bundle?) {
        super.onViewCreated(view, bundle)

        //Movie Poster
        Glide.with(this@DetailFragment).load(resources.getString(R.string.picture_base_url)+(this.arguments?.getString("moviePoster"))).apply( RequestOptions().override(350, 350)).into(view.findViewById(R.id.moviePoster))

        //Movie Title
        (view.findViewById(R.id.movieTitle) as TextView).text = this.arguments?.getString("movieTitle")

        //Movie Release Date
        var dateConverter: DateConverter = DateConverter()
        var date: String = (this.arguments?.get("movieRelease") as Date).toString()
        (view.findViewById(R.id.movieRelease) as TextView).text = "Release Date:  " + date.substring(0, 11) + date.substring((date.length - 4), date.length)

        //Movie Overview
        (view.findViewById(R.id.movieOverview) as TextView).text = "Overview:  " + this.arguments?.getString("movieOverview")
    }
}
