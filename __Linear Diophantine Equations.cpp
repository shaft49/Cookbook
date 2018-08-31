/*
Returns char according to kind of solution
Ax + By = C Run+ Rise-
AX + (-B)y = C Run+ Rise+
When changing X, steps are either d/run or (d+run-1)/run depending on crossing or not.
When changing Y, steps are same as X, but take ABS(Rise) and assign sign to step.
Always assign sign to steps and ADD values to x and y.

set the value of a, b, c, and call solve() method. Solution depends on the return character.
To generate more solution use the value of tun and rise.
Often in problems we need to find solutions near vertical or horizontal line. For
those we can use move NearVerticalLine() and moveNearHorizontalLine() functions

To find another solution(x1, y1) = x + k * B / G, Y - k * A / g), g is an integer
*/
//Extended Euclidean Algorithm
struct LinearDiphontine {
    ll a, b, c, x, y, run, rise;
    char solution;

    ll ext_gcd ( ll A, ll B, ll *X, ll *Y ){
        ll x2, y2, x1, y1, x, y, r2, r1, q, r;
        x2 = 1; y2 = 0;
        x1 = 0; y1 = 1;
        for (r2 = A, r1 = B; r1 != 0; r2 = r1, r1 = r, x2 = x1, y2 = y1, x1 = x, y1 = y ) {
            q = r2 / r1;
            r = r2 % r1;
            x = x2 - (q * x1);
            y = y2 - (q * y1);
        }
        *X = x2; *Y = y2;
        return r2;
    }

    char solve () {
        if ( a == 0 && b == 0 ) {
            if ( c == 0 ) {
                //Infinite solutions. Anything works
                return solution = 'i';
            }
            else return solution = '0'; //No solution
        }
        if ( a == 0 || b == 0 ) {
            //Vertical or Horizontal Line
            if ( !a ) {
                if ( c % b != 0 ) return solution = '0'; /// No Solution
                run = 1; rise = 0;
                return solution = 'h'; /// ( anything, c / b )
            }
            else {
                if ( c % a != 0 ) return solution = '0'; ///No Solution
                run = 0; rise = 1;
                return solution = 'v'; /// ( c / a , anything )
            }
        }

        ll g = ext_gcd( a, b, &x, &y );
        if ( c % g != 0 ) {
            //No solution
            return solution = '0';
        }

        a /= g; b /= g; c /= g;

        ext_gcd ( a, b, &x, &y );
        x *= c; y *= c;

        ///run and rise calculation
        run = b; rise = -a;
        if ( run < 0 ) {
          run *= -1; rise *= -1;
        }

        return solution = '1';
    }

    ///Move solution near to vertical line x = p
    void moveNearVerticalLine( int p ) {
        if ( run == 0 ) return; /// Both are vertical
        ll jump = ( p - x ) / run;
        x += jump * run;
        y += jump * rise;

        if ( x < p ) { ///Keep solution on right of the line
            x += run;
            y += rise;
        }
    }

    void moveNearHorizontalLine( int p ) {
        if ( rise == 0 ) return; /// Both are horizontal
        ll jump = ( p - y ) / rise;
        x += jump * run;
        y += jump * rise;

        if ( y < p ) { ///Keep solution above the line
           if ( rise > 0 ) {
             x += run;
             y += rise;
           }
           else {
             x -= run;
             y -= rise;
           }
        }
    }
};
