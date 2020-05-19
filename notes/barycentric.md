Barycentric coordinates of a  triangle are relative to edges
of the  triangle rather than the  standard perpendicular x/y
axes. Using  such a system  allows interpolation of  a value
smoothely from one vertex to another.

Any  two points  on the  triangle may  be used  to form  the
implicit  equation of  a  line. We  can  use these  implicit
equations to  determine the distance  of any point  near the
triangle to one of the edges of thetriangle.

A linear equation for a curve is typically written

```
Ax + By + C = 0
```

A linear equation  of a line through any  two points (x0,y0)
and (x1,y1) can be written as

A vector  parallel to the  line given by the  the difference
between vector between the two points i.e.

```
(Δx,Δy) = (x1-x0, y1-y0)
```

The gradient is perpendicular to  the line, and the gradient
is given by (A,B), so to find A and B we only need find line
perpendicular to  (Δx,Δy), so we  rotate the vector  by 90
degrees

```
rot90 = (x,y) => (-y,x)
rot90(x1-x0, y1-y0) == (y0-y1, x1-x0)
```

So now we have

```
A = (y0-y1)
B = (x1-x0)
```

giving

```
(y0-y1)x + (x1-x0)y + C = 0
```

Solve for C by plugging in (x0, y0) to the above

```
(y0 - y1)x0 + (x1 - x0)y0 + C = 0
x0y0 - x0y1 + x1y0 - x0y0 + C = 0
x0y0 - x0y0 + x1y0 - x0y1 + C = 0
              x1y0 - x0y1 + C = 0
              x1y0        + C = x0y1
                            C = x0y1 - x1y0
```

plug in the found value of C to get the equation

```
f(x,y) = (y0-y1)x + (x1-x0)y + x0y1 - x1y0
```

when `f(x,y) = 0` then we are on the line

Given the gradient vector (A,B)  the distance from any given
point (i,j) to the line is found by

```
f(i,j) / sqrt(A² + B²)
```

i.e.

```
(y0-y1)i + (x1-x0)j + x0y1 - x1y0
---------------------------------
    sqrt((y0-y1)² + (x1-x0)²)
```

Given  two edges  of a  triangle, view  the triangle  so the
edges form an arrow pointing to your left. The distance from
the bottom edge  is expressed as γ, the  greek "gamma". The
distance from the  top edge of the triangle  is expressed as
β, the greek  "beta". The length of the  lower vector (b-a)
is considered "one unit" of β  i.e. `1 * β` and the length
of the  upper vector  (c-a) is considered  "one unit"  of γ
i.e. `1 * γ`

```
alpha = α
beta = β
gamma = γ
```

Given three vertices  (or points) of a triangle, a,  b and c
(or p0, p1, and p2)  then a point at barycentric coordinates
(β,γ) is

```
p(β,γ) = a + β(c - a) + γ(b - a)
       = a + βc - βa + γb - γa
       = a - βa - γa + βc + γb
       = (1 - β - γ)a + βc + γb
```

we introduce a term α, the greek "alpha"
to represent `(1 - β - γ)` to get

```
p(α,β,γ) = αa + βc + γb
```

this also means that

```
    α + β + γ == 1
```

β will be 0 when the point p is on the line ac (c-a) and if
we can find  a point not on  the line, then we  can use this
information to determine the scaling or (or value) of β.

Say `f_ac(x,y)`  is the  implicit equation  of for  the line
(c-a). We  know that this  function gives the  signed scaled
distance to the  line, and a point is on  the line when that
distance equals zero.

We  also know  that any  `k * f_ac(x,y)`  gives the  signed
scaled distance from the line.

β is some  form of signed scaled distance from  the line so
if  we want  to find  a formula  for β  we could  solve the
equation

```
β = k * f_ac(x,y)
```

But this is  two unknowns, however, we know that  β is 1 at
point b

in other words we can find k by

```
k * f_ac(x_b, y_b) = 1
k = 1 / f_ac(x_b, y_b)
```

so

for any point (x,y)

```
β = f_ac(x, y) / f_ac(x_b, y_b)
```

We can find gamma, and thusly alpha with a similar method.

γ is the signed scaled distance from the line ab where

```
γ = k * f_ab(x,y)
```

γ = 1 at point c so we can find k with

```
k * f_ab(x_c, y_c) = 1
k = 1 / f_ab(x_c, y_c)
```

and substitute back in to get gamma for any point (x,y)

```
γ = f_ab(x,y) / f_ab(x_c, y_c)
```

and of course, finally we now have alpha

```
α = (1 - β - γ)
```

Now we can find the distance  from the edges of the triangle
for  any given  point relative  to the  triangle's size  and
shape.

We can  use this to  determine whether  the point is  in the
triangle and so whether it should be drawn or not.

We can use this to  smoothely vary values across the triangle
smoothely  increasing  the  lighting  at each  pixel  from  a
lowly-lit  vertex to  a highly-lit  vertex depending  on how
close it is to the lighter or darker vertex
