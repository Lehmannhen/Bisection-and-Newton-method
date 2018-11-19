# Bisection method and Newton's method

This is a C program that implements the Bisection method and the Newton method to
find approximations to the roots of mathematical functions.
The mathematical functions are hard coded in this program.

## ----------------- Newton's method ----------------------
Newton's method is an algorithm to find the approximate solution to *f(x) = 0*

The method begins with an initial guess *x<sub>0</sub>*. Now the algorithm checks where
the tangent line to the function *f(x)* at the point (*x<sub>0</sub>*, *f(*x<sub>0</sub>*)*) crosses
the x-axis in order to see if this is a better approximation to the actual solution of *f(x) = 0*.

We can call this new point *x<sub>1</sub>*, if at this point the approximation isn't good enough
the method proceeds by checking the tangent line at (*x<sub>1</sub>*, *f(*x<sub>1</sub>*)*).
This process is repeated until the approximation is within some tolerance.
In general, to get *x<sub>n+1</sub>* the algorithm checks the tangent line at (*x<sub>n</sub>*, *f(*x<sub>n</sub>*)*).

![Newton img](https://raw.githubusercontent.com/Lehmannhen/Bisection-and-Newton-method/master/images/Newton.jpg)




## ----------------- Bisection method ---------------------
The bisection method is another algorithm to find the approximate solution to *f(x) = 0*.

This method begins with two initial guesses, *a* and *b*, where *a* is less than the solution
and *b* is greater than the solution. This can be done by choosing *f(a) < 0* and *f(b) > 0*.
If we consider continuous functions there should be a *c* such that *a < c < b* and *f(c) = 0*.

![Newton img](https://raw.githubusercontent.com/Lehmannhen/Bisection-and-Newton-method/master/images/bisection.jpg)

Once the algorithm knows *a* and *b* it proceeds as follows:
* find the midpoint *m = (a + b) / 2*
* if *f(m) = 0*, the solution is found!
* if *f(m) < 0*, set *a = m*
* if *f(m) > 0*, set *b = m*
This procedure is now repeated until either the solution is found or the approximation is within
some tolerance. Since the solution *c* should lie in the interval *[a, b]* and the length of the
interval gets smaller and smaller with each iteration, we can stop when *b - a <= e* where *e*
is the tolerance.
## ------------------------------------------------------------

## ----------------- How to use the program --------------
* compile:  gcc -g -Wall -o bisect_newton bisect_newton.c -lm
* run:         ./bisect_newton

Note: in the compile command -lm is used to link the math library.


## ----------------- References -----------------------------
Paul Smith, (2018), Bisection [ONLINE].
Available at: https://astarmathsandphysics.com/university-maths-notes/numerical-methods/2009-the-bisection-method.html
[Accessed 19 November 2018].

Quora, (2018), Newton's [ONLINE]. Available at: https://www.quora.com/In-which-cases-is-Newtons-method-not-applicable
[Accessed 19 November 2018].
