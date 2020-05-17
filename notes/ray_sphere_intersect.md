ANGLE OF TWO VECTORS

law of cosines

```
|C|² = |A|² + |B|² + 2(A·B)
|C|² = |A|² + |B|² + 2|A||B|cos(θ)

A·B = |A||B|cos(θ)

           A·B
cos(θ) = --------
          |A||B|

θ = arccos( A·B / |A||B| )
```

CROSS PRODUCT

θ = angle between A and B
n = a unit vector perpendicular to the plane containing a and b in the direction given by the right-hand rule

```
A x B = |A||B|sin(θ)n
```

```
s1 = a2b3 - a3b2
s2 = a3b1 - a1b3
s3 = a1b2 - a2b1
```

PARAMETRIC RAY
we want to check for all points p along the ray
from the ray's starting point to positive infinity

parameterized with t, with the ray's starting point
vector at e and the ray's direction vector d

```
p = f(t) = e + t*d;
```

which reads, to find a point at (time) t, start at
point e and go some amount t in the d direction

VECTOR FORMULA SPHERE

we use a vector formula equation g for whethere a point p is on a sphere
with center c, of radius R

```
g(p) = (p - c) · (p - c) - R² = 0
```

if the center is the origin then this is basically checking whether
magnitude of p (the distance to p from the origin)
is the same as the radius since a vector dot
itself is that vector's magnitude squared, and this is just
checking a vector dot itself against the radius squared, i.e.
when the distance to p minus the radius is 0

RAY SPHERE INTERSECT

we want to find a value t (if any) that gives us a point
along a parameterized ray, where that point along that
ray and the sphere intersect

using the formulas above and plugging in the parameterized
formula f(t) for a point p on a ray into the vector formula
for a sphere g(p), we check to see that distance to p from center
and radius cancel, i.e. where the result of the equation is 0

```
0 = g(p)       = (p - c) · (p - c) - R² = 0
0 = g(f(t))    = (f(t) - c) · (f(t) - c) - R² = 0
0 = g(e + t*d) = (e + t*d - c) · (e + t*d - c) - R²
0 =              (d·d)t² + ((2d)·(e-c))t + (e-c)·(e-c) - R²
```

this is a quadratic in t

```
At² + Bt + C = 0
```

with constants

```
A = d · d
B = 2d · (e-c)
C = (e-c) · (e-c) - R²
```

the discriminant in the quadratic

```
D = B² - 4AC
```

tells the number of real solutions

```
D < 0 : no intersections
D > 0 : two solutions
D = 0 : one solution
```

LAMBERTIAN SHADING

the surface normal at a point p on an implicit
surface is given by the gradient of the implicit
function

```
n = ∂f(p) = [ ∂f/∂x, ∂f/∂y, ∂f/∂z ]
```

for a point p = [x,y,z] on the sphere
centered at [l,m,n]

the surface normal vector is given by

```
N = [ (x-l)/r, (y-m)/r , (z-n)/r ]
```

k = diffuse color
I = light intensity

n = surface normal vector
l = light vector

```
L = k * I max(0, n·l)
```
