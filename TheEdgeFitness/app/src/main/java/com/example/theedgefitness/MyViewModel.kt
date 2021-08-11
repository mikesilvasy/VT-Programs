package com.example.theedgefitness

import android.util.Log
import androidx.lifecycle.ViewModel
import com.google.firebase.database.*

class MyViewModel: ViewModel() {
    private val mDatabase: FirebaseDatabase = FirebaseDatabase.getInstance()
    private val mRefValidUsers: DatabaseReference = mDatabase.getReference("ValidUsers")
    var validUsers: ArrayList<String> = ArrayList<String>()

    private val mRefUsers: DatabaseReference = mDatabase.getReference("Users")
    var users: ArrayList<UserInfo> = ArrayList<UserInfo>()
    var attributes: ArrayList<String> = ArrayList<String>()

    private val mRefQuotes: DatabaseReference = mDatabase.getReference("Quotes")
    var quotes: ArrayList<String> = ArrayList<String>()

    private val mRefQuoteIndex: DatabaseReference = mDatabase.getReference("QuotesIndex")
    var qIndex: Int = readQuoteIndex()

    private val mRefUserIndex: DatabaseReference = mDatabase.getReference("UserIndex")
    var uIndex: Int = readUserIndex()

    fun readValidUsers() {
        mRefValidUsers.addValueEventListener(object : ValueEventListener {
            override fun onDataChange(dataSnapshot: DataSnapshot) {
                if (!isMakingNewProfile) {
                    validUsers.clear()
                    var keys: ArrayList<String> = ArrayList<String>()
                    for (keyNode in dataSnapshot.children) {
                        keys.add(keyNode.key!!)
                        var validUser: String = keyNode.getValue(String::class.java)!!
                        validUsers.add(validUser)
                    }
                }
            }

            override fun onCancelled(error: DatabaseError) {

            }
        })
    }

    fun isValidUser(user: String): Boolean {
        return validUsers.contains(user)
    }

    fun saveInfo(email: String, password: String, firstName: String, lastName: String, age: String, gender: String, index: Int) {
        mRefUsers.child("$index").child("email").setValue(email)
        mRefUsers.child("$index").child("password").setValue(password)
        mRefUsers.child("$index").child("firstName").setValue(firstName)
        mRefUsers.child("$index").child("lastName").setValue(lastName)
        mRefUsers.child("$index").child("age").setValue(age)
        mRefUsers.child("$index").child("gender").setValue(gender)
        users.add(UserInfo(email, password, firstName, lastName, age, gender))
    }

    fun readUsers() {
        mRefUsers.addValueEventListener(object : ValueEventListener {
            override fun onDataChange(dataSnapshot: DataSnapshot) {
                if (!isMakingNewProfile) {
                    var i: Int = 0
                    users.clear()
                    attributes.clear()
                    var keys: ArrayList<String> = ArrayList<String>()
                    for (keyNode in dataSnapshot.children) {
                        keys.add(keyNode.key!!)
                        var keysPerUser: ArrayList<String> = ArrayList<String>()
                        for (value in keyNode.children) {
                            keysPerUser.add(value.key!!)
                            var attr: String = value.getValue()!!.toString()
                            attributes.add(attr)
                        }
                        users.add(UserInfo(attributes[i + 1], attributes[i + 5], attributes[i + 2],
                            attributes[i + 4], attributes[i], attributes[i + 3]))
                        i += 6
                    }
                }
            }

            override fun onCancelled(error: DatabaseError) {

            }
        })
    }

    fun hasMadeAccount(email: String): Boolean {
        var userEmails: ArrayList<String> = ArrayList<String>()
        for (user in users) {
            userEmails.add(user.email)
        }
        return userEmails.contains(email)
    }

    fun doesPasswordMatch(email: String, password: String): Boolean {
        var userEmails: ArrayList<String> = ArrayList<String>()
        for (user in users) {
            userEmails.add(user.email)
        }
        var userPasswords: ArrayList<String> = ArrayList<String>()
        for (user in users) {
            userPasswords.add(user.password)
        }
        var i: Int = userEmails.indexOf(email)
        return password == userPasswords[i]
    }

    fun getCurrentUser(email: String): UserInfo {
        var userEmails: ArrayList<String> = ArrayList<String>()
        for (user in users) {
            userEmails.add(user.email)
        }
        var i: Int = userEmails.indexOf(email)
        return users[i]
    }

    fun readQuotes() {
        mRefQuotes.addValueEventListener(object : ValueEventListener {
            override fun onDataChange(dataSnapshot: DataSnapshot) {
                if (!isMakingNewProfile) {
                    quotes.clear()
                    var keys: ArrayList<String> = ArrayList<String>()
                    for (keyNode in dataSnapshot.children) {
                        keys.add(keyNode.key!!)
                        var quote: String = keyNode.getValue(String::class.java)!!
                        quotes.add(quote)
                    }
                }
            }

            override fun onCancelled(error: DatabaseError) {

            }
        })
    }

    fun pullQuote(index: Int): String {
        return quotes[index]
    }

    fun readQuoteIndex(): Int {
        mRefQuoteIndex.addValueEventListener(object : ValueEventListener {
            override fun onDataChange(dataSnapshot: DataSnapshot) {
                var keys: ArrayList<String> = ArrayList<String>()
                for (keyNode in dataSnapshot.children) {
                    keys.add(keyNode.key!!)
                    qIndex = keyNode.getValue(Int::class.java)!!
                }
            }

            override fun onCancelled(error: DatabaseError) {

            }
        })

        return qIndex
    }

    fun readUserIndex(): Int {
        mRefUserIndex.addValueEventListener(object : ValueEventListener {
            override fun onDataChange(dataSnapshot: DataSnapshot) {
                if (!isMakingNewProfile) {
                    var keys: ArrayList<String> = ArrayList<String>()
                    for (keyNode in dataSnapshot.children) {
                        keys.add(keyNode.key!!)
                        uIndex = keyNode.getValue(Int::class.java)!!
                    }
                }
            }

            override fun onCancelled(error: DatabaseError) {

            }
        })
        return uIndex
    }

    fun incrementUserIndex() {
        mRefUserIndex.child("i").setValue(readUserIndex() + 1)
    }
}