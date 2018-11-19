/* File: bisect_newton.c
 * Purpose: use both Bisection and Newton method to approximate a function f(x)
 * 
 * Input: a leftpoint a, a right point b, the error tolerance, maximum iterations,
 * which function f(x) (1 to 10) to approximate solution for.
 *
 * Output: the approximated value of solution to f(x) calculated from both bisect
 * and Newton 
 * 
 * Note: Bisection method doesn't work on a discontinuous function. It will converge
 * to a false solution.
 *
 * Compile: gcc -g -Wall -o bisect_newton bisect_newton.c -lm
 * Run: ./bisect_newton
 * Henrik Lehmann
 * Student ID: 20495531
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double x, int which);
double f_prime(double x, int which);
void print_result(double approx, double error, int num_iters, int converged,
                  double func_approx);
double Bisection(double a, double b, double error_tol, int max_iters, int func_i);
double Newton(double x_0, double error_tol, int max_iters, int func_i);

int main(void) {
    double a;
    double b;
    double error_tol;
    int max_iters;
    int func_i;
    char user_input;
    
    do {
        printf("Type in interval [a, b], error_tol, max_iters, func_i as:\n");
        printf("a b error_tol max_iters func_i\n");
        scanf("%lf %lf %lf %d %d", &a, &b, &error_tol, &max_iters, &func_i);

        printf("\n******************* Bisection method **********************\n");
        Bisection(a, b, error_tol, max_iters, func_i);
       
        printf("\n******************* Newton's method ***********************\n");
        Newton(b, error_tol, max_iters,func_i);
       
        printf("\nWould you like to run again? (Enter any char, 'q' to stop): ");
        scanf(" %c", &user_input);
        
    } while (user_input != 'q');

    return 0;
}







/*****************************************************************************
 * Bisection
 * Description:
 * The Bisection() function tries to approximate a solution to a function f(x)
 * on a given interval [a, b]. 
 *
 * Parameters:
 * a: left endpoint
 * b: right endpoint
 * error_tol: max error tolerance of the approximated solution
 * max_iters: max number of iterations of the bisection method
 * func_i: the function number i, who's solution will be approximated 
 *
 * Return value:
 * m: the approximated solution. If error occurs the out of bound value a - b 
 * is returned.
 *****************************************************************************/
double Bisection(double a, double b, double error_tol, int max_iters, int func_i) {
    double m = 0.0;
    double error = 0.0;
    double func_approx = 0.0;
    int iters = 0;
    int converged = 1; /*if solution is found before iterations start */
    
    if (f(a, func_i) * f(b, func_i) > 0) {
        fprintf(stderr, "f(%.1lf) * f(%.1lf) > 0 Bisection method failed\n", a, b);
        return a - b; /* return a value that is not in the interval*/
    }
    else if (f(a, func_i) == 0) {
        print_result(a, error, iters, converged, func_approx);
        return a;
    }
    else if (f(b, func_i) == 0) {
        print_result(b, error, iters, converged, func_approx);
        return b;
    }

    while (iters < max_iters && (error = fabs(b - a)) > error_tol) {
        iters++;
        m = (a + b) / 2;
        if (f(m, func_i) == 0) {           
            error = 0.0;
            break; /* Found a solution */
        }
        else if (f(m, func_i) * f(a, func_i) < 0) {
            b = m;
        }
        else {
            a = m;
        }

    }

    /* user entered less than or zero max iterations */
    if (iters <= 0) {
        printf("No iterations in Bisection, max_iters = %d\n", max_iters);
        return a - b;
    }
    converged = error <= error_tol;
    func_approx = f(m, func_i);
    print_result(m, error, iters, converged, func_approx);

    return m;
}







/*****************************************************************************
 * Newton
 * Description:
 * The Newton() function tries to approximate a solution to a function f(x)
 * given an initial guess x_0
 *
 * Parameters:
 * x_0: initial guess
 * error_tol: max error tolerance of the approximated solution
 * max_iters: max number of iterations of the bisection method
 * func_i: the function number i, who's solution will be approximated
 *
 * Return value:
 * x_new: the approximated solution. If error occurs f'(x) = 0, then an error
 * message is printed and whatever value x_new held will be returned
 * 
 *****************************************************************************/
