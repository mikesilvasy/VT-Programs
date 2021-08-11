/* 
 * CS:APP Data Lab 
 * 
 * <Mike Silvasy (silvasym)>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  //Uses De Morgan's Law.  By the negation of (not x or not y), ~x
  //negates to x, or negates to and, and ~y negates to y.  Therefore,
  //the negation of (not x or not y) is logically equivalent to x and y.
  int xAndY = ~(~x | ~y);
  
  //Returns the value of x and y.
  return xAndY;
}
/* 
 * upperBits - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int upperBits(int n) {
	//This line sets a variable x equal to zero or one.  x will be set
	//to zero if n is equal to zero and x will be set to one if n is not
	//equal to zero.
	int x = ((!!n) & 1);
	
	//This line shifts the bits in x (32 - n) times to the left.
	x = x << (32 + (~n + 1));
	
	//This line negates the value of x.  The reason one is added is
	//because in binary, the negation of a number requires one to be
	//added.
	x = (~x + 1);
	
	//Returns the value of x.
	return x;
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
    //This line stores an int made of all ones in binary (equivalent to
    //(0xFF).
    int byteOfOnes = 255;
    
    //This line shifts the bits of n to the left by three and stores the
    //value.
    int nLeftByThree = (n << 3);
    
    //This line shifts the bits of m to the left by three and stores the
    //value.
    int mLeftByThree = (m << 3);
    
    //This line shifts the bits of the byte of ones (n << 3) times to
    //the left and compares this value to x using the and operator.
    //This stores a value where both bits equal one at the same index.
    int nthByte = x & (byteOfOnes << nLeftByThree);
	
    //This line shifts the bits of the byte of ones (m << 3) times to
    //the left and compares this value to x using the and operator.
    //This stores a value where both bits equal one at the same index.
    int mthByte = x & (byteOfOnes << mLeftByThree);
    
	//This line shifts the byte of ones (n << 3) times and (m << 3)
	//times to the left separately.  Afterwards, these two values are
	//compared using the or operator.  This stores a value where at
	//least one of the bits equal one at the same index.  Finally, this
	//line negates the comparison and compares it to x using the and
	//operator.  This stores a value where both bits equal one at the
	//same index.
	int nthOrMthByte = x & (~((byteOfOnes << nLeftByThree) | (byteOfOnes << (m << 3))));
	
	//The line shifts the nthByte back to the right by (n << 3) times
	//and compares this value to the byte of ones using the and
	//operator.  This stores a value where both bits equal one at the
	//same index.
	nthByte = byteOfOnes & (nthByte >> nLeftByThree);
    
    //This line shifts the nthByte one more time back to the left by
    //(m << 3) times.
    nthByte = (nthByte << mLeftByThree);
    
    //The line shifts the mthByte back to the right by (m << 3) times
	//and compares this value to the byte of ones using the and
	//operator.  This stores a value where both bits equal one at the
	//same index.
    mthByte = byteOfOnes & (mthByte >> mLeftByThree);
    
    //This line shifts the mthByte one more time back to the left by
    //(n << 3) times.
    mthByte = (mthByte << nLeftByThree);
    
    //This line finally compares the three calculations of nthOrMthByte,
    //nthByte and mythByte using the or operator.  This stores a value
    //where at least one bit is equal to one at each index.
    return (nthOrMthByte | nthByte | mthByte);
}
/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
	//This line compares the negation of x and y using the or operator.
	//This stores a value where at least one bit is equal to one at each
	//index.
	int xBelYGreatOrEqual = ~x | y;
	
	//This line compares x and y using the exclusive or operator.  This
	//stores a value where only one bit is equal to one at each index.
	int xYSameSign = x ^ y;
	
	//This line takes the negation of (x - y).
	int diffXY = ~(x + (~y + 1));
	
	//This line checks to see if x < y.  If x is less than y, lessThan
	//is set to 1, but if x is greater than or equal to y, lessThan is
	//set to 0.
	//This is done by checking to see if x is less than zero and y is
	//greater than equal to zero, or if x and y have the same sign
	//(+, -) and y - x is greater than or equal to zero.  After
	//computing this value, the value shifts 31 bits to the right.
	//Lastly, this value is compared to one using the and operator.
	//This stores a value where the bits are both equal to one at the
	//same index.  If the value before the comparison is equal to zero,
	//lessThan will be set to zero, but if the value before the
	//comparison is not zero, lessThan will be set to one.
	int lessThan = (~(xBelYGreatOrEqual & (xYSameSign | diffXY)) >> 31) & 1;
	
	//Returns one if x < y and zero otherwise.
	return lessThan;
}
