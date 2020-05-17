#include "linalg/linalg.h"
#include "global/global.h"

#include <iostream>

namespace CxxRay {

using std::cout;
using std::endl;

constexpr Real Pi = 3.14159;
constexpr Real ToRad = Pi/180.0;
constexpr Real ToDeg = 180.0/Pi;

int test_deg_rad_conv()
{
    auto const val = 180.0;
    auto const rad = val * ToRad;
    cout << "rad=\t" << rad << "\n";

    auto const val1 = 180.0;
    auto const deg = val1 * ToDeg;
    cout << "deg=\t" << deg << "\n";

    return 0;
}

int test_vector_add()
{
    auto const a = Vec3{1, -1, 1};
    auto const b = Vec3{2, 4, 4};
    auto const c = a + b;

    cout << "add=\t" << toString(c) << "\n";

    return 0;
}

int test_vector_sub()
{
    auto const a = Vec3{3, 3, 3};
    auto const b = Vec3{1, 2, 3};
    auto const c = a - b;

    cout << "sub=\t" << toString(c) << "\n";

    return 0;
}

int test_vector_scale()
{
    auto const a = Vec3{3, 4, 5};
    auto const c = a * 2.0;

    cout << "scale=\t" << toString(c) << "\n";

    return 0;
}

//int test_vector_det()
//{
//    {
//        auto const a = Vec2{4, 3};
//        auto const b = Vec2{2, 5};
//
//        auto const c = det(a, b);
//
//        cout << "determinant=\t" << c << "\n";
//    }
//
//    {
//        auto const a = Vec3{1, 2, -1};
//        auto const b = Vec3{3, 0,  5};
//        auto const c = Vec3{1, 5,  0};
//
//        auto const val = det(a, b, c);
//
//        cout << "determinant=\t" << val << "\n";
//    }
//
//    return 0;
//}

int test_vector_dot()
{
    auto const a = Vec3{0, 1, 0};
    auto const b = Vec3{0, 0, 1};
    auto const c = dot(a, b);

    cout << "dot=\t" << c << "\n";

    return 0;
}

int test_vector_cross()
{
    auto const a = Vec3{1, 0, 0};
    auto const b = Vec3{0, 1, 0};
    auto const c = cross(a, b);

    cout << "cross=\t" << toString(c) << "\n";

    return 0;
}

int test_mat_add()
{
    {
        auto const a = Mat2{
            1, 1,
            1, 1
        };

        auto const b = Mat2{
            1, 2,
            3, 4
        };

        auto const c = a + b;

        cout << "Mat2 add=\n" << toString(c) << "\n";
    }

    {
        auto const a = Mat3{
            1, 1, 1,
            1, 1, 1,
            1, 1, 1
        };

        auto const b = Mat3{
            0, 1, 2,
            3, 4, 5,
            6, 7, 8
        };

        auto c = a + b;

        cout << "Mat3 add=\n" << toString(c) << "\n";
    }

    {
        auto const a = Mat4{
            1, 1, 1, 1,
            1, 1, 1, 1,
            1, 1, 1, 1,
            1, 1, 1, 1
        };

        auto const b = Mat4{
            -3, -2, -1, 0,
             0,  1,  2, 0,
             3,  4,  5, 0,
             6,  7,  8, 0
        };

        auto const c = a + b;

        cout << "Mat4 add=\n" << toString(c) << "\n";
    }

    return 0;
}

int test_mat_mul()
{
    {
        auto const a = Mat2{
            1.0, 2.0,
            3.0, 4.0
        };

        auto const b = Mat2{
            -2.0, 1.0,
            1.5, -0.5
        };

        auto const c = a * b;
        auto const d = a * 2.0;

        cout << "mul2=\n" << toString(c) << "\n";
        cout << "scale2=\n" << toString(d) << "\n";
    }

    {
        auto const a = Mat2{
            2.5, 0.0,
            0.0, 1.5
        };

        auto const b = Vec2{2.0, 4.0};

        auto const c = a * b;

        cout << "Vec2 mul=\n" << toString(c) << "\n";
    }

    {
        auto const a = Mat3{
            1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 8.0, 9.0
        };

        auto const b = Mat3{
            1.0, 2.0, 3.0,
            1.0, 2.0, 3.0,
            1.0, 2.0, 3.0
        };

        auto const c = a * b;
        auto const d = a * 2.0;

        cout << "mul3=\n" << toString(c) << "\n";
        cout << "scale3=\n" << toString(d) << "\n";
    }

    {
        auto const a = Mat3{
            1.5, 0.0, 0.0,
            0.0, 1.5, 0.0,
            0.0, 0.0, -2.5
        };

        auto const b = Vec3{2.0, 4.0, 3.0};

        auto const c = a * b;

        cout << "Vec3 mul=\n" << toString(c) << "\n";
    }

    {
        auto const a = Mat4{
            1.0, 2.0, 3.0, 4.9,
            4.0, 5.0, 6.0, 4.9,
            7.0, 8.0, 9.0, 4.9,
            7.0, 8.0, 9.0, 4.9
        };

        auto const b = Mat4{
            1.0, 2.0, 3.0, 2.2,
            1.0, 2.0, 3.0, 2.2,
            1.0, 2.0, 3.0, 2.2,
            1.0, 2.0, 3.0, 2.2
        };

        auto const c = a * b;
        auto const d = a * 2.0;

        cout << "mul4=\n" << toString(c) << "\n";
        cout << "scale4=\n" << toString(d) << "\n";
    }

    {
        auto const a = Mat4{
            1.5, 0.0,  0.0, 100.0,
            0.0, 1.5,  0.0, 100.0,
            0.0, 0.0, -2.5, 100.0,
            0.0, 0.0,  0.0, 1.0
        };

        auto const b = Vec4{2.0, 4.0, 3.0, 1.0};

        auto const c = a * b;

        cout << "Vec4 mul=\n" << toString(c) << "\n";
    }

    return 0;
}

int test_mat_det()
{
    {
        auto const a = Mat2{
            3, 8,
            4, 6
        };

        auto c = det(a);

        // should be -14

        cout << "Mat2 det=\n" << c << "\n";
    }

    {
        auto const a = Mat3{
            1,  2, -1,
            3,  0,  5,
            1,  5,  0
        };

        auto c = det(a);

        // should be -30

        cout << "Mat3 det=\n" << c << "\n";
    }

    {
        auto const a = Mat4{
             1, -2, 3,  2,
             2,  3, 1, -1,
             3,  3, 3,  3,
            -1,  4, 2,  1
        };

        auto c = det(a);

        // should be -141

        cout << "Mat4 det=\n" << c << "\n";
    }

    return 0;
}

int test_mat_inv()
{
    {
        auto const a = Mat3{
            1, 1, 2,
            1, 3, 4,
            0, 2, 5
        };

        auto const co = cofac(a);

        cout << "Mat3 cofac=\n" << toString(co) << "\n";

        auto const adj = adjoint(a);

        cout << "Mat3 adj=\n" << toString(adj) << "\n";

        auto const inv = inverse(a);

        cout << "Mat3 inv=\n" << toString(inv) << "\n";
    }

    {
        auto const a = Mat4{
            1, 1, 2, 2,
            1, 3, 4, 9,
            2, 2, 5, 7,
            3, 6, 1, 4
        };

        auto const co = cofac(a);

        cout << "Mat4 cofac=\n" << toString(co) << "\n";

        auto const adj = adjoint(a);

        cout << "Mat4 adj=\n" << toString(adj) << "\n";

        auto const inv = inverse(a);

        cout << "Mat4 inv=\n" << toString(inv) << "\n";

        auto const ident = inv * a;

        cout << "Mat4 ident=\n" << toString(ident) << "\n";
    }

    return 0;
}

int linalgTestMain()
{
    cout << "\ntest_unit_tests\n";

    test_deg_rad_conv();
    test_vector_add();
    test_vector_sub();
    test_vector_scale();
    //test_vector_det();
    //test_vector_rot90();
    test_vector_dot();
    test_vector_cross();
    test_mat_add();
    test_mat_mul();
    test_mat_det();
    test_mat_inv();

    return 0;
}

} // namespace CxxRay

int main()
{
    CxxRay::linalgTestMain();

    return 0;
}
