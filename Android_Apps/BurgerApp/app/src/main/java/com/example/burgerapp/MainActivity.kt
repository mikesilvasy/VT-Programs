package com.example.burgerapp

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.design.widget.TextInputEditText
import android.support.design.widget.TextInputLayout
import android.view.View
import android.widget.*

class MainActivity : AppCompatActivity() {

    val white: String = "white"
    val wheat: String = "wheat"
    val beef: String = "beef"
    val grilled_chicken: String = "grilled chicken"
    val turkey: String = "turkey"
    val salmon: String = "salmon"
    val veggie: String = "veggie"
    val choose_one: String = "choose one"
    val sauteed_mushrooms: String = "sauteed mushrooms"
    val lettuce: String = "lettuce"
    val tomato: String = "tomato"
    val pickles: String = "pickles"
    val mayo: String = "mayo"
    val mustard: String = "mustard"

    private var selected_bun: String? = null
    private var previous_bun: String? = null

    private var selected_patty: String? = null
    private var previous_patty: String? = null

    private var selected_first_topping: String? = null
    private var selected_second_topping: String? = null
    private var selected_third_topping: String? = null

    private var total_cost: Double = 0.0
    private var total_calories: Int = 0

    private var reachedMaxToppings: Boolean = false

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //Bun Spinner
        val bunSpinner: Spinner = findViewById(R.id.BunSpinner)
        ArrayAdapter.createFromResource(
            this,
            R.array.buns,
            android.R.layout.simple_spinner_item
        ).also { adapter ->
            adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
            bunSpinner.adapter = adapter
        }

        bunSpinner.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
            override fun onNothingSelected(parent: AdapterView<*>?) {

            }

