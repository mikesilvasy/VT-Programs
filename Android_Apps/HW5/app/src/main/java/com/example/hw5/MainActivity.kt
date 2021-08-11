package com.example.hw5

import android.Manifest
import android.annotation.SuppressLint
import android.content.Context
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.google.android.material.floatingactionbutton.FloatingActionButton
import androidx.core.app.ActivityCompat
import android.content.pm.PackageManager
import android.location.*
import android.os.Build
import android.provider.Settings
import android.util.Log
import com.google.android.gms.maps.CameraUpdateFactory
import com.google.android.gms.maps.GoogleMap
import com.google.android.gms.maps.OnMapReadyCallback
import com.google.android.gms.maps.model.LatLng
import com.google.android.gms.maps.model.MarkerOptions
import com.google.firebase.database.DatabaseReference
import com.google.firebase.database.FirebaseDatabase
import java.io.IOException
import java.text.SimpleDateFormat
import java.util.*

class MainActivity : AppCompatActivity() {

    private lateinit var recyclerView: RecyclerView
    private lateinit var viewAdapter: RecyclerView.Adapter<*>
    private val mapItems = ArrayList<MapItem>()

    private lateinit var database: DatabaseReference
    private var numLocations: Int = 1

    lateinit var locationManager: LocationManager
    private var hasGps = false
    private var hasNetwork = false
    private var locationGps: Location?=null
    private var locationNetwork: Location?=null

    lateinit var addLocation: FloatingActionButton

    private var permissions = arrayOf(Manifest.permission.ACCESS_FINE_LOCATION, Manifest.permission.ACCESS_COARSE_LOCATION)
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        addLocation = findViewById(R.id.fab)

