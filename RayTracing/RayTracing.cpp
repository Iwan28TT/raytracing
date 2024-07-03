//
// Created by Bardio on 22/05/2024.
//

#include <iostream>

#ifdef _WIN32

#include "sphere.h"
#include "window.h"

#include <bardrix/ray.h>
#include <bardrix/light.h>
#include <bardrix/camera.h>
#include <bardrix/quaternion.h> // Ensure this header is included for bardrix::quaternion


/// \brief Calculates the light intensity at a given intersection point
/// \param shape The shape that was intersected
/// \param light The light source
/// \param camera The camera
/// \param intersection_point The intersection point of an object
/// \return The light intensity at the intersection point
/// \example double intensity = calculate_light_intensity(shape, light, camera, intersection_point);
double calculate_light_intensity(const bardrix::shape& shape, const bardrix::light& light, const bardrix::camera& camera,
const bardrix::point3& intersection_point) {
const bardrix::vector3 light_intersection_vector = intersection_point.vector_to(light.position).normalized();

// Angle between the normal and the light intersection vector
const double angle = shape.normal_at(intersection_point).dot(light_intersection_vector);

if (angle < 0) // This means the light is behind the intersection_point
return 0;

// Specular reflection
bardrix::vector3 reflection = bardrix::quaternion::mirror(light_intersection_vector,
shape.normal_at(intersection_point));
double specular_angle = reflection.dot(camera.position.vector_to(intersection_point).normalized());
double specular = std::pow(specular_angle, shape.get_material().get_shininess());

// We're calculating phong shading (ambient + diffuse + specular)
double intensity = shape.get_material().get_ambient();
intensity += shape.get_material().get_diffuse() * angle;
intensity += shape.get_material().get_specular() * specular;

// Max intensity is 1
return min(1.0, intensity * light.inverse_square_law(intersection_point));
}

int main() {
    int width = 600;
    int height = 600;
    // Create a window
    bardrix::window window("Raytracing", width, height);

    // Create a camera
    bardrix::camera camera = bardrix::camera({ 0,0,0 }, { 0,0,1 }, width, height, 60);

    // Create a sphere
    std::vector<sphere> spheres = {
        sphere(1.0, bardrix::point3(0.0, 0.0, 3.0), bardrix::material(0.1, 1, 0.5, 50)),
        sphere(0.5, bardrix::point3(1.0, 1.0, 4.0), bardrix::material(0.1, 1, 0.5, 50)),
        sphere(0.75, bardrix::point3(-1.0, -1.0, 5.0), bardrix::material(0.1, 1, 0.5, 50))
    };

    //Create a light
    std::vector <bardrix::light> lights = {
    bardrix::light({ -1,0,-1 }, 4, bardrix::color::cyan()),
    bardrix::light({ 1,0,1 }, 1, bardrix::color::cyan()),
    bardrix::light({2,0,1 }, 2, bardrix::color::cyan())

    };

    // [&camera, &sphere] is a capture list, this means we can access those objects outside the lambda
    // If you'd want to add a light you'd have to add this to the capture list too.
    window.on_paint = [&camera, &spheres, &lights](bardrix::window* window, std::vector<uint32_t>& buffer) {
        // Go through all the pixels
        for (int y = 0; y < window->get_height(); y++) {
            for (int x = 0; x < window->get_width(); x++) {

                // Shoot a ray from the camera to the pixel
                bardrix::ray ray = *camera.shoot_ray(x, y, 10);

                // Optional means that we can or cannot have a value
                // In order to check if the optional has a value, we use the has_value() method
                // If the optional has a value, we can access it using the value() method
                // E.g. intersection.value() -> bardrix::point3


                    // Default color is black
                    bardrix::color color = bardrix::color::green();
                for (sphere& s : spheres) {


                    std::optional<bardrix::point3> intersection = s.intersection(ray);

                    // If the ray intersects the sphere, paint the pixel white
                    if (intersection.has_value()) {
                        double intensity = 0;
                        for (bardrix::light& l : lights) {
                            intensity += calculate_light_intensity(s, l, camera, intersection.value());
                            color = l.color.blended(s.get_material().color) * intensity;
                        }
                    }
                }
                // Set the pixel
                buffer[y * window->get_width() + x] = color.argb(); // ARGB is the format used by Windows API
            }
        }
        };

    window.on_resize = [&camera](bardrix::window* window, int width, int height) {
        // Resize the camera
        camera.set_width(width);
        camera.set_height(height);

        window->redraw(); // Redraw the window (calls on_paint)
        };

    // Get width and height of the screen
    int screen_width = GetSystemMetrics(SM_CXSCREEN);
    int screen_height = GetSystemMetrics(SM_CYSCREEN);

    // Show the window in the center of the screen
    if (!window.show(screen_width / 2 - width / 2, screen_height / 2 - height / 2)) {
        std::cout << GetLastError() << std::endl;
        return -1;
    }

    bardrix::window::run();
}

#else // _WIN32

int main() {
    std::cout << "This example is only available on Windows." << std::endl;
    return 0;
}

#endif // _WIN32