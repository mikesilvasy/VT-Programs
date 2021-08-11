/* 
 * CS:APP Data Lab 
 * 
 *   Please put your PID and name below.  If you worked with a partner,
 *   list their PID and name as well.
 * 
 *    PID          Name
 *    -----------------------------------------------------
 * 1: silvasym		Mike Silvasy
 * 2:
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
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
	int compareOddAndX;
	//Creates a 32-bit integer where all of the odd bits are equal to 1
	//and all of the even bits are equal to 0 (0xAAAAAAAA).
	int oddBits = 0xAA;
	oddBits = oddBits | (oddBits << 8);
	oddBits = oddBits | (oddBits << 16);
	//Compares the oddBits integer and the x integer using the or
	//operator.  The or operator stores a value where at least one bit
	//is equal to 1 at each index.  This will ultimately store a value
	//where all odd bits are 1 and if the bits at even indexes are equal
	//to 1 in x, those even indexes will be one in oddBits.
	compareOddAndX = (oddBits | x);
	
	//This first negates compareOddAndX by changing all bits equal to 1
	//to 0, and all bits equal to 0 to 1.  Therefore, if all even bits
	//are 1, the negation will be a 32-bit integer will all 0 bits.
	//Lastly, compareOddAndX is negated again.  If compareOddAndX is
	//now equal to 0, then compareOddAndX will be set to 1.  If
	//compareOddAndX is not equal to 0, then compareOddAndX will be set
	//to 0.
	return !(~compareOddAndX);
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
	int nextShift;
	//This arithmetically shifts each bit in x n times to the right.
	int originalShift = (x >> n);
	//Creates a 32-bit integer where all of the bits are equal to 1
	//(0xFFFFFFFF).
	int allOnes = 0xFF;
	allOnes = allOnes | (allOnes << 8);
	allOnes = allOnes | (allOnes << 16);
	//First, this arithmetically shifts each bit in allOnes (32 - n)
	//times to the left.
	//Next, this value is negated, so that there are (32 - n) bits equal
	//to 1 on the end (right side).
	nextShift = ~(allOnes << (32 + ~n) << 1);
	
	//Compares nextShift and originalShift integers using the and
	//operator.  The and operator stores a value where both bits are
	//equal to 1 at each index.  By using the and operator, the first n
	//bits (left side) will be set to 0 and since it is compared to the
	//previously arithmetically shifted value of x, the integer is now
	//logically shifted.
	return (nextShift & originalShift);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	//If x and y are of opposite signs (+x and -y, or -x and +y),
	//sameSign will equal 1.  If x and y are of the same sign, sameSign
	//will equal 0.  This line does this by comparing x and y using the
	//exclusive or (xOr) operator.  The xOr operator stores a value
	//where only one bit is equal to 1 at each index.  Lastly this value
	//is shifted 31 spots to the right and compared to one using the and
	//operator.  The and operator stores a value where both bits are
	//equal to 1 at the each index.  This value will either be 0 or 1.
	int diffSign = ((x ^ y) >> 31 & 1);
	//If x is negative, signX will be equal to 1, but if x is positive,
	//signX will be equal to 0.
	int signX = (x >> 31 & 1);
	//Determines if (y - x) is positive or negative.  If (y - x) is
	//positive or zero, yMinusX will be equal to 1, but if (y - x) is
	//negative, yMinusX will be equal to 0.
	int yMinusX = (~(y + (~x + 1)) >> 31 & 1);
	
	//This return statement checks two different scenarios.
	//1)If x and y are of different signs and x is negative, then x <= y
	//  and this line will return 1.
	//2)If x and y are of the same sign and (y - x) >= 0, this line will
	//  return 1.
	//If either of these two scenarios' criteria is not met, then this
	//line will return 0.
	return ((diffSign & signX) | (~diffSign & yMinusX));
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
	int bitCount;
	//Creates a 32-bit integer where all even bits are equal to 1
	//(0x55555555).
	//Creates a 32-bit integer where every even group of two bits are
	//equal to 1 (0x33333333).
	//Creates a 32-bit integer where every last four bits in each byte
	//are equal to 1 (0x0F0F0F0F).
	int num1 = 0x55;
	int num2 = 0x33;
	int num3 = 0x0F;
	num1 = num1 | (num1 << 8);
	num1 = num1 | (num1 << 16);
	num2 = num2 | (num2 << 8);
	num2 = num2 | (num2 << 16);
	num3 = num3 | (num3 << 8);
	num3 = num3 | (num3 << 16);
	//First, the bits in x are shifted one spot to the right.  Then, it
	//is compared to num1 using the and operator.  The and operator
	//stores a value where both bits are equal to 1 at each index.
	//Then, one is added to this value.  After, this value is negated.
	//Lastly, this value is added to x and the final value is stored in
	//x.
	x = (x + (~((x>>1) & num1) + 1));
	//First, x is compared to num2 using the and operator.  The and
	//operator stores a value where both bits are equal to 1 at each
	//index.
	//Then, on a separate note, the bits in x are shifted two spots to
	//the right and compared to num2.
	//Finally, the two previously calculated values are added together.
	x = ((x & num2) + ((x >> 2) & num2));
	//First, x is compared to num3 using the and operator.  The and
	//operator stores a value where both bits are equal to 1 at each
	//index.
	//Then, on a separate note the bits in x are shifted two spots to
	//the right and compared to num3.
	//Finally, the two previously calculated values are added together.
	x = ((x & num3) + ((x >> 4) & num3));
	//Sets x equal to x plus x shifted eight bits to the right.
	x = x + (x >> 8);
	//Sets x equal to x plus x shifted 16 bits to the right.
	x = x + (x >> 16);
	//Finally, the value of x is compared to 0x3F
	//(0000 0000 0000 0000 0000 0000 0011 1111) using the and operator.
	//The and operator stores a value where both bits are equal to 1 at
	//each index.
	bitCount = (x & 0x3F);
	
	//Returns the number of bits equal to 1 in x.
	return bitCount;
}
