# Bisection method and Newton's method

This is a C program that implements the Bisection method and the Newton method to
find the roots of mathematical functions. The mathematical functions are hard coded
in this program.

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
![Newton img](https://raw.githubusercontent.com/Lehmannhen/Bisection-and-Newton-method/master/images/bisection.jpg)