            override fun onItemSelected(parent: AdapterView<*>?, view: View?, position: Int, id: Long) {
                selected_bun = parent?.getItemAtPosition(position).toString()
                updateBunPriceAndCalories()
            }
        }

        //Patty Spinner
        val pattySpinner: Spinner = findViewById(R.id.PattySpinner)
        ArrayAdapter.createFromResource(
            this,
            R.array.patties,
            android.R.layout.simple_spinner_item
        ).also { adapter ->
            adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
            pattySpinner.adapter = adapter
        }

        pattySpinner.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
            override fun onNothingSelected(parent: AdapterView<*>?) {

            }

            override fun onItemSelected(parent: AdapterView<*>?, view: View?, position: Int, id: Long) {
                selected_patty = parent?.getItemAtPosition(position).toString()
                updatePattyPriceAndCalories()
            }
        }

        val numBurgersString = findViewById<TextInputEditText>(R.id.numBurgers)
        val enter = findViewById<Button>(R.id.ENTER)
        if (numBurgersString != null && enter != null) {
            enter.setOnClickListener {
                val numBurgers: Int = numBurgersString.text.toString().toInt()
                total_cost = total_cost.times(numBurgers)
                total_calories = total_calories * numBurgers
                setTextViews()
            }
        }
    }

    fun radioButtonSelected(view: View) {
        if (selected_first_topping == null) {
            selected_first_topping = view.tag.toString()
        } else if (selected_second_topping == null) {
            selected_second_topping = view.tag.toString()
        } else if (selected_third_topping == null) {
            selected_third_topping = view.tag.toString()
        }
        updateToppingsPriceAndCalories()
    }

    private fun updateBunPriceAndCalories() {
        if (selected_bun != previous_bun) {
            if (previous_bun == white) {
                total_cost = total_cost - 1
                total_calories = total_calories - 140
            } else if (previous_bun == wheat) {
                total_cost = total_cost - 1
                total_calories = total_calories - 100
            }

            if (selected_bun == white) {
                total_cost = total_cost + 1
                total_calories = total_calories + 140
            } else if (selected_bun == wheat) {
                total_cost = total_cost + 1
                total_calories = total_calories + 100
            }
            previous_bun = selected_bun
        }
        setTextViews()
    }

    private fun updatePattyPriceAndCalories() {
        if (selected_patty != previous_patty) {
            if (previous_patty == beef) {
                total_cost = total_cost - 5.50
                total_calories = total_calories - 240
            } else if (previous_patty == grilled_chicken) {
                total_cost = total_cost - 5
                total_calories = total_calories - 180
            } else if (previous_patty == turkey) {
                total_cost = total_cost - 5
                total_calories = total_calories - 190
            } else if (previous_patty == salmon) {
                total_cost = total_cost - 7.50
                total_calories = total_calories - 95
            } else if (previous_patty == veggie) {
                total_cost = total_cost - 4.50
                total_calories = total_calories - 80
            }

            if (selected_patty == beef) {
                total_cost = total_cost + 5.50
                total_calories = total_calories + 240
            } else if (selected_patty == grilled_chicken) {
                total_cost = total_cost + 5
                total_calories = total_calories + 180
            } else if (selected_patty == turkey) {
                total_cost = total_cost + 5
                total_calories = total_calories + 190
            } else if (selected_patty == salmon) {
                total_cost = total_cost + 7.50
                total_calories = total_calories + 95
            } else if (selected_patty == veggie) {
                total_cost = total_cost + 4.50
                total_calories = total_calories + 80
            }
            previous_patty = selected_patty
        }
        setTextViews()
    }

    private fun updateToppingsPriceAndCalories() {
        if (reachedMaxToppings == false) {
            if (selected_first_topping != null && selected_second_topping == null && selected_third_topping == null) {
                if (selected_first_topping == sauteed_mushrooms) {
                    total_cost = total_cost + 1
                    total_calories = total_calories + 60
                } else if (selected_first_topping == lettuce) {
                    total_cost = total_cost + 0.30
                    total_calories = total_calories + 20
                } else if (selected_first_topping == tomato) {
                    total_cost = total_cost + 0.30
                    total_calories = total_calories + 20
                } else if (selected_first_topping == pickles) {
                    total_cost = total_cost + 0.50
                    total_calories = total_calories + 30
                } else if (selected_first_topping == mayo) {
                    total_calories = total_calories + 100
                } else if (selected_third_topping == mustard) {
                    total_calories = total_calories + 60
                }
            } else if (selected_second_topping != null && selected_third_topping == null) {
                if (selected_second_topping == sauteed_mushrooms) {
                    total_cost = total_cost + 1
                    total_calories = total_calories + 60
                } else if (selected_second_topping == lettuce) {
                    total_cost = total_cost + 0.30
                    total_calories = total_calories + 20
                } else if (selected_second_topping == tomato) {
                    total_cost = total_cost + 0.30
                    total_calories = total_calories + 20
                } else if (selected_second_topping == pickles) {
                    total_cost = total_cost + 0.50
                    total_calories = total_calories + 30
                } else if (selected_second_topping == mayo) {
                    total_calories = total_calories + 100
                } else if (selected_second_topping == mustard) {
                    total_calories = total_calories + 60
                }
            } else if (selected_third_topping != null) {
                if (selected_third_topping == sauteed_mushrooms) {
                    total_cost = total_cost + 1
                    total_calories = total_calories + 60
                } else if (selected_third_topping == lettuce) {
                    total_cost = total_cost + 0.30
                    total_calories = total_calories + 20
                } else if (selected_third_topping == tomato) {
                    total_cost = total_cost + 0.30
                    total_calories = total_calories + 20
                } else if (selected_third_topping == pickles) {
                    total_cost = total_cost + 0.50
                    total_calories = total_calories + 30
                } else if (selected_third_topping == mayo) {
                    total_calories = total_calories + 100
                } else if (selected_third_topping == mustard) {
                    total_calories = total_calories + 60
                }
                reachedMaxToppings = true
            }
            setTextViews()
        }
    }

        private fun setTextViews() {
            findViewById<TextView>(R.id.Cost).text = "%.2f".format(total_cost).toString()
            findViewById<TextView>(R.id.Calories).text = total_calories.toString()
        }
    }