double Newton(double x_0, double error_tol, int max_iters, int func_i) {
    double x_new, x_old, error;
    double func_approx = 0.0;
    int num_iters = 0;
    int converged = 0;

    x_new = x_0;

    /* prevents start of loop in case user enters less than 1 iterations */
    if (max_iters <= 0) {
        printf("No iterations in Newton, max_iters = %d\n", max_iters);
        return x_new;
    }

    do {
        num_iters++;
        x_old = x_new;
        if (f_prime(x_old, func_i) == 0) {
            fprintf(stderr, "Division by zero! f'(%lf) == 0, Newton's method failed\n",
                    x_old);
            return x_new;
        }
        
        x_new = x_old - (f(x_old, func_i) / f_prime(x_old, func_i));
       
    } while ((error = fabs(x_new - x_old)) > error_tol && num_iters < max_iters);

    /* Did the function converge or did we run out of iterations? */
    converged = error <= error_tol;
    func_approx = f(x_new, func_i);
    
    print_result(x_new, error, num_iters, converged, func_approx);
    
    return x_new;
}






/*****************************************************************************
 * print_result
 * Description:
 * The print_result() function prints out information from the calculation
 * of the Bisect or the Newton method. Prints the approximation, error,
 * number of iterations, and if the method converged
 * given an initial guess x_0
 *
 * Parameters:
 * approx: the approximated solution
 * error: the error of the solution
 * num_iters: number of iterations it took for the function to find an approximated
 * solution
 * converged: if the function used found a good enough solution within the number of
 * iterations
 * func_approx: the function f(x) value from the approximation of x
 *
 * Return value: 
 * none. Prints the approximation, error, number of iterations, and
 * if function converged, and the function value of approximation.
 * Note: func_approx should be close to 0.
 *****************************************************************************/
void print_result(double approx, double error, int num_iters, int converged,
                  double func_approx) {
    
    printf("Approximation: %.22lf\nError: %.22lf\nIterations: %d\nConverged: %s\n",
           approx, error, num_iters, converged ? "Yes": "No");
    printf("Function approximation: %.22lf\n", func_approx);
}






/*------------------------------------------------------------
 * Function: f
 */
double f(double x, int which) {
   double y;

   switch (which) {
      case (1):
         // f1;  exact = sqrt(2) = 1.4142135623
         y = x*x - 2;
         break;

      case (2):
         // f2;  exact depends on x_0.  Should be 0, pi, 2pi, etc.
         y = sin(x);
         break;

      case (3):
         // f3;  exact = 1
         y = (x-1)*(x-1)*(x-1);
         break;
 
      case (4):
         // f4;  exact = 1
         // Note the C library pow function doesn't like
         //    negative arguments and fractional exponents
         y = pow(fabs(x-1), 1.0/3.0);
         if (x-1 < 0) y = -y;
         break;

      case (5):
         // f5;  exact = -0.6823278038
         y = x*x*x + x + 1.0;
         break;

      case (6):
         // f6;  exact = 56,771.0543
         y = 2.68e-5*x*x + 4.36e-4*x + 1.18e-1 - 86400;
         break;

      case (7):
         // f7;  no solution, discontinuity at x = 1
         y = (x >= 1 ? 1 : -1);
         break;

      case (8):
         // f8:  exact = 1
         y =  fabs(x - 1);
         break;

      case (9):
         // f9:  exact = 0.75
         y = 4*x - 3;
         break;

      case (10):
         // f10: exact = 1.347241384
         y = x*x*x*x*x*x - x - 1;
         break;
   }  /* switch */
   
   return y;
}  /* f */


/*------------------------------------------------------------
 * Function:  f_prime 
 */
double f_prime(double x, int which) {
   double y;

   switch (which) {
      case (1):
         // f1'
         y = 2*x;
         break;

      case (2):
         // f2'
         y = cos(x);
         break;

      case (3):
         // f3'
         y = 3*(x-1)*(x-1);
         break;

      case (4):
         // f4'
         y = pow(fabs(x-1), -2.0/3.0)/3.0;
         break;

      case (5):
         // f5'
         y = 3*x*x + 1;
         break;

      case (6):
         // f6'
         y = 2*2.68e-5*x + 4.36e-4;
         break;

      case (7):
         // f7'  (y' is actually undefined at x = 1)
         y = 0;
         break;

      case (8):
         // f8'  
         y = (x >= 1) ? 1 : -1;
         break;

      case (9):
         // f9' 
         y = 4;
         break;

      case (10):
         // f10' 
         y = 6*x*x*x*x*x - 1;
         break;
   }

   return y;
}  /* f_prime */
