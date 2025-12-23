/**
    This example shows the interface using virtual functions in C++.
*/

#include <iostream>
#include <memory>

class Shape
{
  public:
    virtual double
    area() const = 0;   // Pure virtual function
    virtual ~Shape() {} // Virtual destructor
};

class Circle : public Shape
{
  private:
    double radius;

  public:
    Circle(double r) : radius(r) {}
    double
    area() const override
    {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape
{
  private:
    double width, height;

  public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double
    area() const override
    {
        return width * height;
    }
};

int
main()
{
    std::unique_ptr<Shape> shapes[2];
    shapes[0] = std::make_unique<Circle>(5.0);
    shapes[1] = std::make_unique<Rectangle>(4.0, 6.0);

    // The following line would cause a compilation error because Shape is an abstract class
    // Shape a = new Shape();

    for (int i = 0; i < 2; ++i) {
        std::cout << "Area of shape " << i + 1 << ": " << shapes[i]->area() << std::endl;
    }

    return 0;
}