        disableView()
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (checkPermission(permissions)) {
                enableView()
            }
            else {
                ActivityCompat.requestPermissions(this, permissions, 0)
            }
        }
        else {
            enableView()
        }
    }

    private fun disableView() {
        addLocation.isEnabled = false
        addLocation.alpha = 0.5F
    }

    private fun enableView() {
        addLocation.isEnabled = true
        addLocation.alpha - 1F
        addLocation.setOnClickListener {
            database = FirebaseDatabase.getInstance().reference

            getLocation()

            recyclerView = findViewById(R.id.entries)
            recyclerView.layoutManager = LinearLayoutManager(this, RecyclerView.VERTICAL, false)
            viewAdapter = RecyclerViewAdapter(mapItems, this)
            recyclerView.adapter = viewAdapter
        }
    }

    private fun newMapItemToDatabase(latLong: String, address: String, timestamp: String) {
        var newItem = MapItem(latLong, address, timestamp)
        database.child("Location $numLocations:").setValue(newItem)
        numLocations += 1
    }

    private fun checkPermission(permissionArray: Array<String>) : Boolean {
        var allSuccess = true
        for (i in permissionArray.indices) {
            if (checkCallingOrSelfPermission(permissionArray[i]) == PackageManager.PERMISSION_DENIED) {
                allSuccess = false
            }
        }
        return allSuccess
    }

    @SuppressLint("MissingPermission")
    private fun getLocation() {
        locationManager = getSystemService(Context.LOCATION_SERVICE) as LocationManager
        hasGps = locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER)
        hasNetwork = locationManager.isProviderEnabled(LocationManager.NETWORK_PROVIDER)
        if (hasGps || hasNetwork) {
            var date: Date = Calendar.getInstance().time
            var dateFormat: SimpleDateFormat = SimpleDateFormat("MM/dd/yyyy | hh:mm:ss")
            var formattedDate: String = dateFormat.format(date)
            if (hasGps) {
                locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 5000, 0F, object : LocationListener {
                    override fun onLocationChanged(location: Location?) {
                        if (location != null) {
                            locationGps = location
                        }
                    }

                    override fun onStatusChanged(provider: String?, status: Int, extras: Bundle?) {
                    }

                    override fun onProviderEnabled(provider: String?) {
                    }

                    override fun onProviderDisabled(provider: String?) {
                    }

                })
                val localGpsLocation = locationManager.getLastKnownLocation(LocationManager.GPS_PROVIDER)
                if (localGpsLocation != null) {
                    locationGps = localGpsLocation
                }
            }
            if (hasNetwork) {
                locationManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, 5000, 0F, object : LocationListener {
                    override fun onLocationChanged(location: Location?) {
                        if (location != null) {
                            locationNetwork = location
                        }
                    }

                    override fun onStatusChanged(provider: String?, status: Int, extras: Bundle?) {
                    }

                    override fun onProviderEnabled(provider: String?) {
                    }

                    override fun onProviderDisabled(provider: String?) {
                    }

                })
                val localNetworkLocation = locationManager.getLastKnownLocation(LocationManager.NETWORK_PROVIDER)
                if (localNetworkLocation != null) {
                    locationGps = localNetworkLocation
                }
            }
            var networkLat: Double? = locationNetwork?.latitude
            var networkLong: Double? = locationNetwork?.longitude
            var gpsLat: Double? = locationGps?.latitude
            var gpsLong: Double? = locationGps?.longitude
            if (locationGps != null && locationNetwork != null) {
                if (locationGps!!.accuracy > locationNetwork!!.accuracy) {
                    var fullAddress: String = ""
                    try {
                        var geocoder: Geocoder = Geocoder(this, Locale.getDefault())
                        var addresses: List<Address> = geocoder.getFromLocation(networkLat!!, networkLong!!, 1)

                        fullAddress = addresses.get(0).getAddressLine(0)
                    }
                    catch (e: IOException) {
                        e.printStackTrace()
                    }
                    var latLong: String = "<$networkLat, $networkLong>"
                    mapItems.add(MapItem(latLong, fullAddress, formattedDate))
                    newMapItemToDatabase(latLong, fullAddress, formattedDate)
                }
                else {
                    var fullAddress: String = ""
                    try {
                        var geocoder: Geocoder = Geocoder(this, Locale.getDefault())
                        var addresses: List<Address> = geocoder.getFromLocation(gpsLat!!, gpsLong!!, 1)

                        fullAddress = addresses.get(0).getAddressLine(0)
                    }
                    catch (e: IOException) {
                        e.printStackTrace()
                    }
                    var latLong: String = "<$gpsLat, $gpsLong>"
                    mapItems.add(MapItem(latLong, fullAddress, formattedDate))
                    newMapItemToDatabase(latLong, fullAddress, formattedDate)
                }
            }
            else if (locationGps != null) {
                var fullAddress: String = ""
                try {
                    var geocoder: Geocoder = Geocoder(this, Locale.getDefault())
                    var addresses: List<Address> = geocoder.getFromLocation(gpsLat!!, gpsLong!!, 1)

                    fullAddress = addresses.get(0).getAddressLine(0)
                }
                catch (e: IOException) {
                    e.printStackTrace()
                }
                var latLong: String = "<$gpsLat, $gpsLong>"
                mapItems.add(MapItem(latLong, fullAddress, formattedDate))
                newMapItemToDatabase(latLong, fullAddress, formattedDate)
            }
            else {
                var fullAddress: String = ""
                try {
                    var geocoder: Geocoder = Geocoder(this, Locale.getDefault())
                    var addresses: List<Address> = geocoder.getFromLocation(networkLat!!, networkLong!!, 1)

                    fullAddress = addresses.get(0).getAddressLine(0)
                }
                catch (e: IOException) {
                    e.printStackTrace()
                }
                var latLong: String = "<$networkLat, $networkLong>"
                mapItems.add(MapItem(latLong, fullAddress, formattedDate))
                newMapItemToDatabase(latLong, fullAddress, formattedDate)
            }
        }
        else {
            startActivity(Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS))
        }
    }

    class RecyclerViewAdapter(private val myDataset: ArrayList<MapItem>, private val activity: MainActivity) :
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
            fun bindItems(mapItem: MapItem) {
                val latLong: TextView = itemView.findViewById(R.id.latLong)
                val address: TextView = itemView.findViewById(R.id.address)
                val timestamp: TextView = itemView.findViewById(R.id.timestamp)

                latLong.text = mapItem.latLong
                address.text = mapItem.address
                timestamp.text = mapItem.timestammp

                itemView.setOnClickListener {
                }
            }
        }
    }
}
