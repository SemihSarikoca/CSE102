#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double data[3][3];
    double det;
} matrix;
typedef struct {
    double x, y, z;
} vector;
typedef struct {
    double a, b, c, d;
} third_order_polynomial;
typedef struct {
    double c1, c2, c3, c4, c5, c6, c7;
} coefficent;

void print_matrix(matrix initial_matrix);
void determinant_of_matrix(matrix* initial_matrix);
void inverse_matrix(matrix* initial_matrix, matrix* inverted_matrix);
void part1();

double find_orthogonal(vector vec_1, vector vec_2, vector* output_vec);
void part2();

double get_integral(third_order_polynomial p1, third_order_polynomial p2, int a, int b);
void part3();

int main() {
    part1();
    part2();
    part3();
    return 0;
}

void print_matrix(matrix initial_matrix) {
    printf("Matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%8.4f", initial_matrix.data[i][j]);
        }
        printf("\n");
    }
    printf("Determinant: %8.4f\n", initial_matrix.det);
}
void determinant_of_matrix(matrix* initial_matrix) {
    // Calculate the determinant using Laplace expansion
    double a11 = initial_matrix->data[0][0];
    double a12 = initial_matrix->data[0][1];
    double a13 = initial_matrix->data[0][2];
    double a21 = initial_matrix->data[1][0];
    double a22 = initial_matrix->data[1][1];
    double a23 = initial_matrix->data[1][2];
    double a31 = initial_matrix->data[2][0];
    double a32 = initial_matrix->data[2][1];
    double a33 = initial_matrix->data[2][2];
    double det = a11 * (a22*a33 - a32*a23) - a12 * (a21*a33 - a31*a23) + a13 * (a21*a32 - a31*a22);
    initial_matrix->det = det;
}
void inverse_matrix(matrix* initial_matrix, matrix* inverted_matrix) {
    determinant_of_matrix(initial_matrix);
    if (initial_matrix->det == 0) {
        printf("Matrix is not invertible.\n");
        return;
    }
    // Find the inverse matrix using the adjugate and determinant
    double det_inv = 1.0 / initial_matrix->det;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            double minor_det = initial_matrix->data[(j+1)%3][(i+1)%3] * initial_matrix->data[(j+2)%3][(i+2)%3]
                            - initial_matrix->data[(j+1)%3][(i+2)%3] * initial_matrix->data[(j+2)%3][(i+1)%3];
            inverted_matrix->data[i][j] = minor_det * det_inv;
        }
    }
}
void part1() {
    matrix initial_matrix = {
        .data = {
            { 1.0000, 0.9134, 0.2785 },
            { 0.9085, 0.6324, 0.5469 },
            { 0.1270, 0.0975, 0.9575 }
        }
    };
    matrix inverted_matrix = { .det = 0.0 };
    
    determinant_of_matrix(&initial_matrix);
    printf("Initial ");
    print_matrix(initial_matrix);

    inverse_matrix(&initial_matrix, &inverted_matrix);
    determinant_of_matrix(&inverted_matrix);
    printf("Inverted ");
    print_matrix(inverted_matrix);
}

double find_orthogonal(vector vec_1, vector vec_2, vector* output_vec) {
    // Calculate the angle between vec_1 and vec_2 in degrees
    double dot_product = vec_1.x * vec_2.x + vec_1.y * vec_2.y + vec_1.z * vec_2.z;
    double mag_vec_1 = sqrt(vec_1.x * vec_1.x + vec_1.y * vec_1.y + vec_1.z * vec_1.z);
    double mag_vec_2 = sqrt(vec_2.x * vec_2.x + vec_2.y * vec_2.y + vec_2.z * vec_2.z);
    double angle = acos(dot_product / (mag_vec_1 * mag_vec_2)) * 180.0 / M_PI;

    // Calculate the cross product of vec_1 and vec_2 to find the orthogonal vector
    vector orthogonal_vec = {
        .x = vec_1.y * vec_2.z - vec_1.z * vec_2.y,
        .y = vec_1.z * vec_2.x - vec_1.x * vec_2.z,
        .z = vec_1.x * vec_2.y - vec_1.y * vec_2.x
    };

    // Set the output vector
    *output_vec = orthogonal_vec;

    // Return the angle in degrees
    return angle;
}
void part2() {
    vector vec_1 = { 1.0, 2.0, 3.0 };
    vector vec_2 = { 4.0, 5.0, 6.0 };
    vector orthogonal_vec;
    double angle = find_orthogonal(vec_1, vec_2, &orthogonal_vec);
    printf("Angle between vec_1 and vec_2: %.2f degrees\n", angle);
    printf("Orthogonal vector: (%.2f, %.2f, %.2f)\n", orthogonal_vec.x, orthogonal_vec.y, orthogonal_vec.z);
}

double get_integral(third_order_polynomial p1, third_order_polynomial p2, int a, int b) {
    coefficent c;
    // Get the coefficent of the profuct of p1 and p2
    c.c1 = p1.a * p2.a;
    c.c2 = p1.a * p2.b + p1.b * p2.a;
    c.c3 = p1.a * p2.c + p1.b * p2.b + p1.c * p2.a;  
    c.c4 = p1.a * p2.d + p1.b * p2.c + p1.c * p2.b + p1.d * p2.a;
    c.c5 = p1.b * p2.d + p1.c * p2.c + p1.d * p2.b;
    c.c6 = p1.c * p2.d + p1.d * p2.c;
    c.c7 = p1.d * p2.d;
    // Calculate a and b value for interval
    double result_a = (c.c1 * pow(a, 7) / 7.0) + (c.c2 * pow(a, 6) / 6.0) + (c.c3 * pow(a, 5) / 5.0) + (c.c4 * pow(a, 4) / 4.0) + (c.c5 * pow(a, 3) / 3.0) + (c.c6 * pow(a, 2) / 2.0) + (c.c7 * a);
    double result_b = (c.c1 * pow(b, 7) / 7.0) + (c.c2 * pow(b, 6) / 6.0) + (c.c3 * pow(b, 5) / 5.0) + (c.c4 * pow(b, 4) / 4.0) + (c.c5 * pow(b, 3) / 3.0) + (c.c6 * pow(b, 2) / 2.0) + (c.c7 * b);
    double result = result_a - result_b;
    return result;
}
void part3() {
    third_order_polynomial p1, p2;
    coefficent c;
    int a, b;
    printf("Enter coefficients of the first third-order polynomial (a*x^3 + b*x^2 + c*x + d):\n");
    scanf("%lf %lf %lf %lf", &p1.a, &p1.b, &p1.c, &p1.d);
    printf("Enter coefficients of the second third-order polynomial (a*x^3 + b*x^2 + c*x + d):\n");
    scanf("%lf %lf %lf %lf", &p2.a, &p2.b, &p2.c, &p2.d);
    printf("Enter interval values a and b:\n");
    scanf("%d %d", &a, &b);
    double result = get_integral(p1, p2, a, b);
    printf("Integrated polynomial result between [%d,%d] = %.2f \n", a, b, result);
}
